/**
 * Copyright (C) 2009 Ubixum, Inc. 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **/


#include <fx2regs.h>
#include <fx2macros.h>
#include <serial.h>


/**
 * using the comp port implies that timer 2 will be used as
 * a baud rate generator.  (Don't use timer 2)
 **/
void sio0_init( WORD baud_rate ) __critical { // baud_rate max should be 57600 since int=2 bytes
	
    WORD hl; // hl value for reload	
	BYTE mult; // multiplier for clock speed
    DWORD tmp; // scratch for mult/divide

    // 0 = 12mhz, 1=24mhz, 2=48mhz    
	mult = CPUFREQ == CLK_12M ? 1 :
           CPUFREQ == CLK_24M ? 2 : 4; // since only 3 clock speeds, fast switch instead of doing 2^clock speed pow(2,clkspd)

	// set the clock rate
	// use clock 2
	RCLK=1;TCLK=1;

//    RCAP2H:L = 0xFFFF - CLKOUT / 32 x baud_rate

    // in order to round to nearest value..
    // tmp * 2 // double
    // tmp / rate // do the divide
    // tmp + 1 // add one (which is like adding 1/2)
    // tmp / 2 // back to original rounded 
    tmp = mult * 375000L * 2 ;
    tmp /= baud_rate;
    tmp += 1;
    tmp /= 2;

    hl = 0xFFFF - (WORD)tmp;

	RCAP2H= MSB(hl);
	// seems that the 24/48mhz calculations are always one less than suggested values    
    // trm table 14-16
	RCAP2L= LSB(hl) + (mult>0?1:0);
	TR2=1; // start the timer
	
	// set up the serial port	
	SM0 = 0; SM1=1;// serial mode 1 (asyncronous)	
	SM2 = 0 ; // has to do with receiving
	REN = 1 ; // to enable receiving
    PCON |= 0x80; // SET SMOD0, baud rate doubler
    TI = 1; // we send initial byte

}

char getchar() {
  char c;
  while (!RI)
    ;  
  c=SBUF0;
  RI=0;
  return c;
}

void _transchar(char c) {
 while ( !TI ); // wait for TI=1 
 TI=0;
 SBUF0=c;
}

void putchar (char c) {
  if (c=='\n') _transchar('\r'); // transmit \r\n
  _transchar(c);  
  if (c == '\r' ) _transchar('\n'); // transmit \r\n
}


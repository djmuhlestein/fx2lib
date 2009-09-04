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

#include <stdio.h>

#include <fx2regs.h>
#include <fx2macros.h>
#include <lights.h>
#include <serial.h>



volatile BYTE ctr=0;
BYTE ctr_repeat=200;
volatile BOOL on=FALSE;


void timer1_isr() interrupt 3 __critical {
	
 if (ctr == 0) { // timer overflowed ctr_repeat times
  if (on) {
     d2on();
  } else {
     d2off();
  }
  on = !on;  
 }
 
 ctr = ctr >= ctr_repeat ? 0 : ctr + 1;
 
}



void main(void)
{

    SETCPUFREQ(CLK_48M);

    // if this image is loaded to as iic to
    // the eeprom
    // the C2 bit will turn this on
    // turn it back off so the device can 
    // handle usb requests
    USBCS &= ~bmRENUM;

	EA=1; // enable interrupts

    sio0_init(57600);
    
	// timer 0 setup
	
	TL1=TH1=0; // start at 0
	ET1=1; // timer 1 interrupts
	TR1=1; // start timer 1
	
	
	d5off(); // end init
	
	while (1) {
		char r=getchar();
		putchar(r);
	}


}

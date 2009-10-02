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

#include <serial.h>
#include <delay.h>
#include <i2c.h>
#include <lights.h>

#define LG_PROM 0x51  // large prom ( is 16 bit addr mode)

#define READ_SIZE 100

xdata BYTE buf[READ_SIZE];

#define IIC_SIZE 8
extern xdata BYTE fx2_c0[];

/*
 Modified eeprom_write that always uses two byte buffer.
 So can write to LG_PROM w/ out recompiling lib.
 (The library dynamically detects the prom based on the startup state.
  On the dev board, you can switch the prom with EEPROM select while
  the firmware is running.)
*/
void eeprom_write_local(BYTE prom_addr, WORD addr, WORD length, BYTE* buf) {
    BYTE addr_len=0;
    // 1st bytes of buffer are address and next byte is value
    BYTE data_buffer[3];
    BYTE cur_byte=0;
    
    while ( cur_byte<length ) {
        addr_len=0;
        printf ( "%d %04x:%02x\n", cur_byte, addr, buf[cur_byte]);
        data_buffer[addr_len++] = MSB(addr);
        data_buffer[addr_len++] = LSB(addr);
        data_buffer[addr_len++] = buf[cur_byte++];
        i2c_write ( prom_addr, addr_len, data_buffer, 0, NULL );
        ++addr; // next byte goes to next address
    }
    
}

void main() {
    
 BOOL on=FALSE;
 unsigned int size=0;

 SETCPUFREQ(CLK_48M);
 sio0_init(57600);
 
 
 eeprom_write_local(LG_PROM, 0, IIC_SIZE, fx2_c0);

 
 while (1) {
    delay(1000);
    if (on) {d5on();} else {d5off();}
    on = !on;    
 }
 

}

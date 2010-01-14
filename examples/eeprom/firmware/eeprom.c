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

#include <string.h>
#include <stdio.h>

#include <fx2regs.h>
#include <fx2macros.h>
#include <autovector.h>
#include <setupdat.h>
#include <i2c.h>
#include <lights.h>
#include <serial.h>
#include <gpif.h>
#include <eputils.h>

#define SYNCDELAY() SYNCDELAY4;

volatile bit dosud;
bit on;
WORD count;


void main() {

 REVCTL = 0; // not using advanced endpoint controls

 dosud=FALSE;
 on=FALSE;
 
 REVCTL = 0x03; // DYN_OUT=1, ENH_PKT=1
 
 RENUMERATE_UNCOND();
 

 SETCPUFREQ(CLK_48M);
 sio0_init(57600); // needed for printf on sio0 
 
 
 USE_USB_INTS();
 
 ENABLE_SUDAV();
 ENABLE_USBRESET();
 ENABLE_HISPEED();
 
 EA=1;
 

 while(TRUE) {

 //printf ( "sud is %d\n" , dosud );
 if (dosud) {
   handle_setupdata();
   dosud=FALSE;
 } 

 }
 

}


#define VC_EEPROM 0xb1
        
BOOL handle_vendorcommand(BYTE cmd) {
 WORD addr=SETUP_VALUE(),len=SETUP_LENGTH();
 printf ( "Handle Vendor Command %02x, addr %d, len %d\n" , cmd, addr, len );
 switch (cmd) {
    case VC_EEPROM:
        {            
            // wait for ep0 not busy
            switch (SETUP_TYPE) {
            case 0xc0:
                 while (len) { // still have bytes to read
                    BYTE cur_read = len > 64 ? 64 : len; // can't read more than 64 bytes at a time
                    while (EP0CS&bmEPBUSY); // can't do this until EP0 is ready                
                    eeprom_read(0x51, addr, cur_read, EP0BUF );
                    EP0BCH=0;
                    SYNCDELAY();
                    EP0BCL=cur_read;
                    len -= cur_read;
                    addr += cur_read;
                }
                break;
            case 0x40:                
                while (len) {
                   BYTE cur_write, c;
//                   printf ( "Len More Bytes %d\n" , len );
                   EP0BCL = 0; // allow pc transfer in
                   while(EP0CS & bmEPBUSY); // wait
                   cur_write=EP0BCL;
//                   printf ( "Writing %d Bytes to %d..\n", cur_write, addr );
                   if ( !eeprom_write(0x51, addr, cur_write, EP0BUF ) ) return FALSE;
                   addr += cur_write;
                   len -= cur_write;
                }
                break;
             default:
                return FALSE; // bad type
            }
            
            printf ( "All OK\n" );
            return TRUE;
        }
    }
 return FALSE;
}
  

// set *alt_ifc to the current alt interface for ifc
BOOL handle_get_interface(BYTE ifc, BYTE* alt_ifc) {
 *alt_ifc=0;
 return TRUE;
}
// return TRUE if you set the interface requested
// NOTE this function should reconfigure and reset the endpoints
// according to the interface descriptors you provided.
BOOL handle_set_interface(BYTE ifc,BYTE alt_ifc) {  
 //return ifc==0&&alt_ifc==0; 
 printf ( "Host wants to set interface: %d\n", alt_ifc );
 
 return TRUE;
}
// handle getting and setting the configuration
// 0 is the default.  If you support more than one config
// keep track of the config number and return the correct number
// config numbers are set int the dscr file.
volatile BYTE config=1;
BYTE handle_get_configuration() { 
 return config; 
}
// return TRUE if you handle this request
// NOTE changing config requires the device to reset all the endpoints
BOOL handle_set_configuration(BYTE cfg) { 
 printf ( "host wants config: %d\n" , cfg );
 config=cfg; 
 return TRUE;
}


void sudav_isr() interrupt SUDAV_ISR {
 dosud=TRUE;
 CLEAR_SUDAV();
}

void usbreset_isr() interrupt USBRESET_ISR {
 handle_hispeed(FALSE);
 CLEAR_USBRESET();
}
void hispeed_isr() interrupt HISPEED_ISR {
 handle_hispeed(TRUE);
 CLEAR_HISPEED();
}


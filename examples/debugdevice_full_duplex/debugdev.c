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
#include <autovector.h>
#include <lights.h>
#include <setupdat.h>
#include <eputils.h>

#define SYNCDELAY SYNCDELAY4
#define REARMVAL 0x80
#define REARM() EP2BCL=REARMVAL

volatile WORD bytes;
volatile __bit gotbuf;
volatile BYTE icount;
volatile __bit got_sud;
DWORD lcount;
__bit on;

extern WORD debug_dscr;
extern void _transchar(char c);
void main()
{
	REVCTL=0; // not using advanced endpoint controls

	d2off();
	on=0;
	lcount=0;
	got_sud=FALSE;
	icount=0;
	gotbuf=FALSE;
	bytes=0;

	// renumerate
	RENUMERATE_UNCOND();


	SETCPUFREQ(CLK_48M);
	SETIF48MHZ();
	sio0_init(115200);


	USE_USB_INTS();
	ENABLE_SUDAV();
	ENABLE_SOF();
	ENABLE_HISPEED();
	ENABLE_USBRESET();


	// only valid endpoints are 2/6
	EP2CFG = 0xA2; // 10100010
	SYNCDELAY;
	EP6CFG = 0xE2; // 11100010
	SYNCDELAY;
	EP1INCFG &= ~bmVALID;
	SYNCDELAY;
	EP1OUTCFG &= ~bmVALID;
	SYNCDELAY;
	EP4CFG &= ~bmVALID;
	SYNCDELAY;
	EP8CFG &= ~bmVALID;
	SYNCDELAY;


	// arm ep2
	EP2BCL = 0x80; // write once
	SYNCDELAY;
	EP2BCL = 0x80; // do it again


	// make it so we enumberate


	EA=1; // global __interrupt enable
	printf ( "USB DEBUG: Done initializing stuff\n" );


	d3off();

	while(TRUE) {

		if ( got_sud ) {
			handle_setupdata();
			got_sud=FALSE;
		}

		if ( !(EP2468STAT & bmEP2EMPTY) ) {
			if  ( !(EP2468STAT & bmEP6FULL) ) { // wait for at least one empty in buffer
				WORD i;

				bytes = MAKEWORD(EP2BCH,EP2BCL);

				for (i=0;i<bytes;++i)
					_transchar(EP2FIFOBUF[i]);
				REARM();
			}
		}
	}

}

// copied routines from setupdat.h

// value (low byte) = ep
#define VC_EPSTAT 0xB1


BOOL handle_vendorcommand(BYTE cmd)
{
	__xdata BYTE* pep;
	switch ( cmd ) {
	case 6:
		return TRUE;
	case VC_EPSTAT:

		pep = ep_addr(SETUPDAT[2]);
		if (pep) {
			EP0BUF[0] = *pep;
			EP0BCH=0;
			EP0BCL=1;
			return TRUE;
		}
	default:
		printf ( "Need to implement vendor command: %02x\n", cmd );
	}
	return FALSE;
}

// this firmware only supports 0,0
BOOL handle_get_interface(BYTE ifc, BYTE* alt_ifc)
{
//	printf ( "Get Interface\n" );
	if (ifc==0) {
		*alt_ifc=0;
		return TRUE;
	} else {
		return FALSE;
	}
}
BOOL handle_set_interface(BYTE ifc, BYTE alt_ifc)
{
	if (ifc==0&&alt_ifc==0) {
		// SEE TRM 2.3.7
		// reset toggles
		RESETTOGGLE(0x02);
		RESETTOGGLE(0x86);
		// restore endpoints to default condition
		RESETFIFO(0x02);
		EP2BCL=0x80;
		SYNCDELAY;
		EP2BCL=0X80;
		SYNCDELAY;
		RESETFIFO(0x86);
		return TRUE;
	} else
		return FALSE;
}

// get/set configuration
BYTE handle_get_configuration()
{
	return 1;
}

BOOL handle_get_descriptor()
{
        BYTE desc = SETUPDAT[3];
	if (desc != DSCR_DEBUG_TYPE)
		return FALSE;

	SUDPTRH = MSB((WORD)&debug_dscr);
	SUDPTRL = LSB((WORD)&debug_dscr);
	return TRUE;
}

BOOL handle_set_configuration(BYTE cfg)
{

	return cfg==1 ? TRUE : FALSE; // we only handle cfg 1
}


// copied usb jt routines from usbjt.h
void sudav_isr() __interrupt SUDAV_ISR {

	got_sud=TRUE;
	CLEAR_SUDAV();
}

__bit on5;
__xdata WORD sofct=0;
void sof_isr () __interrupt SOF_ISR __using 1
{
	if(++sofct==8000) { // about 8000 sof __interrupts per second at high speed
		on5 = !on5;
		if (on5) {
			d5on();
		} else {
			d5off();
		}
		sofct=0;
	}
	CLEAR_SOF();
}

void usbreset_isr() __interrupt USBRESET_ISR
{
	handle_hispeed(FALSE);
	CLEAR_USBRESET();
}
void hispeed_isr() __interrupt HISPEED_ISR
{
	handle_hispeed(TRUE);
	CLEAR_HISPEED();
}


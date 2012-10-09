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

#define SYNCDELAY() SYNCDELAY4

volatile __bit got_sud;

static void setup_usb(void)
{
	USE_USB_INTS();
	ENABLE_SUDAV();
	ENABLE_SOF();
	ENABLE_HISPEED();
	ENABLE_USBRESET();

	CPUCS = 0x12;
	REVCTL = bmBIT0 | bmBIT1;

	IFCONFIG = 0xe3;
	SYNCDELAY();

	PINFLAGSAB = 0xe8; /* FLAGA = EP2EF, FLAGB = EP6FF */
	SYNCDELAY();

	PORTACFG |= 0x80;
	SYNCDELAY();

	// only valid endpoints are 2/6
	EP1INCFG &= ~bmVALID;
	SYNCDELAY();

	EP1OUTCFG &= ~bmVALID;
	SYNCDELAY();

	EP2CFG = 0xa0; /* EP2 OUT, 4x buffer */
	SYNCDELAY();

	EP4CFG = 0x02;
	SYNCDELAY();

	EP6CFG = 0xe0; /* EP6 IN, 4x buffer */
	SYNCDELAY();

	EP8CFG = 0x02;
	SYNCDELAY();

	FIFORESET = 0x80;
	SYNCDELAY();

	FIFORESET = 0x02;
	SYNCDELAY();

	FIFORESET = 0x04;
	SYNCDELAY();

	FIFORESET = 0x06;
	SYNCDELAY();

	FIFORESET = 0x08;
	SYNCDELAY();

	FIFORESET = 0x00;
	SYNCDELAY();

	OUTPKTEND = 0x82;
	SYNCDELAY();
	OUTPKTEND = 0x82;
	SYNCDELAY();
	OUTPKTEND = 0x82;
	SYNCDELAY();
	OUTPKTEND = 0x82;
	SYNCDELAY();


	EP2FIFOCFG = 0;
	SYNCDELAY();

	EP2FIFOCFG = bmAUTOOUT | bmWORDWIDE;
	SYNCDELAY();

	EP6FIFOCFG = 0;
	SYNCDELAY();

	EP6FIFOCFG = bmAUTOIN | bmWORDWIDE;
	SYNCDELAY();

	EP6AUTOINLENH = 0x02;
	SYNCDELAY();

	EP6AUTOINLENL = 0x00;
	SYNCDELAY();

}

void main()
{
	got_sud=FALSE;

	// renumerate
	RENUMERATE_UNCOND();

	setup_usb();

	EA=1; // global __interrupt enable

	while(TRUE) {
		if (got_sud) {
			handle_setupdata();
			got_sud=FALSE;
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
		break;
	}
	return FALSE;
}

// this firmware only supports 0,0
BOOL handle_get_interface(BYTE ifc, BYTE* alt_ifc)
{
	if (ifc==0) {
		*alt_ifc=0;
		return TRUE;
	} else {
		return FALSE;
	}
}
BOOL handle_set_interface(BYTE ifc, BYTE alt_ifc)
{
	RESETTOGGLE(0x02);
	RESETTOGGLE(0x86);
	OUTPKTEND=0x82;
	OUTPKTEND=0x82;
	OUTPKTEND=0x82;
	OUTPKTEND=0x82;
	return ifc == 0 && alt_ifc == 0;
}

// get/set configuration
BYTE handle_get_configuration()
{
	return 1;
}

BOOL handle_get_descriptor(BYTE desc)
{
	(void)desc;
	return FALSE;
}

BOOL handle_set_configuration(BYTE cfg)
{

	return cfg==1 ? TRUE : FALSE; // we only handle cfg 1
}

void sudav_isr() __interrupt SUDAV_ISR
{

	got_sud=TRUE;
	CLEAR_SUDAV();
}

void sof_isr () __interrupt SOF_ISR __using 1
{
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

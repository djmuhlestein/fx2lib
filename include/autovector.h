// Copyright (C) 2010 Ubixum, Inc. 
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA



/** \file usbjt.h
 *
 * To use usbjt, you must tell the linker where to put the IN2JT.
 * It must lie on a page boundary or your interrupts won't work right.
 *
 * example:
 * -Wl"-b INT2JT = 0x1A00"
 *
 * Make sure that INT2JT doesn't overlap your other code!
 *
 * Unlike the standard fx2 interrupts (\ref fx2ints.h), the autovectored
 * interrupts are defined in assemply and have pre-written function names.
 * Be sure to override the functions defined in this header or your 
 * interrupt handler will not be called.
 **/

#ifndef USBJT_H
#define USBJT_H

#include "fx2regs.h"


/**
 * Enable all interrupts (EA=1) separate from this macro.
 * This macro causes the autovector assembly for int2 interrupts
 * to be overlayed at 0x43.  In addition, the jump table for the
 * interrupts will be included in the firmware.  The jump table
 * must lie on a page boundary.  This is done by passing the linker
 * arguments to sdcc.
 *
 * \code
 *   sdcc <files> -Wl"-b INT2JT = 0xaddr"
 * \endcode
 **/
#define USE_USB_INTS() {EUSB=1;\
                        INTSETUP|=bmAV2EN;}
/** This macro causes the autovector assemby for int4 to be overlayed
 * at 0x53.  Don't use this if you want external pin generated int4 interrupts
 * and want to define your own interrupt handler.  It is possible to use
 * usb interrupts with autovectoring and not use GPIF interrupts but GPIF
 * interrupts require the USB jump table.  (You can't USE your own usb interrupt
 * handler if you want to enable GPIF interrupts.)
 **/
#define USE_GPIF_INTS() {EIEX4=1;\
                        INTSETUP|=bmAV4EN|INT4IN;}
             

#define CLEAR_USBINT() EXIF &= ~0x10
#define CLEAR_GPIF() EXIF &= ~0x40

#define ENABLE_SUDAV() USBIE|=bmSUDAV
#define CLEAR_SUDAV() CLEAR_USBINT(); USBIRQ=bmSUDAV

#define ENABLE_SUTOK() USBIE|=bmSUTOK;
#define CLEAR_SUTOK() CLEAR_USBINT(); USBIRQ=bmSUTOK

#define ENABLE_SOF() USBIE|=bmSOF
#define CLEAR_SOF() CLEAR_USBINT(); USBIRQ=bmSOF

#define ENABLE_SUSPEND() USBIE|=bmSUSP
#define CLEAR_SUSPEND() CLEAR_USBINT(); USBIRQ=bmSUSP

#define ENABLE_USBRESET() USBIE|= bmURES
#define CLEAR_USBRESET() CLEAR_USBINT(); USBIRQ=bmURES

#define ENABLE_HISPEED() USBIE|=bmHSGRANT
#define CLEAR_HISPEED() CLEAR_USBINT(); USBIRQ=bmHSGRANT

#define ENABLE_EP0IN() EPIE|=bmEP0IN
#define CLEAR_EP0IN() CLEAR_USBINT(); EPIRQ=bmEP0IN

#define ENABLE_EP0OUT() EPIE|=bmEP0OUT
#define CLEAR_EP0OUT() CLEAR_USBINT(); EPIRQ=bmEP0OUT

#define ENABLE_EP1IN() EPIE|=bmEP1IN
#define CLEAR_EP1IN() CLEAR_USBINT(); EPIRQ=bmEP1IN

#define ENABLE_EP1OUT() EPIE|=bmEP1OUT
#define CLEAR_EP1OUT() CLEAR_USBINT(); EPIRQ=bmEP1OUT

#define ENABLE_EP2() EPIE|=bmEP2
#define CLEAR_EP2() CLEAR_USBINT(); EPIRQ=bmEP2

#define ENABLE_EP4() EPIE|=bmEP4
#define CLEAR_EP4() CLEAR_USBINT(); EPIRQ=bmEP4

#define ENABLE_EP6() EPIE|=bmEP6
#define CLEAR_EP6() CLEAR_USBINT(); EPIRQ=bmEP6

#define ENABLE_EP8() EPIE|=bmEP8
#define CLEAR_EP8() CLEAR_USBINT(); EPIRQ=bmEP8

#define ENABLE_EP2ISOERR() USBERRIE |= bmISOEP2
#define CLEAR_EP2ISOERR() CLEAR_USBINT(); USBERRIRQ = bmISOEP2

#define ENABLE_EP6PF() EP6FIFOIE |= bmBIT2
#define CLEAR_EP6PF() CLEAR_GPIF(); EP6FIFOIRQ=bmBIT2

#define ENABLE_EP6FF() EP6FIFOIE |= bmBIT0
#define CLEAR_EP6FF() CLEAR_GPIF(); EP6FIFOIRQ=bmBIT0

#define ENABLE_GPIFDONE() GPIFIE |= 0x01;
#define CLEAR_GPIFDONE() CLEAR_GPIF(); GPIFIRQ = 0x01;

#define ENABLE_GPIFWF() GPIFIE |= 0x02;
#define CLEAR_GPIFWF() GLEAR_GPIF(); GPIFIRQ = 0x02;

/**
 * ez-usb has 12 built in ISRs, to get
 * sdcc to put these USB ISRs immediately
 * after the other ISRs (and not waste space)
 * we start at 13
 **/
typedef enum {
  SUDAV_ISR=13,
  SOF_ISR,
  SUTOK_ISR,
  SUSPEND_ISR,
  USBRESET_ISR,
  HISPEED_ISR,
  EP0ACK_ISR,  
  EP0IN_ISR,
  EP0OUT_ISR,
  EP1IN_ISR,
  EP1OUT_ISR,
  EP2_ISR,
  EP4_ISR,
  EP6_ISR,
  EP8_ISR,
  IBN_ISR,
  EP0PING_ISR,
  EP1PING_ISR,
  EP2PING_ISR,
  EP4PING_ISR,
  EP6PING_ISR,
  EP8PING_ISR,
  ERRLIMIT_ISR,  
  EP2ISOERR_ISR,
  EP4ISOERR_ISR,
  EP6ISOERR_ISR,
  EP8ISOERR_ISR,
  RESERVED_ISR,
  EP2PF_ISR,
  EP4PF_ISR,
  EP6PF_ISR,
  EP8PF_ISR,
  EP2EF_ISR,
  EP4EF_ISR,
  EP6EF_ISR,
  EP8EF_ISR,
  EP2FF_ISR,
  EP4FF_ISR,
  EP6FF_ISR,
  EP8FF_ISR,
  GPIFDONE_ISR,
  GPIFWF_ISR
} USB_ISR;

// you must include the predef of these in the file with your main
// so lets just define them here

void usb_isr(void) __interrupt (8);
void sudav_isr(void) __interrupt;
void sof_isr(void) __interrupt;
void sutok_isr(void) __interrupt;
void suspend_isr(void) __interrupt;
void usbreset_isr(void) __interrupt;
void hispeed_isr(void) __interrupt;
void ep0ack_isr(void) __interrupt;
void ep0in_isr(void) __interrupt;
void ep0out_isr(void) __interrupt;
void ep1in_isr(void) __interrupt;
void ep1out_isr(void) __interrupt;
void ep2_isr(void) __interrupt;
void ep4_isr(void) __interrupt;
void ep6_isr(void) __interrupt;
void ep8_isr(void) __interrupt;
void ibn_isr(void) __interrupt;
void ep0ping_isr(void) __interrupt;
void ep1ping_isr(void) __interrupt;
void ep2ping_isr(void) __interrupt;
void ep4ping_isr(void) __interrupt;
void ep6ping_isr(void) __interrupt;
void ep8ping_isr(void) __interrupt;
void errlimit_isr(void) __interrupt;
void ep2isoerr_isr(void) __interrupt;
void ep4isoerr_isr(void) __interrupt;
void ep6isoerr_isr(void) __interrupt;
void ep8isoerr_isr(void) __interrupt;
void spare_isr(void) __interrupt; // not used
// gpif ints
void gpif_isr(void) __interrupt (10);
void ep2pf_isr(void) __interrupt;
void ep4pf_isr(void) __interrupt;
void ep6pf_isr(void) __interrupt;
void ep8pf_isr(void) __interrupt;
void ep2ef_isr(void) __interrupt;
void ep4ef_isr(void) __interrupt;
void ep6ef_isr(void) __interrupt;
void ep8ef_isr(void) __interrupt;
void ep2ff_isr(void) __interrupt;
void ep4ff_isr(void) __interrupt;
void ep6ff_isr(void) __interrupt;
void ep8ff_isr(void) __interrupt;
void gpifdone_isr(void) __interrupt;
void gpifwf_isr(void) __interrupt;

#endif


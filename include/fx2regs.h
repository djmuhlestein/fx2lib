// Copyright (C) 2009 Ubixum, Inc. 
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

/*! \file 
 *
 * This is the basic header/register file for working with the cypress fx2
 * (cyc768013) and variants 8051 chipset.  It contains the special function 
 * register definitions as well as the special configuration registers 
 * addresses.
 * 
 * The TRM for the fx2 chip contains the full documentation for what each of
 * these registers do.
 *
 * */


/** \mainpage FX2LIB Documentation
 *  \verbinclude README
 **/

/** \example fw.c
 * The firmware framework allows for easily beginning a new firware project.
 **/

#ifndef FX2REGS_H 
#define FX2REGS_H

#include "fx2types.h"

__xdata __at 0xE400 volatile BYTE GPIF_WAVE_DATA;
__xdata __at 0xE480 volatile BYTE RES_WAVEDATA_END;

// General Configuration

__xdata __at 0xE600 volatile BYTE CPUCS;  ///< Control & Status
__xdata __at 0xE601 volatile BYTE IFCONFIG;  ///< Interface Configuration
__xdata __at 0xE602 volatile BYTE PINFLAGSAB;  ///< FIFO FLAGA and FLAGB Assignments
__xdata __at 0xE603 volatile BYTE PINFLAGSCD;  ///< FIFO FLAGC and FLAGD Assignments
__xdata __at 0xE604 volatile BYTE FIFORESET;  ///< Restore FIFOS to default state
__xdata __at 0xE605 volatile BYTE BREAKPT;  ///< Breakpoint
__xdata __at 0xE606 volatile BYTE BPADDRH;  ///< Breakpoint Address H
__xdata __at 0xE607 volatile BYTE BPADDRL;  ///< Breakpoint Address L
__xdata __at 0xE608 volatile BYTE UART230;  ///< 230 Kbaud clock for T0,T1,T2
__xdata __at 0xE609 volatile BYTE FIFOPINPOLAR;  ///< FIFO polarities
__xdata __at 0xE60A volatile BYTE REVID;  ///< Chip Revision
__xdata __at 0xE60B volatile BYTE REVCTL;  ///< Chip Revision Control

// Endpoint Configuration

__xdata __at 0xE610 volatile BYTE EP1OUTCFG;  ///< Endpoint 1-OUT Configuration
__xdata __at 0xE611 volatile BYTE EP1INCFG;  ///< Endpoint 1-IN Configuration
__xdata __at 0xE612 volatile BYTE EP2CFG;  ///< Endpoint 2 Configuration
__xdata __at 0xE613 volatile BYTE EP4CFG;  ///< Endpoint 4 Configuration
__xdata __at 0xE614 volatile BYTE EP6CFG;  ///< Endpoint 6 Configuration
__xdata __at 0xE615 volatile BYTE EP8CFG;  ///< Endpoint 8 Configuration
__xdata __at 0xE618 volatile BYTE EP2FIFOCFG;  ///< Endpoint 2 FIFO configuration
__xdata __at 0xE619 volatile BYTE EP4FIFOCFG;  ///< Endpoint 4 FIFO configuration
__xdata __at 0xE61A volatile BYTE EP6FIFOCFG;  ///< Endpoint 6 FIFO configuration
__xdata __at 0xE61B volatile BYTE EP8FIFOCFG;  ///< Endpoint 8 FIFO configuration
__xdata __at 0xE620 volatile BYTE EP2AUTOINLENH;  ///< Endpoint 2 Packet Length H (IN only)
__xdata __at 0xE621 volatile BYTE EP2AUTOINLENL;  ///< Endpoint 2 Packet Length L (IN only)
__xdata __at 0xE622 volatile BYTE EP4AUTOINLENH;  ///< Endpoint 4 Packet Length H (IN only)
__xdata __at 0xE623 volatile BYTE EP4AUTOINLENL;  ///< Endpoint 4 Packet Length L (IN only)
__xdata __at 0xE624 volatile BYTE EP6AUTOINLENH;  ///< Endpoint 6 Packet Length H (IN only)
__xdata __at 0xE625 volatile BYTE EP6AUTOINLENL;  ///< Endpoint 6 Packet Length L (IN only)
__xdata __at 0xE626 volatile BYTE EP8AUTOINLENH;  ///< Endpoint 8 Packet Length H (IN only)
__xdata __at 0xE627 volatile BYTE EP8AUTOINLENL;  ///< Endpoint 8 Packet Length L (IN only)
__xdata __at 0xE630 volatile BYTE EP2FIFOPFH;  ///< EP2 Programmable Flag trigger H
__xdata __at 0xE631 volatile BYTE EP2FIFOPFL;  ///< EP2 Programmable Flag trigger L
__xdata __at 0xE632 volatile BYTE EP4FIFOPFH;  ///< EP4 Programmable Flag trigger H
__xdata __at 0xE633 volatile BYTE EP4FIFOPFL;  ///< EP4 Programmable Flag trigger L
__xdata __at 0xE634 volatile BYTE EP6FIFOPFH;  ///< EP6 Programmable Flag trigger H
__xdata __at 0xE635 volatile BYTE EP6FIFOPFL;  ///< EP6 Programmable Flag trigger L
__xdata __at 0xE636 volatile BYTE EP8FIFOPFH;  ///< EP8 Programmable Flag trigger H
__xdata __at 0xE637 volatile BYTE EP8FIFOPFL;  ///< EP8 Programmable Flag trigger L
__xdata __at 0xE640 volatile BYTE EP2ISOINPKTS;  ///< EP2 (if ISO) IN Packets per frame (1-3)
__xdata __at 0xE641 volatile BYTE EP4ISOINPKTS;  ///< EP4 (if ISO) IN Packets per frame (1-3)
__xdata __at 0xE642 volatile BYTE EP6ISOINPKTS;  ///< EP6 (if ISO) IN Packets per frame (1-3)
__xdata __at 0xE643 volatile BYTE EP8ISOINPKTS;  ///< EP8 (if ISO) IN Packets per frame (1-3)
__xdata __at 0xE648 volatile BYTE INPKTEND;  ///< Force IN Packet End
__xdata __at 0xE649 volatile BYTE OUTPKTEND;  ///< Force OUT Packet End

// Interrupts

__xdata __at 0xE650 volatile BYTE EP2FIFOIE;  ///< Endpoint 2 Flag Interrupt Enable
__xdata __at 0xE651 volatile BYTE EP2FIFOIRQ;  ///< Endpoint 2 Flag Interrupt Request
__xdata __at 0xE652 volatile BYTE EP4FIFOIE;  ///< Endpoint 4 Flag Interrupt Enable
__xdata __at 0xE653 volatile BYTE EP4FIFOIRQ;  ///< Endpoint 4 Flag Interrupt Request
__xdata __at 0xE654 volatile BYTE EP6FIFOIE;  ///< Endpoint 6 Flag Interrupt Enable
__xdata __at 0xE655 volatile BYTE EP6FIFOIRQ;  ///< Endpoint 6 Flag Interrupt Request
__xdata __at 0xE656 volatile BYTE EP8FIFOIE;  ///< Endpoint 8 Flag Interrupt Enable
__xdata __at 0xE657 volatile BYTE EP8FIFOIRQ;  ///< Endpoint 8 Flag Interrupt Request
__xdata __at 0xE658 volatile BYTE IBNIE;  ///< IN-BULK-NAK Interrupt Enable
__xdata __at 0xE659 volatile BYTE IBNIRQ;  ///< IN-BULK-NAK interrupt Request
__xdata __at 0xE65A volatile BYTE NAKIE;  ///< Endpoint Ping NAK interrupt Enable
__xdata __at 0xE65B volatile BYTE NAKIRQ;  ///< Endpoint Ping NAK interrupt Request
__xdata __at 0xE65C volatile BYTE USBIE;  ///< USB Int Enables
__xdata __at 0xE65D volatile BYTE USBIRQ;  ///< USB Interrupt Requests
__xdata __at 0xE65E volatile BYTE EPIE;  ///< Endpoint Interrupt Enables
__xdata __at 0xE65F volatile BYTE EPIRQ;  ///< Endpoint Interrupt Requests
__xdata __at 0xE660 volatile BYTE GPIFIE;  ///< GPIF Interrupt Enable
__xdata __at 0xE661 volatile BYTE GPIFIRQ;  ///< GPIF Interrupt Request
__xdata __at 0xE662 volatile BYTE USBERRIE;  ///< USB Error Interrupt Enables
__xdata __at 0xE663 volatile BYTE USBERRIRQ;  ///< USB Error Interrupt Requests
__xdata __at 0xE664 volatile BYTE ERRCNTLIM;  ///< USB Error counter and limit
__xdata __at 0xE665 volatile BYTE CLRERRCNT;  ///< Clear Error Counter EC[3..0]
__xdata __at 0xE666 volatile BYTE INT2IVEC;  ///< Interupt 2 (USB) Autovector
__xdata __at 0xE667 volatile BYTE INT4IVEC;  ///< Interupt 4 (FIFOS & GPIF) Autovector
__xdata __at 0xE668 volatile BYTE INTSETUP;  ///< Interrupt 2&4 Setup

// Input/Output

__xdata __at 0xE670 volatile BYTE PORTACFG;  ///< I/O PORTA Alternate Configuration
__xdata __at 0xE671 volatile BYTE PORTCCFG;  ///< I/O PORTC Alternate Configuration
__xdata __at 0xE672 volatile BYTE PORTECFG;  ///< I/O PORTE Alternate Configuration
__xdata __at 0xE678 volatile BYTE I2CS;  ///< Control & Status
__xdata __at 0xE679 volatile BYTE I2DAT;  ///< Data
__xdata __at 0xE67A volatile BYTE I2CTL;  ///< I2C Control
__xdata __at 0xE67B volatile BYTE XAUTODAT1;  ///< Autoptr1 MOVX access
__xdata __at 0xE67C volatile BYTE XAUTODAT2;  ///< Autoptr2 MOVX access

#define EXTAUTODAT1 XAUTODAT1
#define EXTAUTODAT2 XAUTODAT2

// USB Control

__xdata __at 0xE680 volatile BYTE USBCS;  ///< USB Control & Status
__xdata __at 0xE681 volatile BYTE SUSPEND;  ///< Put chip into suspend
__xdata __at 0xE682 volatile BYTE WAKEUPCS;  ///< Wakeup source and polarity
__xdata __at 0xE683 volatile BYTE TOGCTL;  ///< Toggle Control
__xdata __at 0xE684 volatile BYTE USBFRAMEH;  ///< USB Frame count H
__xdata __at 0xE685 volatile BYTE USBFRAMEL;  ///< USB Frame count L
__xdata __at 0xE686 volatile BYTE MICROFRAME;  ///< Microframe count, 0-7
__xdata __at 0xE687 volatile BYTE FNADDR;  ///< USB Function address

// Endpoints

__xdata __at 0xE68A volatile BYTE EP0BCH;  ///< Endpoint 0 Byte Count H
__xdata __at 0xE68B volatile BYTE EP0BCL;  ///< Endpoint 0 Byte Count L
__xdata __at 0xE68D volatile BYTE EP1OUTBC;  ///< Endpoint 1 OUT Byte Count
__xdata __at 0xE68F volatile BYTE EP1INBC;  ///< Endpoint 1 IN Byte Count
__xdata __at 0xE690 volatile BYTE EP2BCH;  ///< Endpoint 2 Byte Count H
__xdata __at 0xE691 volatile BYTE EP2BCL;  ///< Endpoint 2 Byte Count L
__xdata __at 0xE694 volatile BYTE EP4BCH;  ///< Endpoint 4 Byte Count H
__xdata __at 0xE695 volatile BYTE EP4BCL;  ///< Endpoint 4 Byte Count L
__xdata __at 0xE698 volatile BYTE EP6BCH;  ///< Endpoint 6 Byte Count H
__xdata __at 0xE699 volatile BYTE EP6BCL;  ///< Endpoint 6 Byte Count L
__xdata __at 0xE69C volatile BYTE EP8BCH;  ///< Endpoint 8 Byte Count H
__xdata __at 0xE69D volatile BYTE EP8BCL;  ///< Endpoint 8 Byte Count L
__xdata __at 0xE6A0 volatile BYTE EP0CS;  ///< Endpoint  Control and Status
__xdata __at 0xE6A1 volatile BYTE EP1OUTCS;  ///< Endpoint 1 OUT Control and Status
__xdata __at 0xE6A2 volatile BYTE EP1INCS;  ///< Endpoint 1 IN Control and Status
__xdata __at 0xE6A3 volatile BYTE EP2CS;  ///< Endpoint 2 Control and Status
__xdata __at 0xE6A4 volatile BYTE EP4CS;  ///< Endpoint 4 Control and Status
__xdata __at 0xE6A5 volatile BYTE EP6CS;  ///< Endpoint 6 Control and Status
__xdata __at 0xE6A6 volatile BYTE EP8CS;  ///< Endpoint 8 Control and Status
__xdata __at 0xE6A7 volatile BYTE EP2FIFOFLGS;  ///< Endpoint 2 Flags
__xdata __at 0xE6A8 volatile BYTE EP4FIFOFLGS;  ///< Endpoint 4 Flags
__xdata __at 0xE6A9 volatile BYTE EP6FIFOFLGS;  ///< Endpoint 6 Flags
__xdata __at 0xE6AA volatile BYTE EP8FIFOFLGS;  ///< Endpoint 8 Flags
__xdata __at 0xE6AB volatile BYTE EP2FIFOBCH;  ///< EP2 FIFO total byte count H
__xdata __at 0xE6AC volatile BYTE EP2FIFOBCL;  ///< EP2 FIFO total byte count L
__xdata __at 0xE6AD volatile BYTE EP4FIFOBCH;  ///< EP4 FIFO total byte count H
__xdata __at 0xE6AE volatile BYTE EP4FIFOBCL;  ///< EP4 FIFO total byte count L
__xdata __at 0xE6AF volatile BYTE EP6FIFOBCH;  ///< EP6 FIFO total byte count H
__xdata __at 0xE6B0 volatile BYTE EP6FIFOBCL;  ///< EP6 FIFO total byte count L
__xdata __at 0xE6B1 volatile BYTE EP8FIFOBCH;  ///< EP8 FIFO total byte count H
__xdata __at 0xE6B2 volatile BYTE EP8FIFOBCL;  ///< EP8 FIFO total byte count L
__xdata __at 0xE6B3 volatile BYTE SUDPTRH;  ///< Setup Data Pointer high address byte
__xdata __at 0xE6B4 volatile BYTE SUDPTRL;  ///< Setup Data Pointer low address byte
__xdata __at 0xE6B5 volatile BYTE SUDPTRCTL;  ///< Setup Data Pointer Auto Mode
__xdata __at 0xE6B8 volatile BYTE SETUPDAT[8];  ///< 8 bytes of SETUP data

// GPIF

__xdata __at 0xE6C0 volatile BYTE GPIFWFSELECT;  ///< Waveform Selector
__xdata __at 0xE6C1 volatile BYTE GPIFIDLECS;  ///< GPIF Done, GPIF IDLE drive mode
__xdata __at 0xE6C2 volatile BYTE GPIFIDLECTL;  ///< Inactive Bus, CTL states
__xdata __at 0xE6C3 volatile BYTE GPIFCTLCFG;  ///< CTL OUT pin drive
__xdata __at 0xE6C4 volatile BYTE GPIFADRH;  ///< GPIF Address H
__xdata __at 0xE6C5 volatile BYTE GPIFADRL;  ///< GPIF Address L

__xdata __at 0xE6CE volatile BYTE GPIFTCB3;  ///< GPIF Transaction Count Byte 3
__xdata __at 0xE6CF volatile BYTE GPIFTCB2;  ///< GPIF Transaction Count Byte 2
__xdata __at 0xE6D0 volatile BYTE GPIFTCB1;  ///< GPIF Transaction Count Byte 1
__xdata __at 0xE6D1 volatile BYTE GPIFTCB0;  ///< GPIF Transaction Count Byte 0

__xdata __at 0xE6D2 volatile BYTE EP2GPIFFLGSEL;  ///< EP2 GPIF Flag select
__xdata __at 0xE6D3 volatile BYTE EP2GPIFPFSTOP;  ///< Stop GPIF EP2 transaction on prog. flag
__xdata __at 0xE6D4 volatile BYTE EP2GPIFTRIG;  ///< EP2 FIFO Trigger
__xdata __at 0xE6DA volatile BYTE EP4GPIFFLGSEL;  ///< EP4 GPIF Flag select
__xdata __at 0xE6DB volatile BYTE EP4GPIFPFSTOP;  ///< Stop GPIF EP4 transaction on prog. flag
__xdata __at 0xE6DC volatile BYTE EP4GPIFTRIG;  ///< EP4 FIFO Trigger
__xdata __at 0xE6E2 volatile BYTE EP6GPIFFLGSEL;  ///< EP6 GPIF Flag select
__xdata __at 0xE6E3 volatile BYTE EP6GPIFPFSTOP;  ///< Stop GPIF EP6 transaction on prog. flag
__xdata __at 0xE6E4 volatile BYTE EP6GPIFTRIG;  ///< EP6 FIFO Trigger
__xdata __at 0xE6EA volatile BYTE EP8GPIFFLGSEL;  ///< EP8 GPIF Flag select
__xdata __at 0xE6EB volatile BYTE EP8GPIFPFSTOP;  ///< Stop GPIF EP8 transaction on prog. flag
__xdata __at 0xE6EC volatile BYTE EP8GPIFTRIG;  ///< EP8 FIFO Trigger
__xdata __at 0xE6F0 volatile BYTE XGPIFSGLDATH;  ///< GPIF Data H (16-bit mode only)
__xdata __at 0xE6F1 volatile BYTE XGPIFSGLDATLX;  ///< Read/Write GPIF Data L & trigger transac
__xdata __at 0xE6F2 volatile BYTE XGPIFSGLDATLNOX;  ///< Read GPIF Data L, no transac trigger
__xdata __at 0xE6F3 volatile BYTE GPIFREADYCFG;  ///< Internal RDY,Sync/Async, RDY5CFG
__xdata __at 0xE6F4 volatile BYTE GPIFREADYSTAT;  ///< RDY pin states
__xdata __at 0xE6F5 volatile BYTE GPIFABORT;  ///< Abort GPIF cycles

// UDMA

__xdata __at 0xE6C6 volatile BYTE FLOWSTATE; ///<Defines GPIF flow state
__xdata __at 0xE6C7 volatile BYTE FLOWLOGIC; ///<Defines flow/hold decision criteria
__xdata __at 0xE6C8 volatile BYTE FLOWEQ0CTL; ///<CTL states during active flow state
__xdata __at 0xE6C9 volatile BYTE FLOWEQ1CTL; ///<CTL states during hold flow state
__xdata __at 0xE6CA volatile BYTE FLOWHOLDOFF;
__xdata __at 0xE6CB volatile BYTE FLOWSTB; ///<CTL/RDY Signal to use as master data strobe 
__xdata __at 0xE6CC volatile BYTE FLOWSTBEDGE; ///<Defines active master strobe edge
__xdata __at 0xE6CD volatile BYTE FLOWSTBHPERIOD; ///<Half Period of output master strobe
__xdata __at 0xE60C volatile BYTE GPIFHOLDAMOUNT; ///<Data delay shift 
__xdata __at 0xE67D volatile BYTE UDMACRCH; ///<CRC Upper byte
__xdata __at 0xE67E volatile BYTE UDMACRCL; ///<CRC Lower byte
__xdata __at 0xE67F volatile BYTE UDMACRCQUAL; ///<UDMA In only, host terminated use only

// Endpoint Buffers

__xdata __at 0xE740 volatile BYTE EP0BUF[64];  ///< EP0 IN-OUT buffer
__xdata __at 0xE780 volatile BYTE EP1OUTBUF[64];  ///< EP1-OUT buffer
__xdata __at 0xE7C0 volatile BYTE EP1INBUF[64];  ///< EP1-IN buffer
__xdata __at 0xF000 volatile BYTE EP2FIFOBUF[1024];  ///< 512/1024-byte EP2 buffer (IN or OUT)
__xdata __at 0xF400 volatile BYTE EP4FIFOBUF[1024];  ///< 512 byte EP4 buffer (IN or OUT)
__xdata __at 0xF800 volatile BYTE EP6FIFOBUF[1024];  ///< 512/1024-byte EP6 buffer (IN or OUT)
__xdata __at 0xFC00 volatile BYTE EP8FIFOBUF[1024];  ///< 512 byte EP8 buffer (IN or OUT)

// Error Correction Code (ECC) Registers (FX2LP/FX1 only)

__xdata __at 0xE628 volatile BYTE ECCCFG;  ///< ECC Configuration
__xdata __at 0xE629 volatile BYTE ECCRESET;  ///< ECC Reset
__xdata __at 0xE62A volatile BYTE ECC1B0;  ///< ECC1 Byte 0
__xdata __at 0xE62B volatile BYTE ECC1B1;  ///< ECC1 Byte 1
__xdata __at 0xE62C volatile BYTE ECC1B2;  ///< ECC1 Byte 2
__xdata __at 0xE62D volatile BYTE ECC2B0;  ///< ECC2 Byte 0
__xdata __at 0xE62E volatile BYTE ECC2B1;  ///< ECC2 Byte 1
__xdata __at 0xE62F volatile BYTE ECC2B2;  ///< ECC2 Byte 2

// Feature Registers  (FX2LP/FX1 only)
__xdata __at 0xE50D volatile BYTE GPCR2;  ///< Chip Features

/**
 * SFRs below
 *  According to TRM 15.2, only rows 0 and 8 of the SFRs are bit addressible
 *  row 0: IOA, IOB, IOC, IOD, SCON1, PSW, ACC, B
 *  row 8: TCON, SCON0, IE, IP, T2CON, IECON, EIE, EIP
 *
 *  All others have to move a byte to the SRF address
 **/

__sfr __at 0x80 IOA;
         /*  IOA  */
         __sbit __at 0x80 + 0 PA0;
         __sbit __at 0x80 + 1 PA1;
         __sbit __at 0x80 + 2 PA2;
         __sbit __at 0x80 + 3 PA3;
         __sbit __at 0x80 + 4 PA4;
         __sbit __at 0x80 + 5 PA5;
         __sbit __at 0x80 + 6 PA6;
         __sbit __at 0x80 + 7 PA7;
__sfr __at 0x81 SP;
__sfr __at 0x82 DPL;
__sfr __at 0x83 DPH;
__sfr __at 0x84 DPL1;
__sfr __at 0x85 DPH1;
__sfr __at 0x86 DPS;
__sfr __at 0x87 PCON;
__sfr __at 0x88 TCON;
         /*  TCON  */
         __sbit __at 0x88+0 IT0;
         __sbit __at 0x88+1 IE0;
         __sbit __at 0x88+2 IT1;
         __sbit __at 0x88+3 IE1;
         __sbit __at 0x88+4 TR0;
         __sbit __at 0x88+5 TF0;
         __sbit __at 0x88+6 TR1;
         __sbit __at 0x88+7 TF1;
__sfr __at 0x89 TMOD;
__sfr __at 0x8A TL0;
__sfr __at 0x8B TL1;
__sfr __at 0x8C TH0;
__sfr __at 0x8D TH1;
__sfr __at 0x8E CKCON;
__sfr __at 0x90 IOB;
         /*  IOB  */
         __sbit __at 0x90 + 0 PB0;
         __sbit __at 0x90 + 1 PB1;
         __sbit __at 0x90 + 2 PB2;
         __sbit __at 0x90 + 3 PB3;
         __sbit __at 0x90 + 4 PB4;
         __sbit __at 0x90 + 5 PB5;
         __sbit __at 0x90 + 6 PB6;
         __sbit __at 0x90 + 7 PB7;
__sfr __at 0x91 EXIF;
         
//__sfr __at 0x92 MPAGE;
__sfr __at 0x92 _XPAGE; // same as MPAGE for pdata __sfr access w/ sdcc
__sfr __at 0x98 SCON0;
         /*  SCON0  */
         __sbit __at 0x98+0 RI;
         __sbit __at 0x98+1 TI;
         __sbit __at 0x98+2 RB8;
         __sbit __at 0x98+3 TB8;
         __sbit __at 0x98+4 REN;
         __sbit __at 0x98+5 SM2;
         __sbit __at 0x98+6 SM1;
         __sbit __at 0x98+7 SM0;
__sfr __at 0x99 SBUF0;

__sfr __at 0x9A AUTOPTRH1; 
__sfr __at 0x9B AUTOPTRL1; 
__sfr __at 0x9D AUTOPTRH2;
__sfr __at 0x9E AUTOPTRL2; 

__sfr __at 0xA0 IOC;
         /*  IOC  */
         __sbit __at 0xA0 + 0 PC0;
         __sbit __at 0xA0 + 1 PC1;
         __sbit __at 0xA0 + 2 PC2;
         __sbit __at 0xA0 + 3 PC3;
         __sbit __at 0xA0 + 4 PC4;
         __sbit __at 0xA0 + 5 PC5;
         __sbit __at 0xA0 + 6 PC6;
         __sbit __at 0xA0 + 7 PC7;
__sfr __at 0xA1 INT2CLR;
__sfr __at 0xA2 INT4CLR;

__sfr __at 0xA8 IE;
         /*  IE  */
         __sbit __at 0xA8+0 EX0;
         __sbit __at 0xA8+1 ET0;
         __sbit __at 0xA8+2 EX1;
         __sbit __at 0xA8+3 ET1;
         __sbit __at 0xA8+4 ES0;
         __sbit __at 0xA8+5 ET2;
         __sbit __at 0xA8+6 ES1;
         __sbit __at 0xA8+7 EA;

__sfr __at 0xAA EP2468STAT;
__sfr __at 0xAB EP24FIFOFLGS;
__sfr __at 0xAC EP68FIFOFLGS;
__sfr __at 0xAF AUTOPTRSETUP;
__sfr __at 0xB0 IOD;
         /*  IOD  */
         __sbit __at 0xB0 + 0 PD0;
         __sbit __at 0xB0 + 1 PD1;
         __sbit __at 0xB0 + 2 PD2;
         __sbit __at 0xB0 + 3 PD3;
         __sbit __at 0xB0 + 4 PD4;
         __sbit __at 0xB0 + 5 PD5;
         __sbit __at 0xB0 + 6 PD6;
         __sbit __at 0xB0 + 7 PD7;
__sfr __at 0xB1 IOE;
__sfr __at 0xB2 OEA;
__sfr __at 0xB3 OEB;
__sfr __at 0xB4 OEC;
__sfr __at 0xB5 OED;
__sfr __at 0xB6 OEE;

__sfr __at 0xB8 IP;
         /*  IP  */
         __sbit __at 0xB8+0 PX0;
         __sbit __at 0xB8+1 PT0;
         __sbit __at 0xB8+2 PX1;
         __sbit __at 0xB8+3 PT1;
         __sbit __at 0xB8+4 PS0;
         __sbit __at 0xB8+5 PT2;
         __sbit __at 0xB8+6 PS1;

__sfr __at 0xBA EP01STAT;
__sfr __at 0xBB GPIFTRIG;

__sfr __at 0xBD GPIFSGLDATH;
__sfr __at 0xBE GPIFSGLDATLX;
__sfr __at 0xBF GPIFSGLDATLNOX;

__sfr __at 0xC0 SCON1;
         /*  SCON1  */
         __sbit __at 0xC0+0 RI1;
         __sbit __at 0xC0+1 TI1;
         __sbit __at 0xC0+2 RB81;
         __sbit __at 0xC0+3 TB81;
         __sbit __at 0xC0+4 REN1;
         __sbit __at 0xC0+5 SM21;
         __sbit __at 0xC0+6 SM11;
         __sbit __at 0xC0+7 SM01;
__sfr __at 0xC1 SBUF1;
__sfr __at 0xC8 T2CON;
         /*  T2CON  */
         __sbit __at 0xC8+0 CP_RL2;
         __sbit __at 0xC8+1 C_T2;
         __sbit __at 0xC8+2 TR2;
         __sbit __at 0xC8+3 EXEN2;
         __sbit __at 0xC8+4 TCLK;
         __sbit __at 0xC8+5 RCLK;
         __sbit __at 0xC8+6 EXF2;
         __sbit __at 0xC8+7 TF2;
__sfr __at 0xCA RCAP2L;
__sfr __at 0xCB RCAP2H;
__sfr __at 0xCC TL2;
__sfr __at 0xCD TH2;
__sfr __at 0xD0 PSW;
         /*  PSW  */
         __sbit __at 0xD0+0 P;
         __sbit __at 0xD0+1 FL;
         __sbit __at 0xD0+2 OV;
         __sbit __at 0xD0+3 RS0;
         __sbit __at 0xD0+4 RS1;
         __sbit __at 0xD0+5 F0;
         __sbit __at 0xD0+6 AC;
         __sbit __at 0xD0+7 CY;
__sfr __at 0xD8 EICON; // Was WDCON in DS80C320; Bit Values differ from Reg320
         /*  EICON  */
         __sbit __at 0xD8+3 INT6;
         __sbit __at 0xD8+4 RESI;
         __sbit __at 0xD8+5 ERESI;
         __sbit __at 0xD8+7 SMOD1;
__sfr __at 0xE0 ACC;
__sfr __at 0xE8 EIE; // EIE Bit Values differ from Reg320
         /*  EIE  */
         __sbit __at 0xE8+0 EUSB;
         __sbit __at 0xE8+1 EI2C;
         __sbit __at 0xE8+2 EIEX4;
         __sbit __at 0xE8+3 EIEX5;
         __sbit __at 0xE8+4 EIEX6;
__sfr __at 0xF0 B;
__sfr __at 0xF8 EIP; // EIP Bit Values differ from Reg320
         /*  EIP  */
         __sbit __at 0xF8+0 PUSB;
         __sbit __at 0xF8+1 PI2C;
         __sbit __at 0xF8+2 EIPX4;
         __sbit __at 0xF8+3 EIPX5;
         __sbit __at 0xF8+4 EIPX6;


/* CPU Control & Status Register (CPUCS) */
#define bmPRTCSTB    bmBIT5
#define bmCLKSPD     (bmBIT4 | bmBIT3)
#define bmCLKSPD1    bmBIT4
#define bmCLKSPD0    bmBIT3
#define bmCLKINV     bmBIT2
#define bmCLKOE      bmBIT1
#define bm8051RES    bmBIT0
/* Port Alternate Configuration Registers */
/* Port A (PORTACFG) */
#define bmFLAGD      bmBIT7
#define bmSLCS       bmBIT6
#define bmINT1       bmBIT1
#define bmINT0       bmBIT0
/* Port C (PORTCCFG) */
#define bmGPIFA7     bmBIT7
#define bmGPIFA6     bmBIT6
#define bmGPIFA5     bmBIT5
#define bmGPIFA4     bmBIT4
#define bmGPIFA3     bmBIT3
#define bmGPIFA2     bmBIT2
#define bmGPIFA1     bmBIT1
#define bmGPIFA0     bmBIT0
/* Port E (PORTECFG) */
#define bmGPIFA8     bmBIT7
#define bmT2EX       bmBIT6
#define bmINT6       bmBIT5
#define bmRXD1OUT    bmBIT4
#define bmRXD0OUT    bmBIT3
#define bmT2OUT      bmBIT2
#define bmT1OUT      bmBIT1
#define bmT0OUT      bmBIT0

/* I2C Control & Status Register (I2CS) */
#define bmSTART      bmBIT7
#define bmSTOP       bmBIT6
#define bmLASTRD     bmBIT5
#define bmID         (bmBIT4 | bmBIT3)
#define bmBERR       bmBIT2
#define bmACK        bmBIT1
#define bmDONE       bmBIT0
/* I2C Control Register (I2CTL) */
#define bmSTOPIE     bmBIT1
#define bm400KHZ     bmBIT0
/* Interrupt 2 (USB) Autovector Register (INT2IVEC) */
#define bmIV4        bmBIT6
#define bmIV3        bmBIT5
#define bmIV2        bmBIT4
#define bmIV1        bmBIT3
#define bmIV0        bmBIT2
/* USB Interrupt Request & Enable Registers (USBIE/USBIRQ) */
#define bmEP0ACK     bmBIT6
#define bmHSGRANT    bmBIT5
#define bmURES       bmBIT4
#define bmSUSP       bmBIT3
#define bmSUTOK      bmBIT2
#define bmSOF        bmBIT1
#define bmSUDAV      bmBIT0
/* USBERRIE/IRQ */
#define bmERRLIMIT  bmBIT0
#define bmISOEP2    bmBIT4
#define bmISOEP4    bmBIT5
#define bmISOEP6    bmBIT6
#define bmISOEP8    bmBIT7

/* Endpoint Interrupt & Enable Registers (EPIE/EPIRQ) */
#define bmEP0IN     bmBIT0
#define bmEP0OUT    bmBIT1
#define bmEP1IN     bmBIT2
#define bmEP1OUT    bmBIT3
#define bmEP2       bmBIT4
#define bmEP4       bmBIT5
#define bmEP6       bmBIT6
#define bmEP8       bmBIT7
/* Breakpoint register (BREAKPT) */
#define bmBREAK      bmBIT3
#define bmBPPULSE    bmBIT2
#define bmBPEN       bmBIT1
/* Interrupt 2 & 4 Setup (INTSETUP) */
#define bmAV2EN      bmBIT3
#define INT4IN       bmBIT1
#define bmAV4EN      bmBIT0
/* USB Control & Status Register (USBCS) */
#define bmHSM        bmBIT7
#define bmDISCON     bmBIT3
#define bmNOSYNSOF   bmBIT2
#define bmRENUM      bmBIT1
#define bmSIGRESUME  bmBIT0
/* Wakeup Control and Status Register (WAKEUPCS) */
#define bmWU2        bmBIT7
#define bmWU         bmBIT6
#define bmWU2POL     bmBIT5
#define bmWUPOL      bmBIT4
#define bmDPEN       bmBIT2
#define bmWU2EN      bmBIT1
#define bmWUEN       bmBIT0
/* End Point 0 Control & Status Register (EP0CS) */
#define bmHSNAK      bmBIT7
/* End Point 0-1 Control & Status Registers (EP0CS/EP1OUTCS/EP1INCS) */
#define bmEPBUSY     bmBIT1
#define bmEPSTALL    bmBIT0
/* End Point 2-8 Control & Status Registers (EP2CS/EP4CS/EP6CS/EP8CS) */
#define bmNPAK       (bmBIT6 | bmBIT5 | bmBIT4)
#define bmEPFULL     bmBIT3
#define bmEPEMPTY    bmBIT2
/* Endpoint Status (EP2468STAT) SFR bits */
#define bmEP8FULL    bmBIT7
#define bmEP8EMPTY   bmBIT6
#define bmEP6FULL    bmBIT5
#define bmEP6EMPTY   bmBIT4
#define bmEP4FULL    bmBIT3
#define bmEP4EMPTY   bmBIT2
#define bmEP2FULL    bmBIT1
#define bmEP2EMPTY   bmBIT0
/* Endpoint Config (EP[2468]CFG) */
#define bmVALID     bmBIT7
#define bmDIR       bmBIT6
#define bmTYPE      (bmBIT4|bmBIT5)
#define bmTYPE1     bmBIT5
#define bmTYPE0     bmBIT4
#define bmSIZE      bmBIT3
/* Endpoint Config (EP[24]CFG) */
#define bmBUF       (bmBIT0|bmBIT1)
#define bmBUF1      bmBIT1
#define bmBUF0      bmBIT0
/* SETUP Data Pointer Auto Mode (SUDPTRCTL) */
#define bmSDPAUTO    bmBIT0
/* Endpoint Data Toggle Control (TOGCTL) */
#define bmQUERYTOGGLE  bmBIT7
#define bmSETTOGGLE    bmBIT6
#define bmRESETTOGGLE  bmBIT5
#define bmTOGCTLEPMASK bmBIT3 | bmBIT2 | bmBIT1 | bmBIT0
/* IBN (In Bulk Nak) enable and request bits (IBNIE/IBNIRQ) */
#define bmEP8IBN     bmBIT5
#define bmEP6IBN     bmBIT4
#define bmEP4IBN     bmBIT3
#define bmEP2IBN     bmBIT2
#define bmEP1IBN     bmBIT1
#define bmEP0IBN     bmBIT0

/* PING-NAK enable and request bits (NAKIE/NAKIRQ) */
#define bmEP8PING     bmBIT7
#define bmEP6PING     bmBIT6
#define bmEP4PING     bmBIT5
#define bmEP2PING     bmBIT4
#define bmEP1PING     bmBIT3
#define bmEP0PING     bmBIT2
#define bmIBN         bmBIT0

/* Interface Configuration bits (IFCONFIG) */
#define bmIFCLKSRC    bmBIT7
#define bm3048MHZ     bmBIT6
#define bmIFCLKOE     bmBIT5
#define bmIFCLKPOL    bmBIT4
#define bmASYNC       bmBIT3
#define bmGSTATE      bmBIT2
#define bmIFCFG1      bmBIT1
#define bmIFCFG0      bmBIT0
#define bmIFCFGMASK   (bmIFCFG0 | bmIFCFG1)
#define bmIFGPIF      bmIFCFG1

/* EP 2468 FIFO Configuration bits (EP2FIFOCFG,EP4FIFOCFG,EP6FIFOCFG,EP8FIFOCFG) */
#define bmINFM       bmBIT6
#define bmOEP        bmBIT5
#define bmAUTOOUT    bmBIT4
#define bmAUTOIN     bmBIT3
#define bmZEROLENIN  bmBIT2
#define bmWORDWIDE   bmBIT0

/* Chip Revision Control Bits (REVCTL) - used to ebable/disable revision specidic
   features */ 
#define bmNOAUTOARM    bmBIT1
#define bmSKIPCOMMIT   bmBIT0

/* Fifo Reset bits (FIFORESET) */
#define bmNAKALL       bmBIT7

/* Chip Feature Register (GPCR2) */
#define bmFULLSPEEDONLY    bmBIT4

/* EP 01 status (EP01STAT) */
#define bmEP1INBSY      bmBIT2
#define bmEP1OUTBSY     bmBIT1
#define bmEP0BSY        bmBIT0

#endif   /* FX2REGS_H */

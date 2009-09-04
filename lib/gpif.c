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
#include <delay.h>

#include <gpif.h>

#define SYNCDELAY() SYNCDELAY4

void gpif_init( BYTE* wavedata, BYTE* initdata ) {
    
    BYTE i;
 
  // Registers which require a synchronization delay, see section 15.14
  // FIFORESET        FIFOPINPOLAR
  // INPKTEND         OUTPKTEND
  // EPxBCH:L         REVCTL
  // GPIFTCB3         GPIFTCB2
  // GPIFTCB1         GPIFTCB0
  // EPxFIFOPFH:L     EPxAUTOINLENH:L
  // EPxFIFOCFG       EPxGPIFFLGSEL
  // PINFLAGSxx       EPxFIFOIRQ
  // EPxFIFOIE        GPIFIRQ
  // GPIFIE           GPIFADRH:L
  // UDMACRCH:L       EPxGPIFTRIG
  // GPIFTRIG
  
  // Note: The pre-REVE EPxGPIFTCH/L register are affected, as well...
  //      ...these have been replaced by GPIFTC[B3:B0] registers
 
  // 8051 doesn't have access to waveform memories 'til
  // the part is in GPIF mode.
 
  // IFCLKSRC=1   , FIFOs executes on internal clk source
  // xMHz=1       , 48MHz internal clk rate
  // IFCLKOE=0    , Don't drive IFCLK pin signal at 48MHz
  // IFCLKPOL=0   , Don't invert IFCLK pin signal from internal clk
  // ASYNC=1      , master samples asynchronous
  // GSTATE=1     , Drive GPIF states out on PORTE[2:0], debug WF
  // IFCFG[1:0]=10, FX2 in GPIF master mode  IFCONFIG
  IFCONFIG &= ~0x03; // turn off IFCFG[1:0]
  IFCONFIG |= 0x02; // set's IFCFG[1:0] to 10 to put in GPIF master mode.
  
 
  GPIFABORT = 0xFF;  // abort any waveforms pending
 
  GPIFREADYCFG = initdata[ 0 ];
  GPIFCTLCFG = initdata[ 1 ];
  GPIFIDLECS = initdata[ 2 ];
  GPIFIDLECTL = initdata[ 3 ];
  GPIFWFSELECT = initdata[ 5 ];
  GPIFREADYSTAT = initdata[ 6 ];
 
  // use dual autopointer feature... 
  AUTOPTRSETUP = 0x07;          // inc both pointers, 
                                // ...warning: this introduces pdata hole(s)
                                // ...at E67B (XAUTODAT1) and E67C (XAUTODAT2)
  
  // source
  AUTOPTRH1 = MSB( (WORD)wavedata );
  AUTOPTRL1 = LSB( (WORD)wavedata );
  
  // destination
  AUTOPTRH2 = 0xE4;
  AUTOPTRL2 = 0x00;
 
  // transfer
  for ( i = 0x00; i < 128; i++ )
  {
    EXTAUTODAT2 = EXTAUTODAT1;
  }
 
// Configure GPIF Address pins, output initial value,
// these instructions don't do anything on the
// smaller chips (e.g., 56 pin model only has ports a,b,d)
  PORTCCFG = 0xFF;    // [7:0] as alt. func. GPIFADR[7:0]
  OEC = 0xFF;         // and as outputs
  PORTECFG |= 0x80;   // [8] as alt. func. GPIFADR[8]
  OEE |= 0x80;        // and as output
 
// ...OR... tri-state GPIFADR[8:0] pins
//  PORTCCFG = 0x00;  // [7:0] as port I/O
//  OEC = 0x00;       // and as inputs
//  PORTECFG &= 0x7F; // [8] as port I/O
//  OEE &= 0x7F;      // and as input
 
// GPIF address pins update when GPIFADRH/L written
  SYNCDELAY();                    // 
  GPIFADRH = 0x00;    // bits[7:1] always 0
  SYNCDELAY();                    // 
  GPIFADRL = 0x00;    // point to PERIPHERAL address 0x0000

// set the initial flowstates to be all 0 in case flow states are not used

  FLOWSTATE = 0;
  FLOWLOGIC = 0;
  FLOWEQ0CTL = 0;
  FLOWEQ1CTL = 0;
  FLOWHOLDOFF = 0;
  FLOWSTB = 0;
  FLOWSTBEDGE = 0;
  FLOWSTBHPERIOD = 0;
}

void gpif_setflowstate( BYTE* flowstates, BYTE bank) {
  BYTE base = 9*bank;
  FLOWSTATE = flowstates[ base ];
  FLOWLOGIC = flowstates[ base+1 ];
  FLOWEQ0CTL = flowstates[ base+2 ];
  FLOWEQ1CTL = flowstates[ base+3 ];
  FLOWHOLDOFF = flowstates[ base+4 ];
  FLOWSTB = flowstates[ base+5 ];
  FLOWSTBEDGE = flowstates[ base+6 ];
  FLOWSTBHPERIOD = flowstates[ base+7 ];
}

void gpif_set_tc32(DWORD tc) {
    GPIFTCB3 = MSB(MSW(tc));
    SYNCDELAY();
    GPIFTCB2 = LSB(MSW(tc));
    SYNCDELAY();
    GPIFTCB1 = MSB(LSW(tc));
    SYNCDELAY();
    GPIFTCB0 = LSB(LSW(tc));
}
void gpif_set_tc16(WORD tc) {
    GPIFTCB1= MSB(tc);
    SYNCDELAY();
    GPIFTCB0= LSB(tc);
}


void gpif_single_read16( WORD* res, WORD len ){
    BYTE c;    
    while (!(GPIFTRIG & 0x80)); // wait done
    // dummy read to trigger real read
    res[0] = XGPIFSGLDATLX;
    for (c=0;c<len;++c) {
     while ( !(GPIFTRIG & 0x80) ); // wait done
     // real read
     res[c] = GPIFSGLDATH << 8;
     // whether or not to do another transfer is controlled by GPIFSGLDATLNOX or ..DATLX
     res[c] |= c==len-1 ? GPIFSGLDATLNOX : GPIFSGLDATLX ;
    }
}

void gpif_single_write16( WORD* dat, WORD len) {
   BYTE c;
   for (c=0;c<len;++c) {
    while (!(GPIFTRIG & 0x80) );
    XGPIFSGLDATH = MSB(dat[c]);
    XGPIFSGLDATLX = LSB(dat[c]);
   }
}

void gpif_fifo_read ( GPIF_EP_NUM ep_num ) {
    while ( !(GPIFTRIG & 0x80 ) ); // wait until things are finished
    GPIFTRIG = GPIFTRGRD | ep_num;
}

void gpif_fifo_write ( GPIF_EP_NUM ep_num ) {
    while ( !(GPIFTRIG & 0x80) ); // wait until things are finished
    GPIFTRIG = ep_num; // R/W=0, E[1:0] = ep_num
}

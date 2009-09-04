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
 * These functions do the same thing that the Cypress gpif designer expored c file does.
 * Instead of including their file directly in your project, you include just the
 * generated waveform data.  The gpif2dat script in the utils folder will export your
 * waveform data to a file that can be included in your project.
 * */

#ifndef GPIF_H
#define GPIF_H

#include "fx2types.h"

#define GPIFDONE (GPIFTRIG&0x80)
#define GPIFTC16 (MAKEWORD(GPIFTCB1,GPIFTCB0))
#define GPIFTC32 (MAKEDWORD(MAKEWORD(GPIFTCB3,GPIFTCB2),MAKEWORD(GPIFTCB1,GPIFTCB0)))


/**
 * Gpif designer generates a c file with waveform data.
 * Copy the WaveData[128] array
 * and the InitData[7] to your code somewhere
 * Then this function is pretty much the reset of the generated
 * code but ported to sdcc.
 *
 * uses syncdelay of 4 which might not be long enough if peripheral
 * runs slower than 30mhz.  May not affect anything.
 *
 * IFCONFIG is set with IFCFG[1:0] = 10 for GPIF master but you still
 * have to set the ifclk, polarity, and the rest of the bits
 **/

void gpif_init( BYTE* waveform, BYTE* initdata );

/**
 * Uses the correct bytes from your flowstates array.
 * This may or may not be needed depending on whether
 * your waveform data uses flowstates.  If you don't
 * know if you need them or not, you probably don't.
 *
 * flowstates should have 36 elements.
 * bank should be 0-3
 **/
void gpif_setflowstate( BYTE* flowstates, BYTE bank);



//! These defines/functions pretty much out of the TRM 10.4
#define GPIFTRGWR 0
#define GPIFTRGRD 4
typedef enum {
    GPIF_EP2 = 0,
    GPIF_EP4 = 1,
    GPIF_EP6 = 2,
    GPIF_EP8 = 3
} GPIF_EP_NUM;

/**
 * \brief Simple function to help set the transaction count for gpif
 * transactions.
 * \param tc 32 bit Transaction Count
 **/
void gpif_set_tc32(DWORD tc);
/**
 * \brief Simple function to set transaction count for gpif transactions.
 * \param tc 16 bit Transaction Count
 **/
void gpif_set_tc16(WORD tc);


/**
 * Use the gpif to read a single word at a time.
 * Read len words and store in res
 *
 * At least one EPxFIFOCFG has to have wordwide=1 or this
 * functions won't transfer both bytes.
 **/

void gpif_single_read16( WORD* res , WORD len);

/**
 * Use the gpif to write a single word at a time.
 * Write len words from data
 *
 * At leat one EPxFIFOCFG has to have wordwide=1 or this
 * function won't transfer both bytes.
 **/
void gpif_single_write16( WORD* data, WORD len);

void gpif_fifo_read ( GPIF_EP_NUM ep_num );

void gpif_fifo_write( GPIF_EP_NUM ep_num );

#endif

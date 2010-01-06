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

/** \file i2c.h 
 *  Utilities for reading and writing to i2c devices and as eeproms.
 **/

#ifndef I2C_H
#define I2C_H

#include "fx2types.h"

/**
 * i2c_write and i2c_read set this to FALSE at the beginning of a 
 * transaction.  If for some reason, the read/write is taking too
 * long or not returning, firmware can set this to TRUE to cause the
 * routine to abort.  (Usually done via an interrupt).
 **/
extern volatile xdata BOOL cancel_i2c_trans;

/**
 * \brief write data to i2c bus.
 *
 *  Writes data from addr buffer 1st, then data buffer. 
 *  Either buffer can be NULL (as long as you set lenN to 0).
 *  
 *  Two buffers allows writing data all in one i2c write command without
 *  having to write a hardware address and a data byte with each 
 *  i2c transaction.
 *
 * \param addr i2c address
 * \param len1 length of addr data
 * \param addr_buf addr data
 * \param len2 length of data
 * \param data_buf data bytes
 **/
BOOL i2c_write ( BYTE addr, WORD len1, BYTE* addr_buf, WORD len2, BYTE* data_buf );

/**
 * \brief read data on the i2c bus.
 *
 * \param addr i2c address
 * \param len number of bytes to read
 * \param buf buffer to store data
 **/
BOOL i2c_read ( BYTE addr, WORD len, BYTE* buf);

/**
 * \brief read data from an attached eeprom.
 *
 * Writes the address of the data to read then reads len bytes into buf.
 * This function checks the I2CS register to determine if a one or two
 * byte address eepom was detected on the i2c bus.  Reading from proms
 * at non-standard addresses my require using the i2c_read/write commands
 * explicitly.
 *
 * \param prom_addr eeprom i2c address
 * \param addr address of bytes to start reading
 * \param len number of bytes to read
 * \param buf data buffer
 **/
BOOL eeprom_read( BYTE prom_addr, WORD addr, WORD len, BYTE* buf);

/**
 * \brief write data to the eeprom
 *
 * This function checks the I2CS register to determin if a one or two
 * two byte eeprom is detected.  If the prom is not detected at boot time
 * or is connected to alternate addresses, the i2c_read/write commands should
 * be used explicitly insread of using this function.
 *
 * For each byte in buf, the address is written and then the data byte. Many 
 * proms support writing multiple bytes at the same time.  For these, it is
 * also better to use i2c_read/write explicitly.  This function is rather slow
 * but is effective.
 *
 * \param prom_addr eeprom i2c address
 * \param addr address of bytes to start writing
 * \param len number of bytes to write
 * \param buf data buffer
 **/
BOOL eeprom_write( BYTE prom_addr, WORD addr, WORD len, BYTE* buf);

#endif

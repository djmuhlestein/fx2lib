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

BOOL i2c_read ( BYTE addr, WORD len, BYTE* buf);

BOOL eeprom_read( BYTE prom_addr, WORD addr, WORD len, BYTE* buf);

BOOL eeprom_write( BYTE prom_addr, WORD addr, WORD len, BYTE* buf);

#endif

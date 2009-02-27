// Copyright (C) 2008 Ubixum, Inc. 
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

BOOL i2c_write ( BYTE addr, WORD len, BYTE* buf);

BOOL i2c_read ( BYTE addr, WORD len, BYTE* buf);

void eeprom_read( BYTE prom_addr, WORD addr, WORD len, BYTE* buf);

void eeprom_write( BYTE prom_addr, WORD addr, WORD len, BYTE* buf);

#endif

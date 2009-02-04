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

/*! \file 
 *  Macros for simple common tasks in fx2 firmware.
 * */

#ifndef FX2MACROS_H
#define FX2MACROS_H

#include "fx2regs.h"
#include "fx2types.h"

#define MSB(addr) (BYTE)((addr >> 8) & 0xff)
#define LSB(addr) (BYTE)(addr & 0xff)
#define MAKEWORD(msb,lsb) (((WORD)msb << 8) | lsb)

#define MSW(dword) (WORD)((dword >> 16) & 0xffff)
#define LSW(dword) (WORD)(dword & 0xffff)
#define MAKEDWORD(msw,lsw) (((DWORD)msw << 16) | lsw)

// clock stuff

typedef enum { CLK_12M =0, CLK_24M, CLK_48M} CLK_SPD;
#define CPUFREQ (CLK_SPD)((CPUCS & bmCLKSPD) >> 3)
#define SETCPUFREQ(SPD) CPUCS = (CPUCS & ~bmCLKSPD) | (SPD << 3)

#define XTAL (CPUFREQ==CLK_12M ? 12000000L :\
              CPUFREQ==CLK_24M ? 24000000L : 48000000L)


// i2c stuff
#define I2CFREQ ((I2CTL & bm400KHZ) ? 400000L : 100000L)


// endpoints 
#define IFFREQ (IFCONFIG & bm3048MHZ ? 48000000L : 30000000L)
#define SETIF30MHZ() IFCONFIG &= ~bm3048MHZ
#define SETIF48MHZ() IFCONFIG |= bm3048MHZ


// eeprom stuff
#define EEPROM_TWO_BYTE (I2CS & bmBIT4)


#endif

/**
 * Copyright (C) 2008 Ubixum, Inc. 
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

#ifndef LIGHTS_H
#define LIGHTS_H

#include "fx2types.h"
#include "delay.h"

volatile xdata at 0x8800 BYTE D2ON;
volatile xdata at 0x8000 BYTE D2OFF;
volatile xdata at 0x9800 BYTE D3ON;
volatile xdata at 0x9000 BYTE D3OFF;
volatile xdata at 0xA800 BYTE D4ON;
volatile xdata at 0xA000 BYTE D4OFF;
volatile xdata at 0xB800 BYTE D5ON;
volatile xdata at 0xB000 BYTE D5OFF;
extern xdata BYTE light_dummy;

/**
 * easier to use macros defined below 
**/
//void activate_light ( volatile BYTE xdata *light ) ;
#define activate_light(LIGHT_ADDR) light_dummy=*(LIGHT_ADDR)
#define activate_light_delay(LIGHT_ADDR,millis) activate_light(LIGHT_ADDR); delay(millis)
//void activate_light_delay ( volatile BYTE xdata* light, WORD millis );

#define d2on() activate_light(&D2ON)
#define d2off() activate_light(&D2OFF)
#define d3on() activate_light(&D3ON)
#define d3off() activate_light(&D3OFF)
#define d4on() activate_light(&D4ON)
#define d4off() activate_light(&D4OFF)
#define d5on() activate_light(&D5ON)
#define d5off() activate_light(&D5OFF)

#endif

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

/** \file lights.h
 * macros for turning lights on the EZ-USB development board on and off.
 **/

#ifndef LIGHTS_H
#define LIGHTS_H

#include "fx2types.h"

#ifndef FX1
// FX2 Dev board lights
#define D2ONH #0x88 // assembly high byte of light addr 
#define D2OFFH #0x80 
#define D3ONH #0x98 
#define D3OFFH #0x90 
#define D4ONH #0xA8 
#define D4OFFH #0xA0 
#define D5ONH #0xB8 
#define D5OFFH #0xB0 
volatile xdata at 0x8800 BYTE D2ON;
volatile xdata at 0x8000 BYTE D2OFF;
volatile xdata at 0x9800 BYTE D3ON;
volatile xdata at 0x9000 BYTE D3OFF;
volatile xdata at 0xA800 BYTE D4ON;
volatile xdata at 0xA000 BYTE D4OFF;
volatile xdata at 0xB800 BYTE D5ON;
volatile xdata at 0xB000 BYTE D5OFF;
#else
// FX1 dev board lights
#define D2ONH #0x80 // assembly high byte of light addr 
#define D2OFFH #0x81 
#define D3ONH #0x90 
#define D3OFFH #0x91 
#define D4ONH #0xA0 
#define D4OFFH #0xA1 
#define D5ONH #0xB0 
#define D5OFFH #0xB1 
volatile xdata at 0x8000 BYTE D2ON;
volatile xdata at 0x8100 BYTE D2OFF;
volatile xdata at 0x9000 BYTE D3ON;
volatile xdata at 0x9100 BYTE D3OFF;
volatile xdata at 0xA000 BYTE D4ON;
volatile xdata at 0xA100 BYTE D4OFF;
volatile xdata at 0xB000 BYTE D5ON;
volatile xdata at 0xB100 BYTE D5OFF;
#endif

/**
 * Easier to use macros defined below 
**/
#define activate_light(LIGHT_ADDR) __asm \
 mov __XPAGE, LIGHT_ADDR \
 __endasm; __asm \
 movx a, @r0 \
__endasm \

/**
 *  Easy to make lights blink with these macros:
 *  \code
 *      WORD ct=0;
 *      BOOL on=FALSE;
 *      while (TRUE) {
 *          if (!ct) {
 *              on=!on;
 *              if (on) d2on(); else d2off();
 *          }
 *          ++ct;
 *      }
 *  \endcode
 **/
#define d2on() activate_light(D2ONH)
#define d2off() activate_light(D2OFFH)
#define d3on() activate_light(D3ONH)
#define d3off() activate_light(D3OFFH)
#define d4on() activate_light(D4ONH)
#define d4off() activate_light(D4OFFH)
#define d5on() activate_light(D5ONH)
#define d5off() activate_light(D5OFFH)

#endif

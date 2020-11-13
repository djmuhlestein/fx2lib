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

/** \file serial.h
 * defines functions to print to a serial console with SIO0
 **/

#include "fx2types.h"


/**
 * This function inits sio0 to use T2CON (timer 2)
 * See TRM 14.3.4.1 (Table 14-16)
 * Certain baud rates have too high an error rate to work.  All baud rates are .16%
 * except:
 *
 *          12MHZ      24MHZ
 *   \li 57600  -6.99%
 *   \li 38400  -2.34%     -2.34%
 *   \li 19200  -2.34%
 *
 *   Possible Baud rates:
 *    \li 2400
 *    \li 4800
 *    \li 9600
 *    \li 19200
 *    \li 28800
 *    \li 38400
 *    \li 57600
 *
 *    Any of these rates should work except 57600 at 12mhz.  -2.34% is pushing
 *    most hardware specs for working.  All rates at 48mhz work at .16%
 **/

void sio0_init( DWORD baud_rate ) __critical ; // baud_rate max should be 57600 since int=2 bytes

/**
 putchar('\\n') or putchar('\\r') both transmit \\r\\n
 Just use one or the other. (This makes terminal echo easy)
**/
int putchar(char c);
int getchar();

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
 *  define standard types of fixed widths.
 * */

#ifndef FXTYPES_H
#define FXTYPES_H

typedef unsigned int WORD;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned char BOOL; 
typedef enum {
 FALSE=0,
 TRUE
} BOOL_VALS;

#ifndef NULL
#define NULL (void*)0
#endif

/*-----------------------------------------------------------------------------
   Bit Masks
-----------------------------------------------------------------------------*/

#define bmBIT0	1
#define bmBIT1	2
#define bmBIT2	4
#define bmBIT3	8
#define bmBIT4	16
#define bmBIT5	32
#define bmBIT6	64
#define bmBIT7	128

#endif

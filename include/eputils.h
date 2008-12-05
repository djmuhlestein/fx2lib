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

#ifndef EPUTILS_H
#define EPUTILS_H

#include "fx2types.h"

#define RESETFIFOS() {FIFORESET=0x80; SYNCDELAY();\
                     FIFORESET=0x02; SYNCDELAY();\
                     FIFORESET=0x04; SYNCDELAY();\
                     FIFORESET=0x06; SYNCDELAY();\
                     FIFORESET=0x08; SYNCDELAY();\
                     FIFORESET=0x00; SYNCDELAY();}


void readep0( BYTE* dst, WORD len );



#endif

/**
 * Copyright (C) 2009 Ubixum, Inc. 
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




#include <eputils.h>

#include <fx2regs.h>

#ifdef DEBUG_EPUTILS
#include <stdio.h>
#else
#define printf(...)
#endif

void readep0( BYTE* dst, WORD len) {
    WORD read = 0; // n bytes read
    BYTE c,avail;
    while (read < len) {
        EP0BCH = 0;
        // NOTE need syncdelay?
        EP0BCL = 0; // re-arm ep so host can send more
        while (EP0CS & bmEPBUSY);
        avail = EP0BCL; // max size fits in one byte (64 bytes)
        for (c=0;c<avail;++c)
            dst[read+c] = EP0BUF[c];
        read += avail;
    }
}


void writeep0( BYTE* src, WORD len) {
    WORD written = 0;
    BYTE c;
    while ( written < len ) {
        while ( EP0CS & bmEPBUSY ); // wait
        for (c=0;c<64 && written<len;++c ) {
            EP0BUF[c] = src[written++];
        }
        EP0BCH = 0;
        EP0BCL= c;
        printf ( "Write %d bytes\n", c );
    }
}

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

#include <fx2regs.h>

#include <lights.h>
#include <delay.h>

volatile xdata BYTE* bytes[] = { &D2ON, &D3ON, &D4ON, &D5ON, &D2OFF, &D3OFF, &D4OFF, &D5OFF };

void main(void)
{
    volatile BYTE tmp;
	BYTE cur=0;

    // loop endlessly
    for(;;) {
       tmp=*bytes[cur];
       delay(50);
       cur = cur == 7 ? 0 : cur+1;
    }
}

# Copyright (C) 2009 Ubixum, Inc. 
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

SOURCES = serial.c i2c.c delay.c setupdat.c gpif.c eputils.c
FX2_OBJS = $(patsubst %.c,%.rel, $(SOURCES)) usbjt.rel
INCLUDES = -I../include
SDCC = sdcc -mmcs51 $(SDCCFLAGS)
LIBS = fx2.lib

all: $(LIBS)

$(LIBS): $(FX2_OBJS)
	sdcclib fx2.lib $?

usbjt.rel: usbjt.a51
	asx8051 -logs usbjt.a51

%.rel: %.c
	$(SDCC) $(INCLUDES) -c $?

clean:
	rm -f *.{asm,ihx,lnk,lst,map,mem,rel,rst,sym,adb,cdb,lib}


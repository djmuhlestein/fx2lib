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



# change location of fx2libdir if needed
FX2LIBDIR = ../
INCLUDES = -I$(FX2LIBDIR)/include
FX2LIB = $(FX2LIBDIR)/lib/fx2.lib
LIBS = fx2.lib -L$(FX2LIBDIR)/lib

# change to be your own vid/pid if needed
VID=0x0x04b4 # default Cypress
PID=0x0082 # default EZ-USB

# possible env flags
# -D DEBUG_FIRMWARE - enable stdio & printf on sio-0 (57600 buad)
# -D NORENUM - don't renumerate when firmware loads.  Used for iic load.
SDCCFLAGS := $(SDCCFLAGS)
CC = sdcc -mmcs51 \
	$(SDCCFLAGS) \
   --xram-size 0x0800 \
   --code-size 0x2e00 \
    --xram-loc 0x3200 \
	-Wl"-b DSCR_AREA = 0x2e00" \
	-Wl"-b INT2JT = 0x3000" \

BASENAME = firmware

# add additional sources
SOURCES = fw.c \
		  device.c

OBJS = $(patsubst %.c,%.rel, $(SOURCES)) dscr.rel 

.PHONY: all iic bix
all: $(BASENAME).ihx

%.rel: %.c
	$(CC) -c $(INCLUDES) $?

$(FX2LIB):
	make -C $(FX2LIB)/lib/

$(BASENAME).ihx: $(OBJS) $(FX2LIB)
	$(CC) $(OBJS) $(LIBS) -o $(BASENAME).ihx

dscr.rel: dscr.a51
	asx8051 -logs dscr.a51


$(BASENAME).bix: $(BASENAME).ihx
	packihx $(BASENAME).ihx > $(BASENAME).hex
	objcopy -I ihex -O binary $(BASENAME).hex $(BASENAME).bix

$(BASENAME).iic: $(BASENAME).ihx
	hex2bix -IC -F 0xc2 -M 16000 -V $(VID) -P $(PID) -O $(BASENAME).iic $(BASENAME).ihx

clean:
	rm -f *.{asm,ihx,lnk,lst,map,mem,rel,rst,sym,adb,cdb,bix,iic}

bix: $(BASENAME).bix
iic: $(BASENAME).iic



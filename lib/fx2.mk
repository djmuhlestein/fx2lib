# common make targets for compiling fx2 firmware
#
# In your Makefile, define:
# SOURCES: list of c files to compile
# A51_SOURCES: list of any a51 files.
# DEPS: list of any depedancies (like auto-generated header files) that need
#       generated prior to compiling. You must provide the target definition
#       for any DEPS you define.
# BASENAME: name of your firmware file, i.e., myfirmware, but not myfirmware.c
#
# Leave these alone or redefine as necessary to customize firmware.
# (Redefine after including this makefile)
# VID vendor id
# PID product id
# LIBS optional additional libraries to link with the firmware.
# SDCC build/link options
#  CODE_SIZE:    Default --code-size 0x3c00
#  XRAM_SIZE:    Default --xram-size 0x0200
#  XRAM_LOC:     Default --xram-loc 0x3c00
# BUILDDIR: build directory (default build)
# These two can be changed to be blank if no device descriptor is being used.
#  DSCR_AREA:    Default -Wl"-b DSCR_AREA=0x3e00"
#  INT2JT:		Default -Wl"-b INT2JT=0x3f00"
#
# Provided targets:
#
# default target: creates $(BASENAME).ihx
# bix: creates $(BASENAME).bix
# iic: creates $(BASENAME).iic
# load: uses fx2load to load firmware.bix onto the development board
#  (You can customize VID/PID if you need to load the firmware onto a device that has different vendor and product id
#  The default is  0x04b4, 0x8613
# clean: delete all the temp files.
#
#
#

VID?=0x04b4
PID?=0x8613

DSCR_AREA?=-Wl"-b DSCR_AREA=0x3e00"
INT2JT?=-Wl"-b INT2JT=0x3f00"
CODE_SIZE?=--code-size 0x3c00
XRAM_SIZE?=--xram-size 0x0200
XRAM_LOC?=--xram-loc 0x3c00
BUILDDIR?=build

FX2LIBDIR?=$(dir $(lastword $(MAKEFILE_LIST)))../

RELS=$(addprefix $(BUILDDIR)/, $(addsuffix .rel, $(notdir $(basename $(SOURCES) $(A51_SOURCES)))))
# these are pretty good settings for most firmwares.  
# Have to be careful with memory locations for 
# firmwares that require more xram etc.
CC = sdcc -mmcs51 \
	$(SDCCFLAGS) \
    $(CODE_SIZE) \
    $(XRAM_SIZE) \
    $(XRAM_LOC) \
	$(DSCR_AREA) \
	$(INT2JT)


.PHONY: ihx iic bix load clean clean-all


ihx: $(BUILDDIR)/$(BASENAME).ihx
bix: $(BUILDDIR)/$(BASENAME).bix
iic: $(BUILDDIR)/$(BASENAME).iic

$(FX2LIBDIR)/lib/fx2.lib: $(FX2LIBDIR)/lib/*.c $(FX2LIBDIR)/lib/*.a51
	make -C $(FX2LIBDIR)/lib

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(BASENAME).ihx: $(BUILDDIR) $(SOURCES) $(A51_SOURCES) $(FX2LIBDIR)/lib/fx2.lib $(DEPS) 
# can't use default target %.rel because there is no way
# to differentiate the dependency.  (Is it %.rel: %.c or %.a51)
	for a in $(A51_SOURCES); do \
	 cp $$a $(BUILDDIR)/; \
	 cd $(BUILDDIR) && asx8051 -logs `basename $$a` && cd ..; done
	for s in $(SOURCES); do \
	 THISREL=$$(basename `echo "$$s" | sed -e 's/\.c$$/\.rel/'`); \
	 $(CC) -c -I $(FX2LIBDIR)/include $$s -o $(BUILDDIR)/$$THISREL ; done
	$(CC) -o $@ $(RELS) fx2.lib -L $(FX2LIBDIR)/lib $(LIBS)


$(BUILDDIR)/$(BASENAME).bix: $(BUILDDIR)/$(BASENAME).ihx
	objcopy -I ihex -O binary $< $@
$(BUILDDIR)/$(BASENAME).iic: $(BUILDDIR)/$(BASENAME).ihx
	$(FX2LIBDIR)/utils/ihx2iic.py -v $(VID) -p $(PID) $< $@

load: $(BUILDDIR)/$(BASENAME).bix
	fx2load -v $(VID) -p $(PID) $(BUILDDIR)/$(BASENAME).bix

clean:
	rm -f $(BUILDDIR)/*.{asm,ihx,lnk,lst,map,mem,rel,rst,sym,adb,cdb,bix}

clean-all: clean
	make -C $(FX2LIBDIR)/lib clean


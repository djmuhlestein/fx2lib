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

AS8051?=sdas8051

VID?=0x04b4
PID?=0x8613

INCLUDES?=""
DSCR_AREA?=-Wl"-b DSCR_AREA=0x3e00"
INT2JT?=-Wl"-b INT2JT=0x3f00"
CC=sdcc
CODE_SIZE?=--code-size 0x3c00
XRAM_SIZE?=--xram-size 0x0200
XRAM_LOC?=--xram-loc 0x3c00
BUILDDIR?=build

FX2LIBDIR?=$(dir $(lastword $(MAKEFILE_LIST)))../

RELS=$(addprefix $(BUILDDIR)/, $(addsuffix .rel, $(notdir $(basename $(SOURCES) $(A51_SOURCES)))))
# these are pretty good settings for most firmwares.  
# Have to be careful with memory locations for 
# firmwares that require more xram etc.
SDCC = $(CC) -mmcs51 \
	$(SDCCFLAGS) \
    $(CODE_SIZE) \
    $(XRAM_SIZE) \
    $(XRAM_LOC) \
	$(DSCR_AREA) \
	$(INT2JT)


.PHONY: all ihx iic bix load clean clean-all

all: ihx
ihx: $(BUILDDIR)/$(BASENAME).ihx
bix: $(BUILDDIR)/$(BASENAME).bix
iic: $(BUILDDIR)/$(BASENAME).iic

$(FX2LIBDIR)/lib/fx2.lib: $(FX2LIBDIR)/lib/*.c $(FX2LIBDIR)/lib/*.a51
	$(MAKE) -C $(FX2LIBDIR)/lib

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(BASENAME).ihx: $(BUILDDIR) $(SOURCES) $(A51_SOURCES) $(FX2LIBDIR)/lib/fx2.lib $(DEPS) 
# can't use default target %.rel because there is no way
# to differentiate the dependency.  (Is it %.rel: %.c or %.a51)
	for a in $(A51_SOURCES); do \
	 cp $$a $(BUILDDIR)/; \
	 cd $(BUILDDIR) && $(AS8051) -logs `basename $$a` && cd ..; done
	for s in $(SOURCES); do \
	 THISREL=$$(basename `echo "$$s" | sed -e 's/\.c$$/\.rel/'`); \
	 $(SDCC) -c -I $(FX2LIBDIR)/include -I $(INCLUDES) $$s -o $(BUILDDIR)/$$THISREL ; done
	$(SDCC) -o $@ $(RELS) fx2.lib -L $(FX2LIBDIR)/lib $(LIBS)


$(BUILDDIR)/$(BASENAME).bix: $(BUILDDIR)/$(BASENAME).ihx
	objcopy -I ihex -O binary $< $@
$(BUILDDIR)/$(BASENAME).iic: $(BUILDDIR)/$(BASENAME).ihx
	$(FX2LIBDIR)/utils/ihx2iic.py -v $(VID) -p $(PID) $< $@

load: $(BUILDDIR)/$(BASENAME).bix
	fx2load -v $(VID) -p $(PID) $(BUILDDIR)/$(BASENAME).bix

clean:
	rm -f $(foreach ext, a51 asm ihx lnk lk lst map mem rel rst rest sym adb cdb bix, $(BUILDDIR)/*.${ext})

clean-all: clean
	$(MAKE) -C $(FX2LIBDIR)/lib clean


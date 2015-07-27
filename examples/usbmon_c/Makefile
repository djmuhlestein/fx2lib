FX2LIBDIR=../../
BASENAME = usbmon
SOURCES=usbmon.c
A51_SOURCES=dscr.a51
PID=0x1004

HOSTCC=gcc
CFLAGS=-Wall -Wextra -Os -lusb-1.0

include $(FX2LIBDIR)lib/fx2.mk

download: build/$(BASENAME).ihx
	./download.sh $<

clean:
	rm -rf build

test:	test.c
	$(HOSTCC) $(CFLAGS) -o $@ $<
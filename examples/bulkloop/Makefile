FX2LIBDIR=../../
BASENAME = bulkloop
SOURCES=bulkloop.c
A51_SOURCES=dscr.a51


include $(FX2LIBDIR)/lib/fx2.mk

PID=0x1004

test: test.cpp
	g++ -o test test.cpp -lusb-1.0


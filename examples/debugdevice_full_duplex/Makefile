FX2LIBDIR=../../
BASENAME = debugdev
SOURCES=debugdev.c
A51_SOURCES=dscr.a51
PID=0x1004
include $(FX2LIBDIR)lib/fx2.mk

CXX=g++
HOSTCC=gcc
CXXFLAGS=-Wall -Wextra -O2 -ggdb
HOSTCFLAGS=-Wall -Wextra -O2 -ggdb

all: test terminal build/debugdev.ihx

download: build/$(BASENAME).ihx
	  ./download.sh $<

terminal:	terminal.c
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $< -lusb-1.0

%:		%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -lusb-1.0

INCLUDES = -I../../include
LIBS = fx2.lib -L../../lib
CC = sdcc -mmcs51 --code-size 0x2000 --xram-loc 0x3000 \
	 -Wl"-b DSCR_AREA = 0x2000" \
	 -Wl"-b INT2JT = 0x2200"

BASENAME = bulkloop
DSCR = dscr.rel

$(BASENAME).ihx: $(BASENAME).c $(DSCR)
	$(CC) $(INCLUDES) $(BASENAME).c $(DSCR) $(LIBS)

$(DSCR): dscr_asm
	cp dscr_asm dscr.asm
	asx8051 -logs dscr.asm

$(BASENAME).bix: $(BASENAME).ihx
	objcopy -I ihex -O binary $(BASENAME).ihx $(BASENAME).bix

clean:
	rm -f *.{asm,ihx,lnk,lst,map,mem,rel,rst,sym,adb,cdb,bix}

.PHONY:run bix
run: $(BASENAME).bix
	python load.py

bix: $(BASENAME).bix

test: test.cpp
	g++ -o test test.cpp -lusb-1.0


reset:
	$(CYCFX2PROG) reset

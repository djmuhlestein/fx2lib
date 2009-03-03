INCLUDES = -I../../../include
LIBS = fx2.lib -L../../../lib
CC = sdcc -mmcs51 \
	--xram-loc 0x3000 \
    --xram-size 0x1000 \
	-Wl"-b DSCR_AREA = 0x2800" \
	-Wl"-b INT2JT = 0x2b00"

BASENAME = eeprom
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

.PHONY:bix

bix: $(BASENAME).bix


INCLUDES = -I../../include
LIBS = fx2.lib -L../../lib
CC = sdcc -mmcs51 --xram-loc 0x3000
BASENAME = reset

$(BASENAME).ihx: $(BASENAME).c fx2_c0.rel
	$(CC) $(INCLUDES) $(BASENAME).c fx2_c0.rel $(LIBS)

fx2_c0.rel: fx2_c0.c
	$(CC) -c fx2_c0.c

clean:
	rm -f *.{asm,ihx,lnk,lst,map,mem,rel,rst,sym,adb,cdb,bix}

$(BASENAME).bix:
	objcopy -I ihex -O binary $(BASENAME).ihx $(BASENAME).bix

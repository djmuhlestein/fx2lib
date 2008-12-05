INCLUDES = -I../../include
LIBS = fx2.lib -L ../../lib
CC = sdcc -mmcs51 --debug
BASENAME = lights

$(BASENAME).ihx: $(BASENAME).c
	$(CC) $(INCLUDES) $(BASENAME).c $(LIBS)

$(BASENAME).bix: $(BASENAME).ihx
	objcopy -I ihex -O binary $(BASENAME).ihx $(BASENAME).bix

clean:
	rm -f $(BASENAME).{asm,ihx,lnk,lst,map,mem,rel,rst,sym,adb,cdb,bix}

.PHONY:bix
bix: $(BASENAME).bix


INCLUDES = -I../../include
LIBS = fx2.lib -L../../lib
CC = sdcc -mmcs51 --xram-loc 0x3000 --xram-size 0x1000
BASENAME = serial
MEMSIZE = 4096

$(BASENAME).ihx: $(BASENAME).c
	$(CC) $(INCLUDES) $(BASENAME).c $(LIBS)

clean:
	rm -f $(BASENAME).{asm,ihx,lnk,lst,map,mem,rel,rst,sym,adb,cdb,bix}

$(BASENAME).iic: $(BASENAME).ihx
	../../utils/hex2bix -I -F 0xc2 -O serial.iic serial.ihx

$(BASENAME).bix: $(BASENAME).ihx
	objcopy -I ihex -O binary $(BASENAME).ihx $(BASENAME).bix

bix: $(BASENAME).bix


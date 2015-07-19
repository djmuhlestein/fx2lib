DIRS=	bulkloop debugdevice debugdevice_full_duplex eeprom i2c lights reset serial timers usbmon_c
     
.PHONY: dirs $(DIRS) clean
     
dirs: $(DIRS)
clean: $(DIRS)
     
$(DIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)


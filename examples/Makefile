DIRS=	bulkloop eeprom i2c lights reset serial timers
     
.PHONY: dirs $(DIRS) clean
     
dirs: $(DIRS)
clean: $(DIRS)
     
$(DIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)


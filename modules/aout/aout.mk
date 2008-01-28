
CC_INCLUDE += -I $(MIOS_PATH)/modules/aout 

$(OUTDIR)/aout.o: $(MIOS_PATH)/modules/aout/aout.c
	$(CC) $(CCFLAGS) $(SDCC_DEFINES) $< -o $(OUTDIR)/

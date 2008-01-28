# defines the rule for creating the aout.o object

SDCC_INCLUDE += -I $(MIOS_PATH)/modules/aout 

$(OUTDIR)/aout.o: $(MIOS_PATH)/modules/aout/aout.c
	$(SDCC) $(SDCC_FLAGS) $(SDCC_DEFINES) $< -o $@

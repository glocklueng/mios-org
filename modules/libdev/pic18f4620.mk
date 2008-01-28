# defines the rule for creating the pic18f452.o object
# included from $MIOS_PATH/include/makefile/common.mk
$(OUTDIR)/pic18f4620.o: $(MIOS_PATH)/modules/libdev/pic18f4620.c
	$(SDCC) $(SDCC_FLAGS) $(SDCC_DEFINES) $<

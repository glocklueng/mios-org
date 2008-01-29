# defines the rule for creating the pic18f452.o object
# included from $MIOS_PATH/include/makefile/common.mk
$(OUTDIR)/pic18f452.o: $(MIOS_PATH)/modules/libdev/pic18f452.c
	$(SDCC) $(SDCC_FLAGS) $(SDCC_INCLUDE) $(SDCC_DEFINES) $< -o $@

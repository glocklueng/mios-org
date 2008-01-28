# defines the rule for creating the mios_wrapper.o object
# included from $MIOS_PATH/include/makefile/common.mk
$(OUTDIR)/mios_wrapper.o: $(MIOS_PATH)/modules/mios_wrapper/mios_wrapper.asm
	$(GPASM) $(GPASM_FLAGS) $(MIOS_WRAPPER_DEFINES) -I $(MIOS_PATH)/modules/mios_wrapper $<  -o $@

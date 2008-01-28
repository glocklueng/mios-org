
$(OUTDIR)/mios_wrapper.o: $(MIOS_PATH)/modules/mios_wrapper/mios_wrapper.asm
	$(GPASM) $(GPASMFLAGS) $(MIOS_WRAPPER_DEFINES) -I $(MIOS_PATH)/modules/mios_wrapper $<  -o $@

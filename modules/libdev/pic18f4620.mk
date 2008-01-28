
$(OUTDIR)/pic18f4620.o: $(MIOS_PATH)/modules/libdev/pic18f4620.c
	$(CC) $(CCFLAGS) $(SDCC_DEFINES) $< -o $(OUTDIR)/


$(OUTDIR)/pic18f452.o: $(MIOS_PATH)/modules/libdev/pic18f452.c
	$(CC) $(CCFLAGS) $(SDCC_DEFINES) $< -o $(OUTDIR)/

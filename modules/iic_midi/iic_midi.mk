# defines the rule for creating the iic_midi.o object

SDCC_INCLUDE += -I $(MIOS_PATH)/modules/iic_midi

$(OUTDIR)/iic_midi.o: $(MIOS_PATH)/modules/iic_midi/iic_midi.asm
	$(GPASM) $(GPASM_FLAGS) $(IIC_MIDI_DEFINES) $< -o $@

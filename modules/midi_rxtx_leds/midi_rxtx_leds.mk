# defines the rule for creating the midi_rxtx_leds.o object

SDCC_INCLUDE += -I $(MIOS_PATH)/modules/midi_rxtx_leds

$(OUTDIR)/midi_rxtx_leds.o: $(MIOS_PATH)/modules/midi_rxtx_leds/midi_rxtx_leds.asm
	$(GPASM) $(GPASM_FLAGS) $(MIDI_RXTX_LEDS_DEFINES) $< -o $@

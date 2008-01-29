# defines the rule for creating the midi_rxtx_leds.o object

# (only SDCC include path needs to be extended)
SDCC_INCLUDE += -I $(MIOS_PATH)/modules/midi_rxtx_leds

$(OUTDIR)/midi_rxtx_leds.o: $(MIOS_PATH)/modules/midi_rxtx_leds/midi_rxtx_leds.asm
	$(GPASM) $(GPASM_FLAGS) $(GPASM_INCLUDE) $(GPASM_DEFINES) $(MIDI_RXTX_LEDS_DEFINES) $< -o $@

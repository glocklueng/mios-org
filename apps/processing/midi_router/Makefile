
PROCESSOR=p18f452
OBJS=pic18f452.o mios_wrapper.o main.o iic_midi.o iic_midi_tick.o int_midi.o midi_rxtx_leds.o router.o

GPASM_INCLUDE=-I $(MIOS_PATH)/include/asm

MIOS_WRAPPER_DEFINES=-DSTACK_HEAD=0x37f -DSTACK_IRQ_HEAD=0x33f \
                     -DDONT_INCLUDE_MIOS_ENC_TABLE \
                     -DENABLE_MIDI_NOTIFY_RX -DENABLE_MIDI_NOTIFY_TX

SDCC_INCLUDE=-I $(MIOS_PATH)/include/c  -I.
SDCC_DEFINES=-DDEBUG_MODE=0
GPLINK_FLAGS=-s $(MIOS_PATH)/etc/lkr/$(PROCESSOR).lkr

include $(MIOS_PATH)/include/makefile/common.mk
include $(MIOS_PATH)/modules/midi_rxtx_leds/midi_rxtx_leds.mk
include $(MIOS_PATH)/modules/iic_midi/iic_midi.mk

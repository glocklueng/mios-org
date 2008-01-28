
PROCESSOR=p18f452
OBJS=pic18f452.o mios_wrapper.o main.o midi.o lfo.o eg.o map.o aout.o

ASM_INCLUDE=-I $(MIOS_PATH)/include/asm
CC_INCLUDE=-I $(MIOS_PATH)/include/c  -I.
MIOS_WRAPPER_DEFINES=-DSTACK_HEAD=0x37f -DSTACK_IRQ_HEAD=0x33f
SDCC_DEFINES=-DDEBUG_MODE=0
GPLINKFLAGS=-s $(MIOS_PATH)/etc/lkr/$(PROCESSOR).lkr

include $(MIOS_PATH)/include/makefile/common.mk
include $(MIOS_PATH)/modules/aout/aout.mk

# $Id$

# define the processor here
PROCESSOR = 18f4620

# default flags to GPASM here
GPASM_FLAGS   = 

# include pathes (more will be added by asm_only.mk files)
GPASM_INCLUDE = 

# optional defines that should be passed to GPASM
GPASM_DEFINES = 

# default rule that defines the .hex files which should be created
# note: always require a "cleanall", since dependencies (e.g. on .h and .inc files) are not properly declared
all: cleanall setup_808_mbseqv3_hardware.hex setup_808_mbseqv3_tk.hex setup_808_tk.hex setup_808_default.hex setup_808_with_swingpot.hex setup_seq_dr_default.hex setup_seq_dr_with_swingpot.hex


# include the asm_only.mk file
include $(MIOS_PATH)/include/makefile/asm_only.mk

# include application specific LCD driver (dummy driver by default)
include $(MIOS_PATH)/modules/app_lcd/dummy/app_lcd.mk

# include MBHP_IIC_MIDI driver
include $(MIOS_PATH)/modules/iic_midi/iic_midi.mk

# include AOUT driver
include $(MIOS_PATH)/modules/aout/aout.mk

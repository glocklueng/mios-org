
# define the processor, linker file and project name
PROCESSOR = p18f452
LKR_FILE  = $(MIOS_PATH)/etc/lkr/$(PROCESSOR).lkr
PROJECT   = project

# list of objects that should be created and linked
OBJS = pic18f452.o mios_wrapper.o main.o midi.o lfo.o eg.o map.o aout.o

# include pathes (e.g. "-I./src if source code located there
# more will be added by .mk files)
GPASM_INCLUDE = 
SDCC_INCLUDE  = 

# optional defines which should be passed to GPASM/SDCC
GPASM_DEFINES = -DDEBUG_MODE=0
SDCC_DEFINES  = -DDEBUG_MODE=0

# pass parameters to MIOS wrapper
MIOS_WRAPPER_DEFINES = -DSTACK_HEAD=0x37f -DSTACK_IRQ_HEAD=0x33f


# include the common.mk file
include $(MIOS_PATH)/include/makefile/common.mk

# include additional module specific makefile rules
include $(MIOS_PATH)/modules/aout/aout.mk

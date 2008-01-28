
# default project name
PROJECT=project

# output directory
OUTDIR=_output

# GPASM execution via wrapper
GPASM=perl $(MIOS_BIN_PATH)/mios-gpasm.pl -c -o $(OUTDIR)/

# SDCC execution via wrapper
SDCC=perl $(MIOS_BIN_PATH)/mios-sdcc.pl -c -o $(OUTDIR)/

# GPLINK execution (w/o wrapper yet)
GPLINK=gplink

# default flags for GPASM
GPASM_FLAGS=-p $(PROCESSOR) $(GPASM_INCLUDE) -DDEBUG_MODE=0

# default flags for SDCC
SDCC_FLAGS=-mpic16 -$(PROCESSOR) $(SDCC_INCLUDE) --fommit-frame-pointer --optimize-goto --optimize-cmp --disable-warning 85 --obanksel=2 -pleave-reset-vector

# rule to create a .hex file
# note: currently we always require a "cleanall", since dependencies (e.g. on .h files) are not properly managed
# later we could try it w/o "cleanall", and propose the usage of this step to the user
$(PROJECT).hex: cleanall mk_outdir $(addprefix $(OUTDIR)/, $(OBJS))
	$(GPLINK) $(GPLINK_FLAGS) -m -o $(PROJECT).hex $(addprefix $(OUTDIR)/, $(OBJS))

# default rule for compiling .c programs
$(OUTDIR)/%.o: %.c
	$(SDCC) $(SDCC_FLAGS) $(SDCC_DEFINES) $<

# default rule for compiling .asm programs
# we expect, that they don't need to be converted through the wrapper
$(OUTDIR)/%.o: %.asm
	$(GPASM) $(GPASM_FLAGS) $<

# default rule for compiling .s programs (these are assembler programs as well)
# for .s we expect, that they need to be converted through the wrapper
$(OUTDIR)/%.o: %.s
	$(GPASM) $(GPASM_FLAGS) $<

# include mios_wrapper related rules
include $(MIOS_PATH)/modules/mios_wrapper/mios_wrapper.mk

# add makefile rules of supported processors here
include $(MIOS_PATH)/modules/libdev/pic18f452.mk
include $(MIOS_PATH)/modules/libdev/pic18f4620.mk

# create directory that contains object files
mk_outdir:
	mkdir -p $(OUTDIR)

# clean temporary files
clean:
	rm -rf $(OUTDIR)/*
	rm -rf $(OUTDIR)
	rm -rf *.cod *.map *.lst

# clean temporary files + project image
cleanall: clean
	rm -rf *.hex

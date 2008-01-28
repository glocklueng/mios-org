
PROJECT=project
OUTDIR=_output

GPASM=perl $(MIOS_BIN_PATH)/mios-gpasm.pl -c -o $(OUTDIR)/
CC=perl $(MIOS_BIN_PATH)/mios-sdcc.pl -c -o $(OUTDIR)/
GPLINK=gplink

GPASMFLAGS=-p $(PROCESSOR) $(ASM_INCLUDE) -DDEBUG_MODE=0
CCFLAGS=-mpic16 -$(PROCESSOR) $(CC_INCLUDE) --fommit-frame-pointer --optimize-goto --optimize-cmp --disable-warning 85 --obanksel=2 -pleave-reset-vector

$(PROJECT).hex: cleanall mk_outdir $(addprefix $(OUTDIR)/, $(OBJS))
	$(GPLINK) $(GPLINKFLAGS) -m -o $(PROJECT).hex $(addprefix $(OUTDIR)/, $(OBJS))

$(OUTDIR)/%.o: %.c
	$(CC) $(CCFLAGS) $(SDCC_DEFINES) $< -o $(OUTDIR)/


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

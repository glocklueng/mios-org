
GPASMFLAGS = -p 18f4685 -I $(MIOS_PATH)/include/asm -I ./src 

all: cleanall setup_6581.hex setup_8580.hex setup_tk.hex setup_mb6582.hex

%.hex: %.asm
	gpasm $(GPASMFLAGS) $<

clean:
	rm -f *.cod *.lst *.err

cleanall: clean
	rm -f *.hex


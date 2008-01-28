
GPASMFLAGS = -I $(MIOS_PATH)/include/asm

all: cleanall mios_p18f452.hex mios_p18f4620.hex mios_p18f4520.hex mios_p18f4682.hex mios_p18f4685.hex

mios_p18f452.hex: main.asm
	gpasm $< $(GPASMFLAGS) -p 18f452 -o mios_p18f452.hex

mios_p18f4520.hex: main.asm
	gpasm $< $(GPASMFLAGS) -p 18f4520 -o mios_p18f4520.hex

mios_p18f4620.hex: main.asm
	gpasm $< $(GPASMFLAGS) -p 18f4620 -o mios_p18f4620.hex

mios_p18f4682.hex: main.asm
	gpasm $< $(GPASMFLAGS) -p 18f4682 -o mios_p18f4682.hex

mios_p18f4685.hex: main.asm
	gpasm $< $(GPASMFLAGS) -p 18f4685 -o mios_p18f4685.hex

clean:
	rm -f *.cod *.lst *.err

cleanall: clean
	rm -f *.hex

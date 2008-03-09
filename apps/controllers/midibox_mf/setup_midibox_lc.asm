; $Id$
	LIST R=DEC
;
; Setup File of TK's MIDIbox LC
; Explanations to the switches and levers: see setup_midibox_mf.asm
;
#define DEFAULT_NUMBER_FADERS	8

#define DEFAULT_FADER_GROUP_WIDTH	8

#define DEFAULT_NUMBER_BUTTONS  64

#define DEFAULT_SRIO_DEBOUNCE_CTR 32

#define DEFAULT_ENABLE_MOTORDRIVER	1
#define DEFAULT_MF_PWM_DUTY_UP	        0x01
#define DEFAULT_MF_PWM_DUTY_DOWN        0x01
#define DEFAULT_MF_PWM_PERIOD           0x03

#define DEFAULT_ENABLE_AIN_MUX		0

#define DEFAULT_TOUCH_SENSOR_SR		16
#define DEFAULT_TOUCH_SENSOR_MODE	2
#define	DEFAULT_TOUCH_SENSOR_SENSITIVITY 3

#define DEFAULT_PATCHMODE 0
#define DEFAULT_BANK_PRG_CHNG_CHANNEL 16
#define DEFAULT_PATCH_PRG_CHNG_CHANNEL 15

#define DEFAULT_BANKSTICK_CS	-1

#define DEFAULT_DEVICE_ID	0x00
#define DEFAULT_AUTO_DEVICE_ID	1

#define DEFAULT_MIDI_MONITOR_ENABLED 0
#define DEFAULT_MIDI_RX_LED 0x40
#define DEFAULT_MIDI_TX_LED 0x41

#define DEFAULT_DIN_SR_PIN_01_08	2
#define DEFAULT_DIN_SR_PIN_09_16	3
#define DEFAULT_DIN_SR_PIN_17_24	1
#define DEFAULT_DIN_SR_PIN_25_32	4
#define DEFAULT_DIN_SR_PIN_33_40	5
#define DEFAULT_DIN_SR_PIN_41_48	6
#define DEFAULT_DIN_SR_PIN_49_56	7
#define DEFAULT_DIN_SR_PIN_57_64	8

#define DEFAULT_ENC_DATAWHEEL   1
#define DEFAULT_DIN_MENU_EXEC	7
#define DEFAULT_DIN_MENU_RIGHT	6
#define DEFAULT_DIN_MENU_LEFT	5
#define DEFAULT_DIN_MENU_SNAPSHOT 4

#define DEFAULT_DOUT_SR_PIN_01_08	2
#define DEFAULT_DOUT_SR_PIN_09_16	3
#define DEFAULT_DOUT_SR_PIN_17_24	1
#define DEFAULT_DOUT_SR_PIN_25_32	4
#define DEFAULT_DOUT_SR_PIN_33_40	5
#define DEFAULT_DOUT_SR_PIN_41_48	6
#define DEFAULT_DOUT_SR_PIN_49_56	7
#define DEFAULT_DOUT_SR_PIN_57_64	8

#define DEFAULT_GP_DIN_SR0	2
#define DEFAULT_GP_DIN_SR1	3

#define DEFAULT_GP_DOUT_SR0	2
#define DEFAULT_GP_DOUT_SR1	3

#define DEFAULT_YOFFSET_LINE0	0x00 + 12
#define DEFAULT_YOFFSET_LINE1	0x40 + 12
#define DEFAULT_YOFFSET_LINE2	0x14 + 12
#define DEFAULT_YOFFSET_LINE3	0x54 + 12

#include "src/main.inc"

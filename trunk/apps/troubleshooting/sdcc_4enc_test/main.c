// $Id: main.c 524 2008-11-22 18:54:40Z this $
/*
 * MIOS SDCC Wrapper
 *
 * ==========================================================================
 *
 *  Copyright (C) <year>  <name> (<email>)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */


/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <cmios.h>
#include <pic18fregs.h>


unsigned char enc[4];
unsigned char enc_changed = 0;

/////////////////////////////////////////////////////////////////////////////
// Application specific encoder table
// the default (dummy) table has been disabled via -DDONT_INCLUDE_MIOS_ENC_TABLE
/////////////////////////////////////////////////////////////////////////////
MIOS_ENC_TABLE {
  MIOS_ENC_ENTRY(1, 0, MIOS_ENC_MODE_DETENTED2),
  MIOS_ENC_ENTRY(1, 2, MIOS_ENC_MODE_DETENTED2),
  MIOS_ENC_ENTRY(1, 4, MIOS_ENC_MODE_DETENTED2),
  MIOS_ENC_ENTRY(1, 6, MIOS_ENC_MODE_DETENTED2),
  MIOS_ENC_EOT
};


/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS after startup to initialize the 
// application
/////////////////////////////////////////////////////////////////////////////
void Init(void) __wparam{
	unsigned char i;
 	MIOS_SRIO_UpdateFrqSet(1); // ms
  	MIOS_SRIO_NumberSet(1);
  	MIOS_SRIO_DebounceSet(20);
  	for(i=0;i<4;i++){
  		enc[i] = 0;
  		MIOS_ENC_SpeedSet(i, MIOS_ENC_SPEED_FAST, 4);
  		}
  	TRISCbits.TRISC5 = 0;
  	PORTCbits.RC5 = 1;
  	}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS in the mainloop when nothing else is to do
/////////////////////////////////////////////////////////////////////////////
void Tick(void) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is periodically called by MIOS. The frequency has to be
// initialized with MIOS_Timer_Set
/////////////////////////////////////////////////////////////////////////////
void Timer(void) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when the display content should be 
// initialized. Thats the case during startup and after a temporary message
// has been printed on the screen
/////////////////////////////////////////////////////////////////////////////

void print_enc_values(void) __wparam{
	unsigned char i;
	MIOS_LCD_CursorSet(0x00);
	for(i=0;i<4;i++){
		MIOS_LCD_PrintBCD3(enc[i]);
		MIOS_LCD_PrintChar(' ');
		}
	enc_changed = 0;
	}

void DISPLAY_Init(void) __wparam{
	MIOS_LCD_Clear();	
	print_enc_values();
	}

/////////////////////////////////////////////////////////////////////////////
//  This function is called in the mainloop when no temporary message is shown
//  on screen. Print the realtime messages here
/////////////////////////////////////////////////////////////////////////////
void DISPLAY_Tick(void) __wparam{
	if(enc_changed)
		print_enc_values();
	}

/////////////////////////////////////////////////////////////////////////////
//  This function is called by MIOS when a complete MIDI event has been received
/////////////////////////////////////////////////////////////////////////////
void MPROC_NotifyReceivedEvnt(unsigned char evnt0, unsigned char evnt1, unsigned char evnt2) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when a MIDI event has been received
// which has been specified in the MIOS_MPROC_EVENT_TABLE
/////////////////////////////////////////////////////////////////////////////
void MPROC_NotifyFoundEvent(unsigned entry, unsigned char evnt0, unsigned char evnt1, unsigned char evnt2) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when a MIDI event has not been completly
// received within 2 seconds
/////////////////////////////////////////////////////////////////////////////
void MPROC_NotifyTimeout(void) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when a MIDI byte has been received
/////////////////////////////////////////////////////////////////////////////
void MPROC_NotifyReceivedByte(unsigned char byte) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS before the shift register are loaded
/////////////////////////////////////////////////////////////////////////////
void SR_Service_Prepare(void) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS after the shift register have been loaded
/////////////////////////////////////////////////////////////////////////////
void SR_Service_Finish(void) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when an button has been toggled
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
void DIN_NotifyToggle(unsigned char pin, unsigned char pin_value) __wparam
{
}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when an encoder has been moved
// incrementer is positive when encoder has been turned clockwise, else
// it is negative
/////////////////////////////////////////////////////////////////////////////
void ENC_NotifyChange(unsigned char encoder, char incrementer) __wparam{
	if(incrementer > 0)
		enc[encoder] = (127 - enc[encoder] > incrementer) ? enc[encoder] + incrementer : 127;
	else
		enc[encoder] = ((-enc[encoder]) < incrementer) ? enc[encoder] + incrementer : 0;
	enc_changed = 1;
	}

/////////////////////////////////////////////////////////////////////////////
// This function is called by MIOS when a pot has been moved
/////////////////////////////////////////////////////////////////////////////
void AIN_NotifyChange(unsigned char pin, unsigned int pin_value) __wparam
{
}
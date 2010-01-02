; $Id$
;
; A CORE->LCD Module Interconnection Test
;
; ==========================================================================
;
;  Copyright 2006 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

;; ---[ MIOS header file ]---
#include <mios.h>

;; ---[ useful macros ]---
#include <macros.h>

;; ---[ vectors to MIOS functions (never change!) ]---
#include <mios_vectors.inc>

;; ---[ user hooks (never change!) ]---
#include <user_vectors.inc>

;; ==========================================================================
;;  General Application Settings
;; ==========================================================================

;; ---[ variables used by application ]---
#include "app_defines.h"

; ==========================================================================

;; ---[ configuration table for MIDI processor and rotary encoders ]---
#include <mios_mt_table.inc>
#include <mios_enc_table.inc>

;; ---[ Custom LCD driver ]---
#include <app_lcd.inc>

;; ---[ Debug Message Module ]---
#include <debug_msg.inc>


;; ==========================================================================
;;  All MIOS hooks in one file
;; ==========================================================================

;; --------------------------------------------------------------------------
;;  This function is called by MIOS after startup to initialize the 
;;  application
;; --------------------------------------------------------------------------
USER_Init
	return


;; --------------------------------------------------------------------------
;;  This function is called by MIOS in the mainloop when nothing else is to do
;; --------------------------------------------------------------------------
USER_Tick
	return


;; --------------------------------------------------------------------------
;;  This function is periodically called by MIOS. The frequency has to be
;;  initialized with MIOS_Timer_Set
;;  Note that this is an interrupt service routine! Use FSR2 instead of FSR0
;;  and IRQ_TMPx instead of TMPx -- and make the routine as fast as possible!
;; --------------------------------------------------------------------------
USER_Timer
	return


;; --------------------------------------------------------------------------
;;  This function is called by MIOS when a debug command has been received
;;  via SysEx
;;  Input:
;;     o WREG, MIOS_PARAMETER1, MIOS_PARAMETER2, MIOS_PARAMETER3 like
;;       specified in the debug command
;;  Output:
;;     o return values WREG, MIOS_PARAMETER1, MIOS_PARAMETER2, MIOS_PARAMETER3
;; --------------------------------------------------------------------------
USER_MPROC_DebugTrigger
	return


;; --------------------------------------------------------------------------
;;  This function is called by MIOS when the display content should be 
;;  initialized. Thats the case during startup and after a temporary message
;;  has been printed on the screen
;; --------------------------------------------------------------------------
USER_DISPLAY_Init
	call	MIOS_LCD_Clear

	TABLE_ADDR TEXT_WELCOME_0
	call	MIOS_LCD_PrintString
	call	MIOS_LCD_PrintString

	call	DEBUG_MSG_SendHeader
	movlw	'\n'
	call	DEBUG_MSG_SendChar
	call	DEBUG_MSG_SendFooter
	
	call	DEBUG_MSG_SendHeader
	call	DEBUG_MSG_SendASMString
	db	"LCD Interconnection Test\n", 0
	call	DEBUG_MSG_SendFooter
	
	call	DEBUG_MSG_SendHeader
	call	DEBUG_MSG_SendASMString
	db	"========================\n", 0
	call	DEBUG_MSG_SendFooter

	call	DEBUG_MSG_SendHeader
	call	DEBUG_MSG_SendASMString
	db	"Please play a note on any MIDI channel.\n", 0
	call	DEBUG_MSG_SendFooter
	
	bsf	DISPLAY_UPDATE_REQ, 0

	return

TEXT_WELCOME_0	STRING 16, 0x00, "Test LCD X-Cons."
TEXT_WELCOME_1	STRING  5, 0x40, "Pin: "

;; --------------------------------------------------------------------------
;;  This function is called in the mainloop when no temporary message is shown
;;  on screen. Print the realtime messages here
;; --------------------------------------------------------------------------
USER_DISPLAY_Tick
	;; display update requested from USER_SR_Service_Prepare on every LED change
	btfss	DISPLAY_UPDATE_REQ, 0
	return
	bcf	DISPLAY_UPDATE_REQ, 0

	;; write static message again (could have been cleared by last E line toggling)
	TABLE_ADDR TEXT_WELCOME_0
	call	MIOS_LCD_PrintString
	call	MIOS_LCD_PrintString

	;; print pin name
	movlw	0x40 + 5
	call	MIOS_LCD_CursorSet
	TABLE_ADDR LCD_PIN_NAMES_TABLE
	movf	LCD_PIN_NUMBER, W
	mullw	LCD_PIN_NAMES_LEN
	movf	PRODL, W
	addwf	TBLPTRL, F
	movf	PRODH, W
	addwfc	TBLPTRH, F
	movlw	LCD_PIN_NAMES_LEN
	call	MIOS_LCD_PrintPreconfString


	;; send message to MIOS Terminal
	call	DEBUG_MSG_SendHeader
	call	DEBUG_MSG_SendASMString
	db	"Pin '", 0

	TABLE_ADDR LCD_PIN_NAMES_TABLE
	movf	LCD_PIN_NUMBER, W
	mullw	LCD_PIN_NAMES_LEN
	movf	PRODL, W
	addwf	TBLPTRL, F
	movf	PRODH, W
	addwfc	TBLPTRH, F

	;; always two chars
	tblrd*+
	movf	TABLAT, W
	call	DEBUG_MSG_SendChar
	tblrd*+
	movf	TABLAT, W
	call	DEBUG_MSG_SendChar

	call	DEBUG_MSG_SendASMString
	db	"' of MBHP_CORE::J15 set to 5V, all other data/control pins set to 0V", 0
	call	DEBUG_MSG_SendFooter

	;; IMPORTANT!!!
	;; Since a LCD message could overwrite the data/address/control
	;; line value, we update the pins again
	goto	LCD_SetPin
	
	

LCD_PIN_NAMES_LEN	EQU	2
LCD_PIN_NAMES_NUM	EQU	11
LCD_PIN_NAMES_TABLE
	db	"D0"
	db	"D1"
	db	"D2"
	db	"D3"
	db	"D4"
	db	"D5"
	db	"D6"
	db	"D7"
	db	"E "
	db	"RW"
	db	"RS"


;; --------------------------------------------------------------------------
;;  This function is called by MIOS when a complete MIDI event has been received
;;  Input:
;;     o first  MIDI event byte in MIOS_PARAMETER1
;;     o second MIDI event byte in MIOS_PARAMETER2
;;     o third  MIDI event byte in MIOS_PARAMETER3
;; --------------------------------------------------------------------------
USER_MPROC_NotifyReceivedEvent
	;; if modulation wheel received: set new pin
	movf	MIOS_PARAMETER1, W
	andlw	0xf0
	xorlw	0xb0
	bnz	USER_NotifyReceivedEvent_ChkNote
	movf	MIOS_PARAMETER2, W
	xorlw	0x01
	bnz	USER_NotifyReceivedEvent_ChkNote

	movf	MIOS_PARAMETER3, W
	movwf	LCD_PIN_NUMBER
	movlw	LCD_PIN_NAMES_NUM
	cpfslt	LCD_PIN_NUMBER, ACCESS
	clrf LCD_PIN_NUMBER
	bsf	DISPLAY_UPDATE_REQ, 0

	;; set the pin depending on selected LCD number
	call	LCD_SetPin
	rgoto	USER_NotifyReceivedEvent_End


USER_NotifyReceivedEvent_ChkNote
	;; alternative control via MIDI keyboard (Note On Events with velocity > 0)
	movf	MIOS_PARAMETER1, W
	andlw	0xf0
	xorlw	0x90
	bnz	USER_NotifyReceivedEvent_End
	movf	MIOS_PARAMETER3, W
	bz	USER_NotifyReceivedEvent_End
	;; normalize note to 0..11 range
	movf	MIOS_PARAMETER2, W
USER_NotifyReceivedEvent_NoteNor
	addlw	-12
	BRA_IFCLR WREG, 7, ACCESS, USER_NotifyReceivedEvent_NoteNor
	addlw	12		; now in range 0..11
	movwf	LCD_PIN_NUMBER
	
	movlw	LCD_PIN_NAMES_NUM
	cpfslt	LCD_PIN_NUMBER, ACCESS
	clrf LCD_PIN_NUMBER
	bsf	DISPLAY_UPDATE_REQ, 0

	;; set the pin depending on selected LCD number
	call	LCD_SetPin
	;; 	rgoto	USER_NotifyReceivedEvent_End

USER_NotifyReceivedEvent_End
	return


;; --------------------------------------------------------------------------
;;  This function is called by MIOS when a MIDI event has been received
;;  which has been specified in the CONFIG_MIDI_IN table
;;  Input:
;;     o number of entry in WREG
;;     o first  MIDI event byte in MIOS_PARAMETER1
;;     o second MIDI event byte in MIOS_PARAMETER2
;;     o third  MIDI event byte in MIOS_PARAMETER3
;; --------------------------------------------------------------------------
USER_MPROC_NotifyFoundEvent
	return


;; --------------------------------------------------------------------------
;;  This function is called by MIOS when a MIDI event has not been completly
;;  received within 2 seconds
;; --------------------------------------------------------------------------
USER_MPROC_NotifyTimeout
	return


;; --------------------------------------------------------------------------
;;  This function is called by MIOS when a MIDI byte has been received
;;  Input:
;;     o received MIDI byte in WREG and MIOS_PARAMETER1
;; --------------------------------------------------------------------------
USER_MPROC_NotifyReceivedByte
	return

;; --------------------------------------------------------------------------
;;  This function is called by MIOS before the transfer of a MIDI byte. 
;;  It can be used to monitor the Tx activity or to do any other actions
;;  (e.g. to switch a pin for multiplexed MIDI Outs) before the byte will 
;;  be sent.
;;  Note that this is an interrupt service routine! Use FSR2 instead of FSR0
;;  and IRQ_TMPx instead of TMPx -- and make the routine as fast as possible!
;;  Input:
;;     o transmitted byte in WREG
;; --------------------------------------------------------------------------
USER_MIDI_NotifyTx
	return

;; --------------------------------------------------------------------------
;;  This function is called by MIOS when a MIDI byte has been received.
;;  It can be used to monitor the Rx activity or to do any action - e.g.
;;  to react on realtime events like MIDI clock (0xf8) with a minimum latency
;;  Note that this is an interrupt service routine! Use FSR2 instead of FSR0
;;  and IRQ_TMPx instead of TMPx -- and make the routine as fast as possible!
;;  Input:
;;     o received byte in WREG
;; --------------------------------------------------------------------------
USER_MIDI_NotifyRx
	return

;; --------------------------------------------------------------------------
;;  This function is called by MIOS when an button has been toggled
;;  Input:
;;     o Button number in WREG and MIOS_PARAMETER1
;;     o Button value MIOS_PARAMETER2:
;;       - 1 if button has been released (=5V)
;;       - 0 if button has been pressed (=0V)
;; --------------------------------------------------------------------------
USER_DIN_NotifyToggle
	return


;; --------------------------------------------------------------------------
;;  This function is called by MIOS when an encoder has been moved
;;  Input:
;;     o Encoder number in WREG and MIOS_PARAMETER1
;;     o signed incrementer value in MIOS_PARAMETER2:
;;       - is positive when encoder has been turned clockwise
;;       - is negative when encoder has been turned counter clockwise
;; --------------------------------------------------------------------------
USER_ENC_NotifyChange
	return


;; --------------------------------------------------------------------------
;;  This function is called by MIOS before the shift register are loaded
;;  Note that this is an interrupt service routine! Use FSR2 instead of FSR0
;;  and IRQ_TMPx instead of TMPx -- and make the routine as fast as possible
;; --------------------------------------------------------------------------
USER_SR_Service_Prepare
	return


;; --------------------------------------------------------------------------
;;  This function is called by MIOS after the shift register have been loaded
;;  Note that this is an interrupt service routine! Use FSR2 instead of FSR0
;;  and IRQ_TMPx instead of TMPx -- and make the routine as fast as possible
;; --------------------------------------------------------------------------
USER_SR_Service_Finish
	return

;; --------------------------------------------------------------------------
;;  This function is called by MIOS when a pot has been moved
;;  Input:
;;     o Pot number in WREG and MIOS_PARAMETER1
;;     o LSB value in MIOS_PARAMETER2
;;     o MSB value in MIOS_PARAMETER3
;; --------------------------------------------------------------------------
USER_AIN_NotifyChange
	return



;; --------------------------------------------------------------------------
;;  This function sets a LCD pin depending on LCD_PIN_NUMBER
;; --------------------------------------------------------------------------
;; Pins of LC-Display
MIOS_CLCD_LAT_D		EQU	LATB	; Pin B.7-0
MIOS_CLCD_PORT_D	EQU     PORTB
MIOS_CLCD_TRIS_D	EQU     TRISB

MIOS_CLCD_LAT_E		EQU	LATD
MIOS_CLCD_PIN_E		EQU	7		; Pin D.7
MIOS_CLCD_LAT_RW	EQU     LATD
MIOS_CLCD_PIN_RW	EQU     6               ; Pin D.6
MIOS_CLCD_LAT_RS	EQU     LATD
MIOS_CLCD_PIN_RS	EQU     5               ; Pin D.5

LCD_SetPin
	;; clear the pins
	clrf	MIOS_CLCD_LAT_D
	bcf	MIOS_CLCD_LAT_E, MIOS_CLCD_PIN_E
	bcf	MIOS_CLCD_LAT_RW, MIOS_CLCD_PIN_RW
	bcf	MIOS_CLCD_LAT_RS, MIOS_CLCD_PIN_RS
	;; enable output driver of data pins
	clrf	MIOS_CLCD_TRIS_D

	;; set the selected pin
	movf	LCD_PIN_NUMBER, W
	JUMPTABLE_2BYTES 11	; entries
	rgoto	LCD_SetPin0
	rgoto	LCD_SetPin1
	rgoto   LCD_SetPin2
	rgoto	LCD_SetPin3
	rgoto	LCD_SetPin4
	rgoto   LCD_SetPin5
	rgoto	LCD_SetPin6
	rgoto	LCD_SetPin7
	rgoto   LCD_SetPin8
	rgoto	LCD_SetPin9
	rgoto	LCD_SetPin10

LCD_SetPin0
	bsf	MIOS_CLCD_LAT_D, 0
	return

LCD_SetPin1
	bsf	MIOS_CLCD_LAT_D, 1
	return

LCD_SetPin2
	bsf	MIOS_CLCD_LAT_D, 2
	return

LCD_SetPin3
	bsf	MIOS_CLCD_LAT_D, 3
	return

LCD_SetPin4
	bsf	MIOS_CLCD_LAT_D, 4
	return

LCD_SetPin5
	bsf	MIOS_CLCD_LAT_D, 5
	return

LCD_SetPin6
	bsf	MIOS_CLCD_LAT_D, 6
	return

LCD_SetPin7
	bsf	MIOS_CLCD_LAT_D, 7
	return

LCD_SetPin8
	bsf	MIOS_CLCD_LAT_E, MIOS_CLCD_PIN_E
	return

LCD_SetPin9
	bsf	MIOS_CLCD_LAT_RW, MIOS_CLCD_PIN_RW
	return

LCD_SetPin10
	bsf	MIOS_CLCD_LAT_RS, MIOS_CLCD_PIN_RS
	return


	END

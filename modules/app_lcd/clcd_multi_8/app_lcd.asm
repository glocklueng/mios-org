; $Id: app_lcd.asm 346 2008-06-05 23:56:31Z tk $
;
; Wrapper for app_lcd.inc
; To be used for relocatable programs
;
; ==========================================================================

	radix	dec

#include <mios.h>
#include <mios_vectors.inc>
#include <macros.h>

; ==========================================================================
; Import/Export Labels
; ==========================================================================
	global	USER_LCD_Init
	global	USER_LCD_Data
	global	USER_LCD_Cmd
	global	USER_LCD_Clear
	global	USER_LCD_CursorSet
	global	USER_LCD_PrintChar
	global	USER_LCD_SpecialCharInit

	global	USER_LCD_Select
	global	_USER_LCD_Select

; ==========================================================================
; Start code section and include driver code
; ==========================================================================
APP_LCD CODE
#include "app_lcd.inc"
	END

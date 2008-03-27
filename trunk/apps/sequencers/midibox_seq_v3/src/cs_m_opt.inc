; $Id$
;
; MBSEQ Menu "Options"
;
; ==========================================================================
;
;  Copyright 1998-2006 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

;; --------------------------------------------------------------------------
;;  This table contains the edit values
;; --------------------------------------------------------------------------
CS_M_OPT_PARAMETERS
 ;;			 CC/value				max	cursor/len	MenuParameterHook
 CS_MENU_PARAMETER_ENTRY -1,					0x01,	0x40 +  1, 3,	CS_M_OPT_ValueChanged_0
 CS_MENU_PARAMETER_ENTRY -1,					0x01,	0x40 + 18, 3,	CS_M_OPT_ValueChanged_1
 CS_MENU_PARAMETER_ENTRY -1,					0x01,	0x40 + 28,11,	CS_M_OPT_ValueChanged_2
 CS_MENU_PARAMETER_ENTRY -1,			                0x04,   0xc0 +  1, 8,   CS_M_OPT_ValueChanged_3
 CS_MENU_PARAMETER_ENTRY -1,			                0x0c,   0xc0 + 10, 8,   CS_M_OPT_ValueChanged_4
 CS_MENU_PARAMETER_ENTRY -1,			SEQ_SCALE_NUMBER-1,     0xc0 + 16,20,   CS_M_OPT_ValueChanged_5


;; --------------------------------------------------------------------------
;;  This is the menu specific GP callback function called by cs_menu_button.inc 
;;  when the GP hook has been installed
;;  Input:
;;     o GP Button number in MIOS_PARAMETER1 (0x00-0x0f)
;;     o Button value MIOS_PARAMETER2:
;;       - 1 if button has been released (=5V)
;;       - 0 if button has been pressed (=0V)
;;     o encoder incrementer in CS_MENU_ENC_INCREMENTER if encoder has been used
;;  Output:
;;     should return the GP LED values in
;;     CS_MENU_GP_OVERLAY_DOUT_SR[01]
;;     should clear CS_MENU_ENC_INCREMENTER if radio-button function desired
;; --------------------------------------------------------------------------
CS_M_OPT_GP_Callback
	;; do nothing if GP button has been depressed
	btfsc	MIOS_PARAMETER2, 0
	return

	;; preselect base
	SET_BSR	SEQ_BASE

	;; branch depending on button
	movf	MIOS_PARAMETER1, W
	andlw	0x0f
	JUMPTABLE_2BYTES_UNSECURE
	rgoto	CS_M_OPT_GP_Callback_1
	rgoto	CS_M_OPT_GP_Callback_2
	rgoto	CS_M_OPT_GP_Callback_3
	rgoto	CS_M_OPT_GP_Callback_4
	rgoto	CS_M_OPT_GP_Callback_5
	rgoto	CS_M_OPT_GP_Callback_6
	rgoto	CS_M_OPT_GP_Callback_7
	rgoto	CS_M_OPT_GP_Callback_8
	rgoto	CS_M_OPT_GP_Callback_9
	rgoto	CS_M_OPT_GP_Callback_10
	rgoto	CS_M_OPT_GP_Callback_11
	rgoto	CS_M_OPT_GP_Callback_12
	rgoto	CS_M_OPT_GP_Callback_13
	rgoto	CS_M_OPT_GP_Callback_14
	rgoto	CS_M_OPT_GP_Callback_15
	rgoto	CS_M_OPT_GP_Callback_16

CS_M_OPT_GP_Callback_1
CS_M_OPT_GP_Callback_2
CS_M_OPT_GP_Callback_3
	;; toggle flag
	btg	SEQ_CFG0, SEQ_CFG0_PATTERN_SYNCH, BANKED
	movlw	0		; Item #0
	rgoto	CS_M_OPT_GP_Callback_Cont

CS_M_OPT_GP_Callback_4
CS_M_OPT_GP_Callback_5
	btg	SEQ_CFG0, SEQ_CFG0_FOLLOW_SONG, BANKED
	movlw	1		; Item #1
	rgoto	CS_M_OPT_GP_Callback_Cont


CS_M_OPT_GP_Callback_6
CS_M_OPT_GP_Callback_7
CS_M_OPT_GP_Callback_8
	btg	SEQ_CFG0, SEQ_CFG0_PASTE_CLR_ALL, BANKED
	movlw	2		; Item #2
	rgoto	CS_M_OPT_GP_Callback_Cont

CS_M_OPT_GP_Callback_9
CS_M_OPT_GP_Callback_10
	movlw	3		; Item #3
	rgoto	CS_M_OPT_GP_Callback_Cont

CS_M_OPT_GP_Callback_11
	movlw	4		; Item #4
	rgoto	CS_M_OPT_GP_Callback_Cont

CS_M_OPT_GP_Callback_12
CS_M_OPT_GP_Callback_13
CS_M_OPT_GP_Callback_14
CS_M_OPT_GP_Callback_15
CS_M_OPT_GP_Callback_16
	movlw	5		; Item #5
	rgoto	CS_M_OPT_GP_Callback_Cont


CS_M_OPT_GP_Callback_Cont
	cpfseq	CS_MENU_CURSOR_POS, ACCESS
	rgoto CS_M_OPT_GP_Callback_Cont_NP
	return			; pos already selected, increment allowed

CS_M_OPT_GP_Callback_Cont_NP
	clrf	CS_MENU_ENC_INCREMENTER
	movwf	CS_MENU_CURSOR_POS
	goto	CS_MENU_NewCursorPos	; notify new cursor position and exit


;; --------------------------------------------------------------------------
CS_M_OPT_UpdateGPLEDs
	;; clear all LEDs
	clrf	CS_MENU_GP_OVERLAY_DOUT_SR0
	clrf	CS_MENU_GP_OVERLAY_DOUT_SR1

	;; flash LEDs
	bcf	MB_STAT, MB_STAT_DONT_FLASH_R_GP_DOUT
	bcf	MB_STAT, MB_STAT_DONT_FLASH_L_GP_DOUT

	;; get pattern depending on cursor position
	movf	CS_MENU_CURSOR_POS, W
	TABLE_ADDR_MUL_W CS_M_OPT_UpdateGPLEDs_TAB, 1
	tblrd*+
	movlw	3
	cpfslt	CS_MENU_CURSOR_POS, ACCESS
	rgoto CS_M_OPT_UpdateGPLEDs_R
CS_M_OPT_UpdateGPLEDs_L
	movff	TABLAT, CS_MENU_GP_OVERLAY_DOUT_SR0
	return
CS_M_OPT_UpdateGPLEDs_R
	movff	TABLAT, CS_MENU_GP_OVERLAY_DOUT_SR1
	return

CS_M_OPT_UpdateGPLEDs_TAB
	db	b'00000111', b'00011000', b'11100000', b'00000011', b'00000100', b'11111000'

;; --------------------------------------------------------------------------
;;  Menu Init routine is called when menu page should be initialized
;; --------------------------------------------------------------------------
CS_M_OPT_Init
	;; switch to full screen view
	call	SEQ_LCD_SetMsgOffsets

	;; install parameter table
	TABLE_ADDR CS_M_OPT_PARAMETERS	; pointer to table
	movlw	6			; number of parameters
	call	CS_MENU_SetMenuParameterTable

	;; install callback function for general purpose buttons
	TABLE_ADDR CS_M_OPT_GP_Callback
	call	CS_MENU_SetMenuGPCallbackHook

	;; init LEDs
	rcall	CS_M_OPT_UpdateGPLEDs

	;; copy selected option into CS_MENU_PARAMETER_L
	rgoto	CS_M_OPT_CopyOpt


;; --------------------------------------------------------------------------
;;  Menu Tick routine is called on every refresh cycle
;; --------------------------------------------------------------------------
CS_M_OPT_Tick
	;; layout:
	;; 00000000001111111111222222222233333333330000000000111111111122222222223333333333
	;; 01234567890123456789012345678901234567890123456789012345678901234567890123456789
	;; <--------------------------------------><-------------------------------------->
	;; SyncPatChange  FollowSong  Paste/Clr Beh Control  Root      Selected Scale      
	;; 00000000001111111111222222222233333333334444444444555555555566666666667777777777
	;;      off          off       Steps only   Global   Keyb   50:Hungarian Gypsy     
	;; -----888----------999-------AAAAAAAAAA--BBBBBBBBBBCCCCCDDDDDEEEEEEEEEEEEEEEEEEEE

	;; print segments 0-15

	;; upper line
	BRA_IFCLR CS_MENU_REFRESH_ITEM_CTR, 3, ACCESS, CS_M_OPT_Tick_Upper

	;; lower line
	movf	CS_MENU_REFRESH_ITEM_CTR, W
	andlw	0x07
	JUMPTABLE_2BYTES_UNSECURE
	rgoto	CS_M_OPT_Tick_8
	rgoto	CS_M_OPT_Tick_9
	rgoto	CS_M_OPT_Tick_A
	rgoto	CS_M_OPT_Tick_B
	rgoto	CS_M_OPT_Tick_C
	rgoto	CS_M_OPT_Tick_D
	rgoto	CS_M_OPT_Tick_E
	rgoto	CS_M_OPT_Tick_F


CS_M_OPT_Tick_Upper_STR
	db	"SyncPatChange  FollowSong  Paste/Clr Beh Control  Root      Selected Scale      "
CS_M_OPT_Tick_Upper
	;; determine cursor pos
	movf	CS_MENU_REFRESH_ITEM_CTR, W
	andlw	0x03
	mullw	10
	movf	PRODL, W
	btfsc	CS_MENU_REFRESH_ITEM_CTR, 2
	iorlw 0x80
	call	MIOS_LCD_CursorSet

	;; determine string offset
	movf	CS_MENU_REFRESH_ITEM_CTR, W
	TABLE_ADDR_MUL_W CS_M_OPT_Tick_Upper_STR, 10

	;; print string part (10 characters)
	movlw	10
	call	MIOS_LCD_PrintPreconfString

	rgoto	CS_M_OPT_Tick_Cont


CS_M_OPT_Tick_8
	movlw	0x40 + 5
	call	MIOS_LCD_CursorSet
	movlw	0		; item number
	call	CS_MENU_CursorHandler2
	skpnz
	rgoto	CS_M_OPT_Tick_Cont

	SET_BSR	SEQ_BASE
	movlw	0x00
	btfsc	SEQ_CFG0, SEQ_CFG0_PATTERN_SYNCH, BANKED
	movlw 0x01
	call	SEQ_LCD_PrnOnOff
	rgoto	CS_M_OPT_Tick_Cont

CS_M_OPT_Tick_9
	movlw	0x40 + 18
	call	MIOS_LCD_CursorSet
	movlw	1		; item number
	call	CS_MENU_CursorHandler2
	skpnz
	rgoto	CS_M_OPT_Tick_Cont

	SET_BSR	SEQ_BASE
	movlw	0x00
	btfsc	SEQ_CFG0, SEQ_CFG0_FOLLOW_SONG, BANKED
	movlw 0x01
	call	SEQ_LCD_PrnOnOff
	rgoto	CS_M_OPT_Tick_Cont

CS_M_OPT_Tick_A_TABLE
	db	"Steps only  "
	db	"Whole Track "

CS_M_OPT_Tick_A
	movlw	0x40 + 28
	call	MIOS_LCD_CursorSet
	movlw	2		; item number
	call	CS_MENU_CursorHandler2
	skpnz
	rgoto	CS_M_OPT_Tick_Cont

	SET_BSR	SEQ_BASE
	movlw	0x00
	btfsc	SEQ_CFG0, SEQ_CFG0_PASTE_CLR_ALL, BANKED
	movlw 0x01
	TABLE_ADDR_MUL_W CS_M_OPT_Tick_A_TABLE, 12
	movlw	12
	call	MIOS_LCD_PrintPreconfString
	rgoto	CS_M_OPT_Tick_Cont


CS_M_OPT_Tick_B_TABLE
	db	"Global  "
	db	"Group G1"
	db	"Group G2"
	db	"Group G3"
	db	"Group G4"

CS_M_OPT_Tick_B
	movlw	0xc0 + 1
	call	MIOS_LCD_CursorSet
	movlw	3		; item number
	call	CS_MENU_CursorHandler2
	bz	CS_M_OPT_Tick_Cont

	SET_BSR	SEQ_BASE
	movf	SEQ_GLOBAL_SCALE_CTRL, W, BANKED
	andlw	0x0f
	TABLE_ADDR_MUL_W CS_M_OPT_Tick_B_TABLE, 8
	movlw	8
	call	MIOS_LCD_PrintPreconfString
	rgoto	CS_M_OPT_Tick_Cont


CS_M_OPT_Tick_C_TABLE
	db	"Keyb", " C  ", " C# ", " D  ", " D# ", " E  ", " F  ", " F# ", " G  ", " G# ", " A  ", " A# ", " B  "
CS_M_OPT_Tick_C
	movlw	0xc0 + 10
	call	MIOS_LCD_CursorSet
	movlw	4		; item number
	call	CS_MENU_CursorHandler2
	bz	CS_M_OPT_Tick_Cont

	call	SEQ_SCALE_GetRoot
	TABLE_ADDR_MUL_W CS_M_OPT_Tick_C_TABLE, 4
	movlw	4
	call	MIOS_LCD_PrintPreconfString
	rgoto	CS_M_OPT_Tick_Cont


CS_M_OPT_Tick_D
	movlw	0xc0 + 16
	call	MIOS_LCD_CursorSet
	movlw	5		; item number
	call	CS_MENU_CursorHandler2
	bz	CS_M_OPT_Tick_Cont

	SET_BSR	SEQ_BASE
	call	SEQ_SCALE_GetScale
	call	MIOS_LCD_PrintBCD3
	movlw	':'
	call	MIOS_LCD_PrintChar
	rgoto	CS_M_OPT_Tick_Cont

CS_M_OPT_Tick_E
	movlw	0xc0 + 20
	call	MIOS_LCD_CursorSet
	movlw	5		; item number
	call	CS_MENU_CursorHandler2
	bz	CS_M_OPT_Tick_Cont

	call	SEQ_SCALE_GetScale
	call	SEQ_SCALE_Prn	; (20 characters)
	rgoto	CS_M_OPT_Tick_Cont

CS_M_OPT_Tick_F
	;;  	rgoto	CS_M_OPT_Tick_Cont

CS_M_OPT_Tick_Cont
	;; Tick function will be called 16 times
	incf	CS_MENU_REFRESH_ITEM_CTR, F
	BRA_IFCLR CS_MENU_REFRESH_ITEM_CTR, 4, ACCESS, CS_M_OPT_Tick_End
	clrf	CS_MENU_REFRESH_ITEM_CTR
	;; 	rgoto	CS_M_PATTERN_Tick_End

CS_M_OPT_Tick_End
	return


;; ==========================================================================

;; --------------------------------------------------------------------------
;;  This hook is called when the menu parameter value has been changed
;; --------------------------------------------------------------------------
CS_M_OPT_ValueChanged_0
	SET_BSR	SEQ_BASE
	bcf	SEQ_CFG0, SEQ_CFG0_PATTERN_SYNCH, BANKED
	btfsc	CS_MENU_PARAMETER_L, 0
	bsf	SEQ_CFG0, SEQ_CFG0_PATTERN_SYNCH, BANKED
	return

CS_M_OPT_ValueChanged_1
	SET_BSR	SEQ_BASE
	bcf	SEQ_CFG0, SEQ_CFG0_FOLLOW_SONG, BANKED
	btfsc	CS_MENU_PARAMETER_L, 0
	bsf	SEQ_CFG0, SEQ_CFG0_FOLLOW_SONG, BANKED
	return

CS_M_OPT_ValueChanged_2
	SET_BSR	SEQ_BASE
	bcf	SEQ_CFG0, SEQ_CFG0_PASTE_CLR_ALL, BANKED
	btfsc	CS_MENU_PARAMETER_L, 0
	bsf	SEQ_CFG0, SEQ_CFG0_PASTE_CLR_ALL, BANKED
	return

CS_M_OPT_ValueChanged_3
	SET_BSR	SEQ_BASE
	movlw	0xf0
	andwf	SEQ_GLOBAL_SCALE_CTRL, F, BANKED
	movf	CS_MENU_PARAMETER_L, W
	andlw	0x0f
	iorwf	SEQ_GLOBAL_SCALE_CTRL, F, BANKED
	return

CS_M_OPT_ValueChanged_4
	call	SEQ_SCALE_GetRootPtr
	movlw	0x0f
	andwf	INDF1, F
	swapf	CS_MENU_PARAMETER_L, W
	andlw	0xf0
	iorwf	INDF1, F
	return

CS_M_OPT_ValueChanged_5
	call	SEQ_SCALE_GetScalePtr
	movff	CS_MENU_PARAMETER_L, INDF1
	return


;; --------------------------------------------------------------------------
;;  This function copies the selected option into CS_MENU_PARAMETER_L
;; --------------------------------------------------------------------------
CS_M_OPT_CopyOpt
	clrf	CS_MENU_PARAMETER_L

	SET_BSR	SEQ_BASE
	movf	CS_MENU_CURSOR_POS, W
	bz	CS_M_OPT_CopyOpt_0
	addlw	-1
	bz	CS_M_OPT_CopyOpt_1
	addlw	-1
	bz	CS_M_OPT_CopyOpt_2
	addlw	-1
	bz	CS_M_OPT_CopyOpt_3
	addlw	-1
	bz	CS_M_OPT_CopyOpt_4
	addlw	-1
	bz	CS_M_OPT_CopyOpt_5
	return

CS_M_OPT_CopyOpt_0
	btfsc	SEQ_CFG0, SEQ_CFG0_PATTERN_SYNCH, BANKED
	bsf	CS_MENU_PARAMETER_L, 0
	return

CS_M_OPT_CopyOpt_1
	btfsc	SEQ_CFG0, SEQ_CFG0_FOLLOW_SONG, BANKED
	bsf	CS_MENU_PARAMETER_L, 0
	return

CS_M_OPT_CopyOpt_2
	btfsc	SEQ_CFG0, SEQ_CFG0_PASTE_CLR_ALL, BANKED
	bsf	CS_MENU_PARAMETER_L, 0
	return

CS_M_OPT_CopyOpt_3
	SET_BSR	SEQ_BASE
	movf	SEQ_GLOBAL_SCALE_CTRL, W, BANKED
	andlw	0x0f
	movwf	CS_MENU_PARAMETER_L
	return

CS_M_OPT_CopyOpt_4
	call	SEQ_SCALE_GetRoot
	movwf	CS_MENU_PARAMETER_L
	return

CS_M_OPT_CopyOpt_5
	call	SEQ_SCALE_GetScale
	movwf	CS_MENU_PARAMETER_L
	return
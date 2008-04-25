; $Id$
;
; MIDIbox FM
; Parameter Input Handling
;
; ==========================================================================
;
;  Copyright 1998-2006 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

;; --------------------------------------------------------------------------
;;  IN: index of parameter in WREG, value in MIOS_PARAMETER1,
;;	instrument in MBFM_CURRENT_INSTRUMENT
;; --------------------------------------------------------------------------
MBFM_PARIN_Set
	rcall	MBFM_PAR_TABLE_Get
	;; now:
	;; value     is in MIOS_PARAMETER1
	;; command   is in MIOS_PARAMETER2
	;; parameter is in FSR1 (pointer)

MBFM_PARIN_Set_Cmd
	;; branch depending on command
	movf	MIOS_PARAMETER2, W
	andlw	0x0f
	JUMPTABLE_2BYTES_UNSECURE
	rgoto	MBFM_PARIN_Cmd_NOP
	rgoto	MBFM_PARIN_Cmd_7BIT
	rgoto	MBFM_PARIN_Cmd_7BIT_TO_7_4
	rgoto	MBFM_PARIN_Cmd_7BIT_TO_3_0
	rgoto	MBFM_PARIN_Cmd_INV_7BIT_TO_7_4
	rgoto	MBFM_PARIN_Cmd_INV_7BIT_TO_3_0
	rgoto	MBFM_PARIN_Cmd_7BIT_TO_7_6
	rgoto	MBFM_PARIN_Cmd_INV_7BIT_TO_5_0
	rgoto	MBFM_PARIN_Cmd_7BIT_TO_3_1
	rgoto	MBFM_PARIN_Cmd_7BIT_TO_CNT
	rgoto	MBFM_PARIN_Cmd_7BIT_TO_0
	rgoto	MBFM_PARIN_Cmd_ACHN_ALL
	rgoto	MBFM_PARIN_Cmd_ACHN
	rgoto	MBFM_PARIN_Cmd_MODWHEEL
	rgoto	MBFM_PARIN_Cmd_VELOCITY
	rgoto	MBFM_PARIN_Cmd_AFTERTOUCH

; ==========================================================================

;; --------------------------------------------------------------------------
;;  This function behaves like MBFM_PARIN_Set with the difference that
;;  address 0x00-0x0f writes the patch name
;; --------------------------------------------------------------------------
MBFM_PARIN_SysEx_Set
	movwf	TABLAT
	movlw	0x10
	cpfslt	TABLAT, ACCESS
	rgoto MBFM_PARIN_SysEx_Set_Norm

MBFM_PARIN_SysEx_Set_Name
	call	MBFM_INSTR_GetBase
	movf	TABLAT, W
	movff	MIOS_PARAMETER1, PLUSW1
	return

MBFM_PARIN_SysEx_Set_Norm
	movf	TABLAT, W
	rgoto	MBFM_PARIN_Set

; ==========================================================================

;; --------------------------------------------------------------------------
;; used for modwheel/aftertouch/velocity control of parameters
;; Input:
;;    - modulate value in MIOS_PARAMETER1
;;    - depth in MIOS_PARAMETER2
;;    - init value in MIOS_PARAMETER3
;; Output:
;;    - resulting value (which can be forwarded to MBFM_PARIN_Set) in WREG
;; --------------------------------------------------------------------------
MBFM_PARIN_Modulate
	movf	MIOS_PARAMETER2, W	; multiply depth with value
	andlw	0x3f
	btfss	MIOS_PARAMETER2, 6
	sublw 0x3f
	clrc
	rlf	WREG, F
	rlf	WREG, W
	mulwf	MIOS_PARAMETER1, ACCESS

	movf	PRODH, W
	BRA_IFSET MIOS_PARAMETER2, 6, ACCESS, MBFM_PARIN_Modulate_Pos
MBFM_PARIN_Modulate_Neg
	xorlw	0xff
	addwf	MIOS_PARAMETER3, W
	btfsc	WREG, 7
	movlw 0x00
	goto	MBFM_PARIN_Modulate_Cont
MBFM_PARIN_Modulate_Pos
	addwf	MIOS_PARAMETER3, W
	btfsc	WREG, 7
	movlw 0x7f
MBFM_PARIN_Modulate_Cont
	return

; ==========================================================================


;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_NOP
	return

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_7BIT
	movff	MIOS_PARAMETER1, INDF1
	rgoto	MBFM_PARIN_Send

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_7BIT_TO_7_4
	movlw	0x0f
	andwf	INDF1, F
	swapf	MIOS_PARAMETER1, W
	andlw	0xf0
	iorwf	INDF1, F
	rgoto	MBFM_PARIN_Send

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_7BIT_TO_3_0
	movlw	0xf0
	andwf	INDF1, F
	movf	MIOS_PARAMETER1, W
	andlw	0x0f
	iorwf	INDF1, F
	rgoto	MBFM_PARIN_Send

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_INV_7BIT_TO_7_4
	movlw	0x0f
	andwf	INDF1, F
	swapf	MIOS_PARAMETER1, W
	andlw	0xf0
	xorlw	0xf0
	iorwf	INDF1, F
	rgoto	MBFM_PARIN_Send

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_INV_7BIT_TO_3_0
	movlw	0xf0
	andwf	INDF1, F
	movf	MIOS_PARAMETER1, W
	andlw	0x0f
	xorlw	0x0f
	iorwf	INDF1, F
	rgoto	MBFM_PARIN_Send

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_7BIT_TO_7_6
	movlw	0x3f
	andwf	INDF1, F
	swapf	MIOS_PARAMETER1, W
	rlf	WREG, W
	rlf	WREG, W
	andlw	0xc0
	iorwf	INDF1, F
	rgoto	MBFM_PARIN_Send

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_INV_7BIT_TO_5_0
	movlw	0xc0
	andwf	INDF1, F
	movf	MIOS_PARAMETER1, W
	andlw	0x3f
	xorlw	0x3f
	iorwf	INDF1, F
	rgoto	MBFM_PARIN_Send

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_7BIT_TO_3_1
	movlw	0xf1
	andwf	INDF1, F
	rlf	MIOS_PARAMETER1, W
	andlw	0x0e
	iorwf	INDF1, F
	rgoto	MBFM_PARIN_Send

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_7BIT_TO_CNT
	bcf	INDF1, 0
	btfsc	MIOS_PARAMETER1, 0
	bsf	INDF1, 0
	movf	POSTINC1, W	; increment
	bcf	INDF1, 0
	btfsc	MIOS_PARAMETER1, 1
	bsf	INDF1, 0
	movf	POSTDEC1, W	; decrement

	;; send first byte
	rcall	MBFM_PARIN_Send

	;; EXTRA sending routine for second byte: dirty but ok here
	call	MBFM_INSTR_GetBase
	movlw	MBFM_Ix_OP34_CH_FB_CNT
	movwf	MIOS_PARAMETER1
	movf	PLUSW1, W
	goto	MBFM_INSTR_SendPar

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_7BIT_TO_0
	movlw	0xfe
	andwf	INDF1, F
	movf	MIOS_PARAMETER1, W
	andlw	0x01
	iorwf	INDF1, F
	rgoto	MBFM_PARIN_Send

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_ACHN_ALL
	movff	MIOS_PARAMETER1, POSTINC1
	movff	MIOS_PARAMETER1, POSTDEC1
	rgoto	MBFM_PARIN_Cmd_ACHN_End

MBFM_PARIN_Cmd_ACHN
	movff	MIOS_PARAMETER1, INDF1

MBFM_PARIN_Cmd_ACHN_End
	goto	MBFM_INSTR_SendAudioChn

;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_MODWHEEL
	movff	MIOS_PARAMETER1, INDF1

	call	MBFM_INSTR_GetBase
	movlw	MBFM_Ix_MODWHEEL_ASSIGN	; exit when modwheel assigned to 0
	movf	PLUSW1, W
	bz	MBFM_PARIN_Cmd_MODWHEEL_End
	addlw	-1			; prevent endless loop
	bz	MBFM_PARIN_Cmd_MODWHEEL_End

	movlw	MBFM_Ix_MODWHEEL
	movff	PLUSW1, MIOS_PARAMETER1
	movlw	MBFM_Ix_MODWHEEL_DEPTH
	movff	PLUSW1, MIOS_PARAMETER2
	movlw	MBFM_Ix_MODWHEEL_INIT
	movff	PLUSW1, MIOS_PARAMETER3
	rcall	MBFM_PARIN_Modulate
	movwf	MIOS_PARAMETER1
	movlw	MBFM_Ix_MODWHEEL_ASSIGN
	movf	PLUSW1, W
	rgoto	MBFM_PARIN_Set

MBFM_PARIN_Cmd_MODWHEEL_End
	return


;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_VELOCITY
	movff	MIOS_PARAMETER1, INDF1

MBFM_PARIN_Cmd_VELOCITY_MIDI	; direct entry from mbfm_midi.inc
	call	MBFM_INSTR_GetBase
	movlw	MBFM_Ix_VELOCITY_ASSIGN	; exit when velocity assigned to 0
	movf	PLUSW1, W
	bz	MBFM_PARIN_Cmd_VELOCITY_End

	movlw	MBFM_Ix_VELOCITY
	movff	PLUSW1, MIOS_PARAMETER1
	movlw	MBFM_Ix_VELOCITY_DEPTH
	movff	PLUSW1, MIOS_PARAMETER2
	movlw	MBFM_Ix_VELOCITY_INIT
	movff	PLUSW1, MIOS_PARAMETER3
	rcall	MBFM_PARIN_Modulate
	movwf	MIOS_PARAMETER1
	movlw	MBFM_Ix_VELOCITY_ASSIGN
	movf	PLUSW1, W
	rgoto	MBFM_PARIN_Set

MBFM_PARIN_Cmd_VELOCITY_End
	return


;; --------------------------------------------------------------------------
MBFM_PARIN_Cmd_AFTERTOUCH
	movff	MIOS_PARAMETER1, INDF1

MBFM_PARIN_Cmd_AFTERTOUCH_MIDI	; direct entry from mbfm_midi.inc
	call	MBFM_INSTR_GetBase
	movlw	MBFM_Ix_AFTERTOUCH_ASSIGN	; exit when aftertouch assigned to 0
	movf	PLUSW1, W
	bz	MBFM_PARIN_Cmd_AFTERTOUCH_End

	movlw	MBFM_Ix_AFTERTOUCH
	movff	PLUSW1, MIOS_PARAMETER1
	movlw	MBFM_Ix_AFTERTOUCH_DEPTH
	movff	PLUSW1, MIOS_PARAMETER2
	movlw	MBFM_Ix_AFTERTOUCH_INIT
	movff	PLUSW1, MIOS_PARAMETER3
	rcall	MBFM_PARIN_Modulate
	movwf	MIOS_PARAMETER1
	movlw	MBFM_Ix_AFTERTOUCH_ASSIGN
	movf	PLUSW1, W
	rgoto	MBFM_PARIN_Set

MBFM_PARIN_Cmd_AFTERTOUCH_End
	return


;; --------------------------------------------------------------------------

	;; sends the new parameter to the OPL3 module
	;; IN: value in INDF1
	;;     Ix/DRx/Ex offset in MIOS_PARAMETER3
MBFM_PARIN_Send
	;; don't reinit instruments during sysex write action to save performance
	movlw	0x02
	cpfseq	MBFM_SYSEX_ACTION, BANKED
	rgoto MBFM_PARIN_Send_Ok
	return

MBFM_PARIN_Send_Ok
	movff	MIOS_PARAMETER3, MIOS_PARAMETER1

	;; branch depending on Instrument/Drum/Ensemble
	BRA_IFSET MIOS_PARAMETER3, 7, ACCESS, MBFM_PARIN_Send_Drum
	movlw	MBFM_Ix_ENSEMBLE_BEGIN
	cpfslt	MIOS_PARAMETER3, ACCESS
	rgoto MBFM_PARIN_Send_Ens
MBFM_PARIN_Send_Instr
	movf	INDF1, W
	goto	MBFM_INSTR_SendPar

MBFM_PARIN_Send_Drum
	movf	INDF1, W
	bcf	MIOS_PARAMETER1, 7
	goto	MBFM_DRUM_SendPar

MBFM_PARIN_Send_Ens
	;; patch/bank: re-init patch
	movf	MIOS_PARAMETER3, W
	andlw	0x0e
	bnz	MBFM_PARIN_Send_Ens_NoBP
MBFM_PARIN_Send_Ens_BP
	goto	MBFM_INSTR_Init
	
MBFM_PARIN_Send_Ens_NoBP
	;; (temporary force voice parameter update on a dirty way)
	call	MBFM_INSTR_GetBase
	movlw	MBFM_Ix_FINETUNE
	movwf	MIOS_PARAMETER1
	movf	PLUSW1, W
	goto	MBFM_INSTR_SendPar
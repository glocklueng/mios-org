;; midi_event_pitch_wheel.inc
;; --------------------------
;; PITCH BEND ROUTINE
;; WRITE PITCH BEND TO TONE A, B or C

;; ---------------------------------
;; Pitch Bend  
MIDI_EVNT_IS_Ex
;; JUMPED IN HERE FROM midi_event_jump_table.inc

	;; THER WAS A PITCH BEND MIDI EVENT
	;; ------------------------------------------
	;; 1) So write PITCH BEND Value to temp variables
	;; 1a) Write 30 to MIDI_EVENT_CHANGE_FLAG 
	;;    See ==> user_tick_lcd_redraw.inc
	;; 
	;; (A)
	;; 2.0) Check: does MIDI ch. Tone A Match?
	;; 2.1) IF YES: Perform PITCH BEND (DeTune) Tone A 
	;; 2.2) Write PITCH BEND to AY Chip if Ch. Match
	;;
	;; (B)
	;; 3.0) Check: does MIDI ch. Tone B Match?
	;; 3.1) IF YES: Perform PITCH BEND (DeTune) Tone B
	;; 3.2) Write PITCH BEND to AY Chip 
	;;
	;; (C)
	;; 4.0) Check: does MIDI ch. Tone C Match?
	;; 4.1) IF YES: Perform PITCH BEND (DeTune) Tone C
	;; 4.2) Write PITCH BEND to AY Chip 

;;----------------------------------------------------------

;; 1) write PITCH BEND Value to variables
	;; WRITE PITCH BEND VALUE DATA BYTE2 (0-127)
	movff	MIDI_EVNT_VALUE, AY_TONE_A_TUNE_PITCH_BEND
	movff	MIDI_EVNT_VALUE, AY_TONE_B_TUNE_PITCH_BEND
	movff	MIDI_EVNT_VALUE, AY_TONE_C_TUNE_PITCH_BEND
	;; WRITE CURRENT NOTE ON VALUE (TONE A B C) TO PITCH BEND TEMP variables
	movff 	AY_TONE_A_TUNE_COARSE_MIDI, 	AY_TONE_A_TUNE_COARSE_MIDI_PITCH_BEND_TMP
	movff 	AY_TONE_A_TUNE_FINE_MIDI, 	AY_TONE_A_TUNE_FINE_MIDI_PITCH_BEND_TMP
	movff 	AY_TONE_B_TUNE_COARSE_MIDI, 	AY_TONE_B_TUNE_COARSE_MIDI_PITCH_BEND_TMP
	movff 	AY_TONE_B_TUNE_FINE_MIDI, 	AY_TONE_B_TUNE_FINE_MIDI_PITCH_BEND_TMP
	movff 	AY_TONE_C_TUNE_COARSE_MIDI, 	AY_TONE_C_TUNE_COARSE_MIDI_PITCH_BEND_TMP
	movff 	AY_TONE_C_TUNE_FINE_MIDI, 	AY_TONE_C_TUNE_FINE_MIDI_PITCH_BEND_TMP

;; 1a) Write 30 to MIDI_EVENT_CHANGE_FLAG
	;; BECAUSE THERE HAT BEEN A CC MIDI EVENT 	
	;; WRITE 30 to => MIDI_EVENT_CHANGE_FLAG 
	;; See => user_tick_lcd_redraw.inc
	movlw CC_30_PITCH_BEND
	movwf MIDI_EVENT_CHANGE_FLAG


;; ------[CHECK PITCH BEND EVENT MIDI CH = MIDI CH TONE A or B or C ?]------------

	;; (A)
	;; 2.0) Check: does MIDI ch. Tone A Match?
	;; 2.1) IF YES: Perform PITCH BEND (DeTune) Tone A 
	;; 2.2) Write PITCH BEND to AY Chip if Ch. Match
	
;; ----[ CHECK MIDI CH. TONE A]--------------
MIDI_EVNT_PITCH_BEND_CHK_CH_A
 	movf    MIDI_EVNT_CHANNEL, W
	cpfseq  AY_TONE_A_MIDI_CHANNEL_USER

		; NO - IST'S NOT MIDI CH TONE A, SO GO AND CHECK CH. B
		rgoto MIDI_EVNT_PITCH_BEND_CHK_CH_B
		
		;YES - OK, IT'S MIDI CH TONE A
		rgoto MIDI_EVNT_PITCH_BEND_PITCH_BEND_TONE_A
		
;; -----[CHECK PITCH BEND (+) or (-) ]---------

MIDI_EVNT_PITCH_BEND_PITCH_BEND_TONE_A
	
	;; CHECK IF USER DETUNE IS (+) OR (-)
	;; ----------------------------------
	;; Pitch Bend Value:
	;; [-RANGE[0-63]]| 64=0 | [+RANGE[65-127]]
	movlw	CHK_POS_NEG_VIA_63
	;; TONE A FINE TUNE > 63? 
	cpfsgt 	AY_TONE_A_TUNE_PITCH_BEND	

			;; NO => PITCH BEND = (-)
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_TONE_A_NEGATIVE
			
			;; YES => PITCH BEND = (+) / or 0
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_TONE_A_POSITIVE

;; ----------------------[PITCH = POSITIVE]----------

MIDI_EVNT_PITCH_BEND_PITCH_TONE_A_POSITIVE
	;; PITCH BEND / DETUNE IS POSITIVE (+) - HIGHER FREQUENCY
	;; MIDI EVENT PITCH BEND VALUE RANGE [64 to 127]
	
	;; Pitch Bend Value [64  to 127] 
	;; x2 	   => RANGE [128 to 254]	
	rlncf 	AY_TONE_A_TUNE_PITCH_BEND, F
	
	;; Write PITCH BEND A VALUE to 
	;; TUNE Fine USER 
	;; SEE => TUNE MENU (MAIN MENU 2)	
	movff   AY_TONE_A_TUNE_PITCH_BEND, AY_TONE_A_TUNE_FINE_USER
	
	;; Clear THE OFFSET
	;; WRITE 128 TO WREG
	movlw	CLEAR_OFFSET_128
	;; {PITCH BEND = 128 to 254] - [WREG|(128)]} 
	subwf	AY_TONE_A_TUNE_PITCH_BEND, F
	;; Range => [0 to 126]
	
	;; x2 => Range [0 to 254]
	movf	AY_TONE_A_TUNE_PITCH_BEND, W
	addwf	AY_TONE_A_TUNE_PITCH_BEND, F
	;; +1 => RANGE [1 to 255]
	incf	AY_TONE_A_TUNE_PITCH_BEND, F

	
	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; CHECK IF MIDI TUNE COARSE REG > 3 
	;; 4 to 15 => NO RATIO CHANGE
	movlw	0x03	 
	cpfsgt 	AY_TONE_A_TUNE_COARSE_MIDI	

			;; NO [MIDI TUNE COARSE REG = 0 to 3]
			;; THERE MUST BE A PITCH BEND RATIO CONVERSATION
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_A_POSITIVE_RATIO_CHANGE
			
			;; YES [MIDI TUNE COARSE REG > 3]
			;; THERE MUST BE *NO* PITCH BEND RATIO CHANGE
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_A_POSITIVE_GO_ON

MIDI_EVNT_PITCH_BEND_PITCH_A_POSITIVE_RATIO_CHANGE	
	;; PITCH BEND /16 ==> IF MIDI TUNE COARSE REG == 0
	;; PITCH BEND / 8 ==> IF MIDI TUNE COARSE REG == 1
	;; PITCH BEND / 4 ==> IF MIDI TUNE COARSE REG == 2
	;; PITCH BEND / 2 ==> IF MIDI TUNE COARSE REG == 3
	movf AY_TONE_A_TUNE_COARSE_MIDI, W
	JUMPTABLE_2BYTES 4
		rgoto        MIDI_EVNT_PITCH_BEND_A_POSITIVE_RATIO_CHANGE_DIVIDE_16x 	;; 0  ==> PITCH BAND VALUE /16
		rgoto        MIDI_EVNT_PITCH_BEND_A_POSITIVE_RATIO_CHANGE_DIVIDE_8x 	;; 1  ==> PITCH BAND VALUE /8
		rgoto        MIDI_EVNT_PITCH_BEND_A_POSITIVE_RATIO_CHANGE_DIVIDE_4x 	;; 2  ==> PITCH BAND VALUE /4
		rgoto        MIDI_EVNT_PITCH_BEND_A_POSITIVE_RATIO_CHANGE_DIVIDE_2x 	;; 3  ==> PITCH BAND VALUE /2
	
;; JUMP IN HERE = PITCH BAND /16
MIDI_EVNT_PITCH_BEND_A_POSITIVE_RATIO_CHANGE_DIVIDE_16x
			rrncf	AY_TONE_A_TUNE_PITCH_BEND, F
			bcf	AY_TONE_A_TUNE_PITCH_BEND, 7
;; JUMP IN HERE = PITCH BAND /8
MIDI_EVNT_PITCH_BEND_A_POSITIVE_RATIO_CHANGE_DIVIDE_8x
			rrncf	AY_TONE_A_TUNE_PITCH_BEND, F
			bcf	AY_TONE_A_TUNE_PITCH_BEND, 7
;; JUMP IN HERE = PITCH BAND /4
MIDI_EVNT_PITCH_BEND_A_POSITIVE_RATIO_CHANGE_DIVIDE_4x
			rrncf	AY_TONE_A_TUNE_PITCH_BEND, F
			bcf	AY_TONE_A_TUNE_PITCH_BEND, 7
;; JUMP IN HERE = PITCH BAND /2
MIDI_EVNT_PITCH_BEND_A_POSITIVE_RATIO_CHANGE_DIVIDE_2x
			rrncf	AY_TONE_A_TUNE_PITCH_BEND, F
			bcf	AY_TONE_A_TUNE_PITCH_BEND, 7



MIDI_EVNT_PITCH_BEND_PITCH_A_POSITIVE_GO_ON

	movf AY_TONE_A_TUNE_PITCH_BEND, W		
	;; SUBTRACT PITCH BEND POSITIVE VALUE from "NOTE ON" MIDI VALUE
	;; THE (+) PITCH VALUE WILL BE SUBTRACTED (DON'T BE CONFUSED;)
	;; (+) = HIGHER FREQUENCY = MINUS @ THE AY REG AT THE AY SOUND CHIP REG
	subwf	AY_TONE_A_TUNE_FINE_MIDI_PITCH_BEND_TMP, F
	
		
		;; CHECK: DO WE NEED TO SUBTRACT THE NEGATIVE CARRY BIT
		;; FROM THE MIDI TUNE COARSE REG?
		;; IS [PITCH BEND] IS > W [TONE FINE MIDI] ?
		;; // [PITCH BEND] MUST BE = or < THEN [TONE FINE MIDI]
		;; // otherwise WE HAVE DO DEC -1 @ [COARSE MIDI REG]
		movf 	AY_TONE_A_TUNE_FINE_MIDI, W 	;; W
		cpfsgt	AY_TONE_A_TUNE_PITCH_BEND 	;; F
			
			;; NO
			;; W [MIDI FINE REG] WAS > F [PITCH BEND]
			;; or W [MIDI FINE REG] == F [PITCH BEND]
			;; SO WE CAN GO ON 
			;; WRITE PITCH BEND DATA TO AY CHIP
			rgoto MIDI_EVNT_PITCH_BEND_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_A
		
			;; YES
			;; F [PITCH BEND] WAS > W [MIDI FINE REG]
			;; SO WE HAVE DO DEC -1 [COARSE MIDI REG]
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_POSITIVE_COARSE_REG_A_DEC_VALUE

MIDI_EVNT_PITCH_BEND_PITCH_POSITIVE_COARSE_REG_A_DEC_VALUE
		;; CHECK MIDI COASE REG = 0x00 ? 
		;; 0 = INVALID VALUE 
		clrw	;; WREG = 0
		cpfseq 	AY_TONE_A_TUNE_COARSE_MIDI_PITCH_BEND_TMP

			;; NO - OK COASE REG IS VALID
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_CARRY_COARSE_REG_A_DEC_GO_ON

			;; YES - SO WE CAN NOT DEC. COARSE REG (IS ALLREADY 0x00)
			;; WRITE THE highest PITCH BEND DATA as possible TO THE FINE AND COARSE REG
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_CARRY_WRITE_HIGHEST_PITCH_A


MIDI_EVNT_PITCH_BEND_PITCH_CARRY_COARSE_REG_A_DEC_GO_ON	
		;; DEC DETUNE CARRY FROM FINETUNE REG (MINUS CARY) 
		;; -1 to COASE TUNE REG 
		decf AY_TONE_A_TUNE_COARSE_MIDI_PITCH_BEND_TMP, F
	
		  	;; WRITE PITCH BEND DATA TO AY CHIP
		  	rgoto MIDI_EVNT_PITCH_BEND_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_A


MIDI_EVNT_PITCH_BEND_PITCH_CARRY_WRITE_HIGHEST_PITCH_A
	;; WE CAN NOT DEC. COARSE REG (IS ALLREADY 0x00)
	;; BECAUSE COARSE TUNE REG IS == 0x00
	;; SET FINE TUNE REG TO 0x0A 
	;; (highest TUNE value that is VALID = MIN. VALUE @ AY CHIP REG VALUE)
	movlw FINE_TUNE_MIN_VALUE_B00001010	;; 0x0A / dec 10
	movwf	AY_TONE_A_TUNE_FINE_MIDI_PITCH_BEND_TMP
	
		;; WRITE PITCH BEND DATA TO AY CHIP
		  rgoto MIDI_EVNT_PITCH_BEND_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_A



;; ----------------------[PITCH A == NEGATIVE]--------------------------------------

MIDI_EVNT_PITCH_BEND_PITCH_TONE_A_NEGATIVE
	;; PITCH BEND / DETUNE IS NEGATIVE - LOWER FREQUENCY
	;; WRITE MIDI EVENT PITCH BEND DATA BYTE2 (0-127)
		
	;; Pitch Bend Value [0-63] 
	;; x2 => RANGE [0-126]	
	rlncf 	AY_TONE_A_TUNE_PITCH_BEND, F	
	
	;; Write PITCH BEND A VALUE to 
	;; TUNE Fine USER => TUNE MENU (See MAIN MENU 2)	
	movff   AY_TONE_A_TUNE_PITCH_BEND, AY_TONE_A_TUNE_FINE_USER
	
	;; WRITE 128 TO WREG
	movlw	CLEAR_OFFSET_128
	;; {[WREG|(128)] - [AY_TONE_ABC_TUNE_PITCH_BEND 0 to 126]} 
	subfwb 	AY_TONE_A_TUNE_PITCH_BEND, F
	movf	AY_TONE_A_TUNE_PITCH_BEND, W
	;; => [2 to 128]
		
	;; x2 => RANGE (-) [4 to 256]
	addwf	AY_TONE_A_TUNE_PITCH_BEND, F
	decf	AY_TONE_A_TUNE_PITCH_BEND, F
	;; => (-) RANGE [3 to 255]

	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; CHECK IF MIDI TUNE COARSE REG > 3 
	;; 4 to 15 => NO RATIO CHANGE
	movlw	0x03	 
	cpfsgt 	AY_TONE_A_TUNE_COARSE_MIDI	

			;; NO [MIDI TUNE COARSE REG = 0 to 3]
			;; THERE MUST BE A PITCH BEND RATIO CONVERSATION
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_A_NAGATIVE_RATIO_CHANGE
			
			;; YES [MIDI TUNE COARSE REG > 3]
			;; THERE MUST BE *NO* PITCH BEND RATIO CHANGE
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_GO_ON	

MIDI_EVNT_PITCH_BEND_PITCH_A_NAGATIVE_RATIO_CHANGE
	;; 0) PITCH BEND /16 ==> IF MIDI TUNE COARSE REG == 0
	;; 1) PITCH BEND / 8 ==> IF MIDI TUNE COARSE REG == 1
	;; 2) PITCH BEND / 4 ==> IF MIDI TUNE COARSE REG == 2
	;; 3) PITCH BEND / 2 ==> IF MIDI TUNE COARSE REG == 3
	movf AY_TONE_A_TUNE_COARSE_MIDI, W
	JUMPTABLE_2BYTES 4
		rgoto        MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_RATIO_CHANGE_DIVIDE_16x 	;; 0  ==> PITCH BAND VALUE /16
		rgoto        MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_RATIO_CHANGE_DIVIDE_8x 	;; 1  ==> PITCH BAND VALUE /8
		rgoto        MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_RATIO_CHANGE_DIVIDE_4x 	;; 2  ==> PITCH BAND VALUE /4
		rgoto        MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_RATIO_CHANGE_DIVIDE_2x 	;; 3  ==> PITCH BAND VALUE /2
	
	
;; JUMP IN HERE = PITCH BAND /16
MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_RATIO_CHANGE_DIVIDE_16x
	rrncf	AY_TONE_A_TUNE_PITCH_BEND, F
	bcf	AY_TONE_A_TUNE_PITCH_BEND, 7
;; JUMP IN HERE = PITCH BAND /8
MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_RATIO_CHANGE_DIVIDE_8x
	rrncf	AY_TONE_A_TUNE_PITCH_BEND, F
	bcf	AY_TONE_A_TUNE_PITCH_BEND, 7
;; JUMP IN HERE = PITCH BAND /4
MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_RATIO_CHANGE_DIVIDE_4x
	rrncf	AY_TONE_A_TUNE_PITCH_BEND, F
	bcf	AY_TONE_A_TUNE_PITCH_BEND, 7
;; JUMP IN HERE = PITCH BAND /2
MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_RATIO_CHANGE_DIVIDE_2x
	rrncf	AY_TONE_A_TUNE_PITCH_BEND, F
	bcf	AY_TONE_A_TUNE_PITCH_BEND, 7


MIDI_EVNT_PITCH_BEND_PITCH_A_NEGATIVE_GO_ON			
	;; >> ADD (-) DETUNE to "NOTE ON" VALUE <<
	;; DON'T BE CONFUSED: 
	;; DETUNE NEGATIVE => LOWER  FREQ = HIGHER TUNE REG VALUE
	;; DETUNE POSITIVE => HIGHER FREQ = LOWER TUNE REG VALUE
	movf	AY_TONE_A_TUNE_PITCH_BEND, W
	addwf 	AY_TONE_A_TUNE_FINE_MIDI_PITCH_BEND_TMP, F
	    
	    ;;  carry flag is set when an instruction overflows a register.
	    ;;  branch if carry for INC (+1) the 4 BIT COASE TUNE REG
 	    bc MIDI_EVNT_PITCH_BEND_PITCH_TONE_A_POSITIVE_COARSE_REG_INC_VALUE

			rgoto 	MIDI_EVNT_PITCH_BEND_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_A


MIDI_EVNT_PITCH_BEND_PITCH_TONE_A_POSITIVE_COARSE_REG_INC_VALUE
	;; CHECK MIDI COASE REG = 0x0F ? 
	;; F > BIN xxxx1110 ? => 14 (15 = higest Value) 
	movlw	COARSE_TUNE_MAX_MINUS_1_B00001110
	cpfsgt 	AY_TONE_A_TUNE_COARSE_MIDI_PITCH_BEND_TMP	

		;; NO - OK COASE REG IS VALID
		;; GO ON WITH INC (+1)
		rgoto MIDI_EVNT_PITCH_BEND_PITCH_CARRY_COARSE_A_REG_INC
		
		;; YES - INC OF COARSE REG NOT POSSIBLE
		;; SO WRITE MAXIMUM VALUE TO COARSE and FINE REG. 
		rgoto MIDI_EVNT_PITCH_BEND_WRITE_MAXIMUM_VALUE_TO_FINE_AND_COARSE_REG_TONE_A


MIDI_EVNT_PITCH_BEND_PITCH_CARRY_COARSE_A_REG_INC	
			;; INC COARSE REG ( => CARRY FROM FINE-TUNE REG) 
			;; +1 to COARSE TUNE REG 
			incf AY_TONE_A_TUNE_COARSE_MIDI_PITCH_BEND_TMP, F
	
		  		;; GO AND WRITE TUNE TO AY CHIP
		  		rgoto MIDI_EVNT_PITCH_BEND_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_A

MIDI_EVNT_PITCH_BEND_WRITE_MAXIMUM_VALUE_TO_FINE_AND_COARSE_REG_TONE_A
			;; WRITE MAXIMUM VALUE TO COARSE and FINE REG
			movlw COARSE_TUNE_MAX_VALUE_B00001111
			movwf AY_TONE_A_TUNE_COARSE_MIDI_PITCH_BEND_TMP
			movlw FINE_TUNE_MAX_VALUE_B11010010
			movwf AY_TONE_A_TUNE_FINE_MIDI_PITCH_BEND_TMP
	
				;; GO AND WRITE TUNE TO AY CHIP
		 		rgoto MIDI_EVNT_PITCH_BEND_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_A

;; -----------------------------------------------------------------------------

MIDI_EVNT_PITCH_BEND_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_A
	
	;; -------------[SEND TUNE TONE A DATA TO AY CHIP]--------------
	;; SEND TUNE A TO AY CHIP
	movlw AY_CHIP_ADR_01_TONE_A_FREQUENCY_PERIOD_COARSE	; ADRESS => AY REGISTER
	movwf AY_REG_ADDRESS 					; ADDRESS FOR => AY_SR_Write
	
	movf  AY_TONE_A_TUNE_COARSE_MIDI_PITCH_BEND_TMP, W	; DATA FOR AY REG X
	movwf AY_REG_DATA 				; FOR => AY_SR_Write (WRITE DATA TO AY REG)
	
		call LABEL_AY_SR_Write			; WRITING 8BIT DATA 
							;(AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE	

	movlw AY_CHIP_ADR_00_TONE_A_FREQUENCY_FINE	; ADRESS => AY REGISTER
	movwf AY_REG_ADDRESS 				; ADDRESS FOR => AY_SR_Write

	movf  AY_TONE_A_TUNE_FINE_MIDI_PITCH_BEND_TMP, W		; DATA FOR AY REG X
	movwf AY_REG_DATA 				; FOR => AY_SR_Write (WRITE DATA TO AY REG)
	
		call LABEL_AY_SR_Write			; WRITING 8BIT DATA 
							;; (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE




;; ----[B]--------------

	;; (B)
	;; 3.0) Check: does MIDI ch. Tone B Match?
	;; 3.1) IF YES: Perform PITCH BEND (DeTune) Tone B
	;; 3.2) Write PITCH BEND to AY Chip 


MIDI_EVNT_PITCH_BEND_CHK_CH_B	
	movf    MIDI_EVNT_CHANNEL, W
	cpfseq  AY_TONE_B_MIDI_CHANNEL_USER

		; NO - GO CHECK CH. C
		rgoto MIDI_EVNT_IS_Ex_CHK_CH_C
		
		;YES - OK, IT'S MIDI CH TONE B
		rgoto MIDI_EVNT_IS_Ex_PITCH_BEND_TONE_B


MIDI_EVNT_IS_Ex_PITCH_BEND_TONE_B
	
	;; CHECK IF USER DETUNE IS (+) OR (-)
	;; ----------------------------------
	movlw	CHK_POS_NEG_VIA_63	;; 0x3F
	;; TONE B FINE TUNE > 63? 
	cpfsgt 	AY_TONE_B_TUNE_PITCH_BEND	

			;; NO => PITCH BEND = (-)
			rgoto MIDI_EVNT_IS_Ex_PITCH_TONE_B_NEGATIVE
			
			;; YES => PITCH BEND = (+)
			rgoto MIDI_EVNT_IS_Ex_PITCH_TONE_B_POSITIVE

;; ----------------------[PITCH B == POSITIVE]--------------------------------------

MIDI_EVNT_IS_Ex_PITCH_TONE_B_POSITIVE
	;; PITCH BEND / DETUNE IS POSITIVE (+) - HIGHER FREQUENCY
	
	;; Pitch Bend Value x2 => RANGE [128-254]	
	rlncf 	AY_TONE_B_TUNE_PITCH_BEND, F
	
	;; Write PITCH BEND B VALUE to 
	;; TUNE Fine USER => TUNE MENU (See MAIN MENU 2)	
	movff   AY_TONE_B_TUNE_PITCH_BEND, AY_TONE_B_TUNE_FINE_USER
	
	;; CHECK THE OFFSET
	;; WRITE 128 TO WREG
	movlw	CLEAR_OFFSET_128
	;; {PITCH BEND = 128 to 254] - [WREG|(128)]} WRITE TO => [WREG]
	subwf	AY_TONE_B_TUNE_PITCH_BEND, F
	;; Now You have a value range of [0-126]
	
	;; x2 => [0 to 254]
	movf	AY_TONE_B_TUNE_PITCH_BEND, W
	addwf	AY_TONE_B_TUNE_PITCH_BEND, F
	;; +1 => [1 to 255]
	incf	AY_TONE_B_TUNE_PITCH_BEND, F

	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; CHECK IF MIDI TUNE COARSE REG > 3 
	;; 4 to 15 => NO RATIO CHANGE
	movlw	0x03	 
	cpfsgt 	AY_TONE_B_TUNE_COARSE_MIDI	

			;; NO [MIDI TUNE COARSE REG = 0 to 3]
			;; THERE MUST BE A PITCH BEND RATIO CONVERSATION
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_B_POSITIVE_RATIO_CHANGE
			
			;; YES [MIDI TUNE COARSE REG > 3]
			;; THERE MUST BE *NO* PITCH BEND RATIO CHANGE
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_B_POSITIVE_GO_ON

MIDI_EVNT_PITCH_BEND_PITCH_B_POSITIVE_RATIO_CHANGE
	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; 0) PITCH BEND /16 ==> IF MIDI TUNE COARSE REG == 0
	;; 1) PITCH BEND / 8 ==> IF MIDI TUNE COARSE REG == 1
	;; 2) PITCH BEND / 4 ==> IF MIDI TUNE COARSE REG == 2
	;; 3) PITCH BEND / 2 ==> IF MIDI TUNE COARSE REG == 3
	movf AY_TONE_B_TUNE_COARSE_MIDI, W
	JUMPTABLE_2BYTES 4
		rgoto        MIDI_EVNT_IS_Ex_PITCH_B_POSITIVE_RATIO_CHANGE_DIVIDE_16x 	;; 0  ==> PITCH BAND VALUE /16
		rgoto        MIDI_EVNT_IS_Ex_PITCH_B_POSITIVE_RATIO_CHANGE_DIVIDE_8x 	;; 1  ==> PITCH BAND VALUE /8
		rgoto        MIDI_EVNT_IS_Ex_PITCH_B_POSITIVE_RATIO_CHANGE_DIVIDE_4x 	;; 2  ==> PITCH BAND VALUE /4
		rgoto        MIDI_EVNT_IS_Ex_PITCH_B_POSITIVE_RATIO_CHANGE_DIVIDE_2x 	;; 3  ==> PITCH BAND VALUE /2
	
;; JUMP IN HERE = PITCH BAND /16
MIDI_EVNT_IS_Ex_PITCH_B_POSITIVE_RATIO_CHANGE_DIVIDE_16x
			rrncf	AY_TONE_B_TUNE_PITCH_BEND, F
			bcf	AY_TONE_B_TUNE_PITCH_BEND, 7
;; JUMP IN HERE = PITCH BAND /8
MIDI_EVNT_IS_Ex_PITCH_B_POSITIVE_RATIO_CHANGE_DIVIDE_8x
			rrncf	AY_TONE_B_TUNE_PITCH_BEND, F
			bcf	AY_TONE_B_TUNE_PITCH_BEND, 7
;; JUMP IN HERE = PITCH BAND /4
MIDI_EVNT_IS_Ex_PITCH_B_POSITIVE_RATIO_CHANGE_DIVIDE_4x
			rrncf	AY_TONE_B_TUNE_PITCH_BEND, F
			bcf	AY_TONE_B_TUNE_PITCH_BEND, 7
;; JUMP IN HERE = PITCH BAND /2
MIDI_EVNT_IS_Ex_PITCH_B_POSITIVE_RATIO_CHANGE_DIVIDE_2x
			rrncf	AY_TONE_B_TUNE_PITCH_BEND, F
			bcf	AY_TONE_B_TUNE_PITCH_BEND, 7

;; ----------[RATIO CHANGE END]-------------------------------

MIDI_EVNT_PITCH_BEND_PITCH_B_POSITIVE_GO_ON	
	;; SUBTRACT DETUNE from "NOTE ON" MIDI VALUE 
	;; THE (+) PITCH VALUE WILL BE SUBTRACTED (DON'T BE CONFUSED;)
	;; (+) = HIGHER FREQUENCY = MINUS @ THE AY REG AT THE AY SOUND CHIP REG
	movf AY_TONE_B_TUNE_PITCH_BEND, W	
	subwf	AY_TONE_B_TUNE_FINE_MIDI_PITCH_BEND_TMP, F
	
		;; CHECK: DO WE NEED TO SUBTRACT THE NEGATIVE CARRY BIT
		;; FROM THE MIDI TUNE COARSE REG?
		;; IS [PITCH BEND] IS > W [TONE FINE MIDI] ?
		;; // [PITCH BEND] MUST BE = or < THEN [TONE FINE MIDI]
		;; // otherwise WE HAVE DO DEC -1 @ [COARSE MIDI REG]
		movf 	AY_TONE_B_TUNE_FINE_MIDI, W 	;; W
		cpfsgt	AY_TONE_B_TUNE_PITCH_BEND 	;; F
			
			;; W [MIDI FINE REG] WAS > F [PITCH BEND]
			;; or W [MIDI FINE REG] == F [PITCH BEND]
			;; SO WE CAN GO ON 
			;; WRITE PITCH BEND DATA TO AY CHIP
			rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_B
		
			;; F [PITCH BEND] WAS > W [MIDI FINE REG]
			;; SO WE HAVE DO DEC -1 [COARSE MIDI REG]
			rgoto MIDI_EVNT_IS_Ex_PITCH_POSITIVE_COASE_REG_B_DEC_VALUE

MIDI_EVNT_IS_Ex_PITCH_POSITIVE_COASE_REG_B_DEC_VALUE
		;; CHECK MIDI COASE REG = 0x00 ? 
		;; 0 = INVALID VALUE 
		clrw	;; WREG = 0
		cpfseq 	AY_TONE_B_TUNE_COARSE_MIDI_PITCH_BEND_TMP

			;; NO - OK COASE REG IS VALID
			rgoto MIDI_EVNT_IS_Ex_PITCH_CARRY_COASE_REG_B_DEC_GO_ON

			;; YES - SO WE CAN NOT DEC. COARSE REG (IS ALLREADY 0x00)
			;; WRITE THE highest PITCH BEND DATA as possible TO THE FINE AND COARSE REG
			rgoto MIDI_EVNT_IS_Ex_PITCH_CARRY_WRITE_HIGHEST_PITCH_B


MIDI_EVNT_IS_Ex_PITCH_CARRY_COASE_REG_B_DEC_GO_ON	
	
		;; DEC DETUNE CARRY FROM FINETUNE REG (MINUS CARY) 
		;; -1 to COASE TUNE REG 
		decf AY_TONE_B_TUNE_COARSE_MIDI_PITCH_BEND_TMP, F
	
		  	;; WRITE PITCH BEND DATA TO AY CHIP
		  	rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_B


MIDI_EVNT_IS_Ex_PITCH_CARRY_WRITE_HIGHEST_PITCH_B
	
	;; OUT OF RANGE [TUNE is > 0]
	;; BECAUSE COARSE TUNE REG IS ALREADY = 0x00
	;; SET FINE TUNE REH TO 0x0A (highest TUNE value that is VALID)
	movlw FINE_TUNE_MIN_VALUE_B00001010
	movwf	AY_TONE_B_TUNE_FINE_MIDI_PITCH_BEND_TMP
	
		;; WRITE PITCH BEND DATA TO AY CHIP
		  rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_B


;; ----------------------[PITCH B == NEGATIVE]--------------------------------------

MIDI_EVNT_IS_Ex_PITCH_TONE_B_NEGATIVE
	;; PITCH BEND / DETUNE IS NEGATIVE - LOWER FREQUENCY
	;; WRITE MIDI EVENT PITCH BEND DATA BYTE2 (0-127)
	
	;; Pitch Bend Value [0-63] x2 => RANGE [0-126]	
	rlncf 	AY_TONE_B_TUNE_PITCH_BEND, F	
	
	;; Write PITCH BEND B VALUE to 
	;; TUNE Fine USER => TUNE MENU (See MAIN MENU 2)	
	movff   AY_TONE_B_TUNE_PITCH_BEND, AY_TONE_B_TUNE_FINE_USER
	
	;; WRITE 128 TO WREG
	movlw	CLEAR_OFFSET_128
	;; {[WREG|(128)] - [AY_TONE_ABC_TUNE_PITCH_BEND 0 to 126]} WRITE TO => [WREG]
	subfwb 	AY_TONE_B_TUNE_PITCH_BEND, F
	movf	AY_TONE_B_TUNE_PITCH_BEND, W
	;; => [2 to 128]
		
	;; x2 => RANGE (-) [4 to 256]
	addwf	AY_TONE_B_TUNE_PITCH_BEND, F
	decf	AY_TONE_B_TUNE_PITCH_BEND, F
	;; => (-) RANGE [3 to 255]

	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; CHECK IF MIDI TUNE COARSE REG > 3 
	;; 4 to 15 => NO RATIO CHANGE
	movlw	0x03	 
	cpfsgt 	AY_TONE_B_TUNE_COARSE_MIDI	

			;; NO [MIDI TUNE COARSE REG = 0 to 3]
			;; THERE MUST BE A PITCH BEND RATIO CONVERSATION
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_B_NAGATIVE_RATIO_CHANGE
			
			;; YES [MIDI TUNE COARSE REG > 3]
			;; THERE MUST BE *NO* PITCH BEND RATIO CHANGE
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_B_NEGATIVE_GO_ON	

MIDI_EVNT_PITCH_BEND_PITCH_B_NAGATIVE_RATIO_CHANGE
	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; 0) PITCH BEND /16 ==> IF MIDI TUNE COARSE REG == 0
	;; 1) PITCH BEND / 8 ==> IF MIDI TUNE COARSE REG == 1
	;; 2) PITCH BEND / 4 ==> IF MIDI TUNE COARSE REG == 2
	;; 3) PITCH BEND / 2 ==> IF MIDI TUNE COARSE REG == 3
	movf AY_TONE_B_TUNE_COARSE_MIDI, W
	JUMPTABLE_2BYTES 4
		rgoto        MIDI_EVNT_PITCH_B_NEGATIVE_RATIO_CHANGE_DIVIDE_16x 	;; 0  ==> PITCH BAND VALUE /16
		rgoto        MIDI_EVNT_PITCH_B_NEGATIVE_RATIO_CHANGE_DIVIDE_8x 	;; 1  ==> PITCH BAND VALUE /8
		rgoto        MIDI_EVNT_PITCH_B_NEGATIVE_RATIO_CHANGE_DIVIDE_4x 	;; 1  ==> PITCH BAND VALUE /4
		rgoto        MIDI_EVNT_PITCH_B_NEGATIVE_RATIO_CHANGE_DIVIDE_2x 	;; 2  ==> PITCH BAND VALUE /2
	
;; /16
MIDI_EVNT_PITCH_B_NEGATIVE_RATIO_CHANGE_DIVIDE_16x
	rrncf	AY_TONE_B_TUNE_PITCH_BEND, F
	bcf	AY_TONE_B_TUNE_PITCH_BEND, 7
;; /8
MIDI_EVNT_PITCH_B_NEGATIVE_RATIO_CHANGE_DIVIDE_8x
	rrncf	AY_TONE_B_TUNE_PITCH_BEND, F
	bcf	AY_TONE_B_TUNE_PITCH_BEND, 7
;; /4
MIDI_EVNT_PITCH_B_NEGATIVE_RATIO_CHANGE_DIVIDE_4x
	rrncf	AY_TONE_B_TUNE_PITCH_BEND, F
	bcf	AY_TONE_B_TUNE_PITCH_BEND, 7
;; /2
MIDI_EVNT_PITCH_B_NEGATIVE_RATIO_CHANGE_DIVIDE_2x
	rrncf	AY_TONE_B_TUNE_PITCH_BEND, F
	bcf	AY_TONE_B_TUNE_PITCH_BEND, 7


MIDI_EVNT_PITCH_BEND_PITCH_B_NEGATIVE_GO_ON	
	;; >> ADD (-) DETUNE to "NOTE ON" VALUE <<
	;; DON'T BE CONFUSED: 
	;; DETUNE NEGATIVE => LOWER  FREQ = HIGHER TUNE REG VALUE
	;; DETUNE ADDITIVE => HIGHER FREQ = LOWER TUNE REG VALUE
	clrc	;; clar Carry Bit
	movf	AY_TONE_B_TUNE_PITCH_BEND, W
	addwf 	AY_TONE_B_TUNE_FINE_MIDI_PITCH_BEND_TMP, F

	    ;;  carry flag is set when an instruction overflows a register.
	    ;;  branch if carry for INC the 4 BIT COASE TUNE REG
 	    bc MIDI_EVNT_IS_Ex_PITCH_TONE_B_POSITIVE_COARSE_REG_INC_VALUE

			rgoto 	MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_B


MIDI_EVNT_IS_Ex_PITCH_TONE_B_POSITIVE_COARSE_REG_INC_VALUE
	;; CHECK MIDI COASE REG = 0x0F ? 
	;; F = BIN xxxx1111 = 15 
	movlw	COARSE_TUNE_MAX_VALUE_B00001111	
	cpfseq 	AY_TONE_B_TUNE_COARSE_MIDI_PITCH_BEND_TMP	

			;; NO - OK COASE REG IS VALID
			rgoto MIDI_EVNT_IS_Ex_PITCH_CARRY_COARSE_REG_B_INC

			;; YES - OK NO INC. 
			rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_B


MIDI_EVNT_IS_Ex_PITCH_CARRY_COARSE_REG_B_INC
	
	;; INC PITCH CARRY FROM FINE-TUNE REG 
	;; +1 to COASE TUNE REG 
	incf AY_TONE_B_TUNE_COARSE_MIDI_PITCH_BEND_TMP, F
	
		  ;; GO ON WITH COASE TUNE CHECKING
		  rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_B

;; -----------------------------------------------------------------------------

MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_B
	;; -------------[SEND TUNE TONE A DATA TO AY CHIP]--------------
	;; SEND TUNE B TO AY CHIP
	movlw AY_CHIP_ADR_03_TONE_B_FREQUENCY_PERIOD_COARSE	; ADRESS => AY REGISTER
	movwf AY_REG_ADDRESS 					; ADDRESS FOR => AY_SR_Write
	
	movf  AY_TONE_B_TUNE_COARSE_MIDI_PITCH_BEND_TMP, W	; DATA FOR AY REG X
	movwf AY_REG_DATA 				; FOR => AY_SR_Write (WRITE DATA TO AY REG)
	
		call LABEL_AY_SR_Write			; WRITING 8BIT DATA 
							;(AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE	

	movlw AY_CHIP_ADR_02_TONE_B_FREQUENCY_PERIOD_FINE	; ADRESS => AY REGISTER
	movwf AY_REG_ADDRESS 					; ADDRESS FOR => AY_SR_Write

	movf  AY_TONE_B_TUNE_FINE_MIDI_PITCH_BEND_TMP, W		; DATA FOR AY REG X
	movwf AY_REG_DATA 				; FOR => AY_SR_Write (WRITE DATA TO AY REG)
	
		call LABEL_AY_SR_Write			; WRITING 8BIT DATA 
							;; (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE



;; ----[C]--------------

	;; (C)
	;; 4.0) Check: does MIDI ch. Tone B Match?
	;; 4.1) IF YES: Perform PITCH BEND (DeTune) Tone B
	;; 4.2) Write PITCH BEND to AY Chip 


MIDI_EVNT_IS_Ex_CHK_CH_C
	movf    MIDI_EVNT_CHANNEL, W
	cpfseq  AY_TONE_C_MIDI_CHANNEL_USER

		; NO - IT'S *NOT* MIDI CH TONE A or B or C - SKIP HERE
		rgoto MIDI_EVNT_IS_Ex_EXIT	
		
		;YES - - OK, IT'S MIDI CH TONE C
		; GO ON WITH PITCH BEND @ TONE C
		rgoto MIDI_EVNT_IS_Ex_PITCH_BEND_TONE_C


MIDI_EVNT_IS_Ex_PITCH_BEND_TONE_C
	
	;; CHECK IF USER DETUNE IS (+) OR (-)
	;; ----------------------------------
	movlw	CHK_POS_NEG_VIA_63
	;; TONE C FINE TUNE > 63? 
	cpfsgt 	AY_TONE_C_TUNE_PITCH_BEND	

			;; NO => PITCH BEND = (-)
			rgoto MIDI_EVNT_IS_Ex_PITCH_TONE_C_NEGATIVE
			
			;; YES => PITCH BEND = (+)
			rgoto MIDI_EVNT_IS_Ex_PITCH_TONE_C_POSITIVE

;; ----------------------[PITCH C == POSITIVE]--------------------------------------

MIDI_EVNT_IS_Ex_PITCH_TONE_C_POSITIVE
	;; PITCH BEND / DETUNE IS POSITIVE (+) - HIGHER FREQUENCY
	
	;; Pitch Bend Value x2 => RANGE [128-254]	
	rlncf 	AY_TONE_C_TUNE_PITCH_BEND, F
	
	;; Write PITCH BEND C VALUE to 
	;; TUNE Fine USER => TUNE MENU (See MAIN MENU 2)	
	movff   AY_TONE_C_TUNE_PITCH_BEND, AY_TONE_C_TUNE_FINE_USER
	
	;; CHECK THE OFFSET
	;; WRITE 128 TO WREG
	movlw	CLEAR_OFFSET_128
	;; {PITCH BEND = 128 to 254] - [WREG|(128)]} WRITE TO => [WREG]
	subwf	AY_TONE_C_TUNE_PITCH_BEND, F
	
	;; Now You have a value range of [0-126]
	;; x2 => [0 to 254]
	movf	AY_TONE_C_TUNE_PITCH_BEND, W
	addwf	AY_TONE_C_TUNE_PITCH_BEND, F
	;; +1 => [0 to 255]
	incf	AY_TONE_C_TUNE_PITCH_BEND, F

	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; CHECK IF MIDI TUNE COARSE REG > 3 
	;; 4 to 15 => NO RATIO CHANGE
	movlw	0x03	 
	cpfsgt 	AY_TONE_C_TUNE_COARSE_MIDI	

			;; NO [MIDI TUNE COARSE REG = 0 to 3]
			;; THERE MUST BE A PITCH BEND RATIO CONVERSATION
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_C_POSITIVE_RATIO_CHANGE
			
			;; YES [MIDI TUNE COARSE REG > 3]
			;; THERE MUST BE *NO* PITCH BEND RATIO CHANGE
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_C_POSITIVE_GO_ON

MIDI_EVNT_PITCH_BEND_PITCH_C_POSITIVE_RATIO_CHANGE
	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; 0) PITCH BEND /16 ==> IF MIDI TUNE COARSE REG == 0
	;; 1) PITCH BEND / 8 ==> IF MIDI TUNE COARSE REG == 1
	;; 2) PITCH BEND / 4 ==> IF MIDI TUNE COARSE REG == 2
	;; 3) PITCH BEND / 2 ==> IF MIDI TUNE COARSE REG == 3
	movf AY_TONE_C_TUNE_COARSE_MIDI, W
	JUMPTABLE_2BYTES 4
		rgoto        MIDI_EVNT_IS_Ex_PITCH_C_POSITIVE_RATIO_CHANGE_DIVIDE_16x 	;; 0  ==> PITCH BAND VALUE /16
		rgoto        MIDI_EVNT_IS_Ex_PITCH_C_POSITIVE_RATIO_CHANGE_DIVIDE_8x 	;; 1  ==> PITCH BAND VALUE /8
		rgoto        MIDI_EVNT_IS_Ex_PITCH_C_POSITIVE_RATIO_CHANGE_DIVIDE_4x 	;; 3  ==> PITCH BAND VALUE /4
		rgoto        MIDI_EVNT_IS_Ex_PITCH_C_POSITIVE_RATIO_CHANGE_DIVIDE_2x 	;; 2  ==> PITCH BAND VALUE /2
	
;; /16
MIDI_EVNT_IS_Ex_PITCH_C_POSITIVE_RATIO_CHANGE_DIVIDE_16x
			rrncf	AY_TONE_C_TUNE_PITCH_BEND, F
			bcf	AY_TONE_C_TUNE_PITCH_BEND, 7
;; /8
MIDI_EVNT_IS_Ex_PITCH_C_POSITIVE_RATIO_CHANGE_DIVIDE_8x
			rrncf	AY_TONE_C_TUNE_PITCH_BEND, F
			bcf	AY_TONE_C_TUNE_PITCH_BEND, 7
;; /4
MIDI_EVNT_IS_Ex_PITCH_C_POSITIVE_RATIO_CHANGE_DIVIDE_4x
			rrncf	AY_TONE_C_TUNE_PITCH_BEND, F
			bcf	AY_TONE_C_TUNE_PITCH_BEND, 7
;; /2
MIDI_EVNT_IS_Ex_PITCH_C_POSITIVE_RATIO_CHANGE_DIVIDE_2x
			rrncf	AY_TONE_C_TUNE_PITCH_BEND, F
			bcf	AY_TONE_C_TUNE_PITCH_BEND, 7

;; ----------[END RATIO CHANGE]-----------------------------

MIDI_EVNT_PITCH_BEND_PITCH_C_POSITIVE_GO_ON

	;; SUBTRACT DETUNE from "NOTE ON" MIDI VALUE 
	;; THE (+) PITCH VALUE WILL BE SUBTRACTED (DON'T BE CONFUSED;)
	;; (+) = HIGHER FREQUENCY = MINUS @ THE AY REG AT THE AY SOUND CHIP REG
	movf 	AY_TONE_C_TUNE_PITCH_BEND, W		
	subwf	AY_TONE_C_TUNE_FINE_MIDI_PITCH_BEND_TMP, F
	
		;; CHECK: DO WE NEED TO SUBTRACT THE NEGATIVE CARRY BIT
		;; FROM THE MIDI TUNE COARSE REG?
		;; IS [PITCH BEND] IS > W [TONE FINE MIDI] ?
		;; // [PITCH BEND] MUST BE = or < THEN [TONE FINE MIDI]
		;; // otherwise WE HAVE DO DEC -1 @ [COARSE MIDI REG]
		movf 	AY_TONE_C_TUNE_FINE_MIDI, W 	;; W
		cpfsgt	AY_TONE_C_TUNE_PITCH_BEND 	;; F
			
			;; W [MIDI FINE REG] WAS > F [PITCH BEND]
			;; or W [MIDI FINE REG] == F [PITCH BEND]
			;; SO WE CAN GO ON 
			;; WRITE PITCH BEND DATA TO AY CHIP
			rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_C
		
			;; F [PITCH BEND] WAS > W [MIDI FINE REG]
			;; SO WE HAVE DO DEC -1 [COARSE MIDI REG]
			rgoto MIDI_EVNT_IS_Ex_PITCH_POSITIVE_COASE_REG_C_DEC_VALUE

MIDI_EVNT_IS_Ex_PITCH_POSITIVE_COASE_REG_C_DEC_VALUE
		;; CHECK MIDI COASE REG = 0x00 ? 
		;; 0 = INVALID VALUE 
		clrw	;; WREG = 0
		cpfseq 	AY_TONE_C_TUNE_COARSE_MIDI_PITCH_BEND_TMP

			;; NO - OK COASE REG IS VALID
			rgoto MIDI_EVNT_IS_Ex_PITCH_CARRY_COASE_REG_C_DEC_GO_ON

			;; YES - SO WE CAN NOT DEC. COARSE REG (IS ALLREADY 0x00)
			;; WRITE THE highest PITCH BEND DATA as possible TO THE FINE AND COARSE REG
			rgoto MIDI_EVNT_IS_Ex_PITCH_CARRY_WRITE_HIGHEST_PITCH_C


MIDI_EVNT_IS_Ex_PITCH_CARRY_COASE_REG_C_DEC_GO_ON	
	
		;; DEC DETUNE CARRY FROM FINETUNE REG (MINUS CARY) 
		;; -1 to COASE TUNE REG 
		decf AY_TONE_C_TUNE_COARSE_MIDI_PITCH_BEND_TMP, F
	
		  	;; WRITE PITCH BEND DATA TO AY CHIP
		  	rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_C


MIDI_EVNT_IS_Ex_PITCH_CARRY_WRITE_HIGHEST_PITCH_C
	
	;; OUT OF RANGE [TUNE is > 0]
	;; BECAUSE COARSE TUNE REG IS == 0x00
	;; SET FINE TUNE REH TO 0x0A (highest value that is VALID)
	movlw FINE_TUNE_MIN_VALUE_B00001010
	movwf	AY_TONE_C_TUNE_FINE_MIDI_PITCH_BEND_TMP
	
		;; WRITE PITCH BEND DATA TO AY CHIP
		  rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_C



;; ----------------------[PITCH C == NEGATIVE]--------------------------------------

MIDI_EVNT_IS_Ex_PITCH_TONE_C_NEGATIVE
	;; PITCH BEND / DETUNE IS NEGATIVE - LOWER FREQUENCY
	;; WRITE MIDI EVENT PITCH BEND DATA BYTE2 (0-127)
		
	;; Pitch Bend Value [0-63] x2 => RANGE [0-126]	
	rlncf 	AY_TONE_C_TUNE_PITCH_BEND, F	
	
	;; Write PITCH BEND C VALUE to 
	;; TUNE Fine USER => TUNE MENU (See MAIN MENU 2)	
	movff   AY_TONE_C_TUNE_PITCH_BEND, AY_TONE_C_TUNE_FINE_USER
	
	;; WRITE 128 TO WREG
	movlw	CLEAR_OFFSET_128
	;; {[WREG|(128)] - [AY_TONE_ABC_TUNE_PITCH_BEND 0 to 126]} WRITE TO => [WREG]
	subfwb 	AY_TONE_C_TUNE_PITCH_BEND, F
	movf	AY_TONE_C_TUNE_PITCH_BEND, W
	;; => [2 to 128]
		
	;; x2 => RANGE (-) [4 to 256]
	addwf	AY_TONE_C_TUNE_PITCH_BEND, F
	decf	AY_TONE_C_TUNE_PITCH_BEND, F
	;; => (-) RANGE [3 to 255]

	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; CHECK IF MIDI TUNE COARSE REG > 3 
	;; 4 to 15 => NO RATIO CHANGE
	movlw	0x03	 
	cpfsgt 	AY_TONE_C_TUNE_COARSE_MIDI	

			;; NO [MIDI TUNE COARSE REG = 0 to 3]
			;; THERE MUST BE A PITCH BEND RATIO CONVERSATION
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_C_NAGATIVE_RATIO_CHANGE
			
			;; YES [MIDI TUNE COARSE REG > 3]
			;; THERE MUST BE *NO* PITCH BEND RATIO CHANGE
			rgoto MIDI_EVNT_PITCH_BEND_PITCH_C_NEGATIVE_GO_ON	

MIDI_EVNT_PITCH_BEND_PITCH_C_NAGATIVE_RATIO_CHANGE
	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; 0) PITCH BEND /16 ==> IF MIDI TUNE COARSE REG == 0
	;; 1) PITCH BEND / 8 ==> IF MIDI TUNE COARSE REG == 1
	;; 2) PITCH BEND / 4 ==> IF MIDI TUNE COARSE REG == 2
	;; 3) PITCH BEND / 2 ==> IF MIDI TUNE COARSE REG == 3
	movf AY_TONE_C_TUNE_COARSE_MIDI, W
	JUMPTABLE_2BYTES 4
		rgoto        MIDI_EVNT_PITCH_C_NEGATIVE_RATIO_CHANGE_DIVIDE_16x 	;; 0  ==> PITCH BAND VALUE /16
		rgoto        MIDI_EVNT_PITCH_C_NEGATIVE_RATIO_CHANGE_DIVIDE_8x 	;; 1  ==> PITCH BAND VALUE /8
		rgoto        MIDI_EVNT_PITCH_C_NEGATIVE_RATIO_CHANGE_DIVIDE_4x 	;; 1  ==> PITCH BAND VALUE /4
		rgoto        MIDI_EVNT_PITCH_C_NEGATIVE_RATIO_CHANGE_DIVIDE_2x 	;; 2  ==> PITCH BAND VALUE /2

;; /16
MIDI_EVNT_PITCH_C_NEGATIVE_RATIO_CHANGE_DIVIDE_16x
	rrncf	AY_TONE_C_TUNE_PITCH_BEND, F
	bcf	AY_TONE_C_TUNE_PITCH_BEND, 7
;; /8
MIDI_EVNT_PITCH_C_NEGATIVE_RATIO_CHANGE_DIVIDE_8x
	rrncf	AY_TONE_C_TUNE_PITCH_BEND, F
	bcf	AY_TONE_C_TUNE_PITCH_BEND, 7
;; /4
MIDI_EVNT_PITCH_C_NEGATIVE_RATIO_CHANGE_DIVIDE_4x
	rrncf	AY_TONE_C_TUNE_PITCH_BEND, F
	bcf	AY_TONE_C_TUNE_PITCH_BEND, 7
;; /2
MIDI_EVNT_PITCH_C_NEGATIVE_RATIO_CHANGE_DIVIDE_2x
	rrncf	AY_TONE_C_TUNE_PITCH_BEND, F
	bcf	AY_TONE_C_TUNE_PITCH_BEND, 7


MIDI_EVNT_PITCH_BEND_PITCH_C_NEGATIVE_GO_ON	
	;; >> ADD (-) DETUNE to "NOTE ON" VALUE <<
	;; DON'T BE CONFUSED: 
	;; DETUNE NEGATIVE => LOWER  FREQ = HIGHER TUNE REG VALUE
	;; DETUNE ADDITIVE => HIGHER FREQ = LOWER TUNE REG VALUE
	clrc
	movf	AY_TONE_C_TUNE_PITCH_BEND, W
	addwf 	AY_TONE_C_TUNE_FINE_MIDI_PITCH_BEND_TMP, F
	    
	    ;;  carry flag is set when an instruction overflows a register.
	    ;;  branch if carry for INC the 4 BIT COASE TUNE REG
 	    bc MIDI_EVNT_IS_Ex_PITCH_TONE_C_POSITIVE_COARSE_REG_INC_VALUE

			rgoto 	MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_C


MIDI_EVNT_IS_Ex_PITCH_TONE_C_POSITIVE_COARSE_REG_INC_VALUE
	;; CHECK MIDI COASE REG = 0x0F ? 
	;; F = BIN xxxx1111 = 15 
	movlw	COARSE_TUNE_MAX_VALUE_B00001111
	cpfseq 	AY_TONE_C_TUNE_COARSE_MIDI_PITCH_BEND_TMP	

			;; NO - OK COASE REG IS VALID
			rgoto MIDI_EVNT_IS_Ex_PITCH_CARRY_COARSE_REG_C_INC

			;; YES - OK NO INC. 
			rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_C


MIDI_EVNT_IS_Ex_PITCH_CARRY_COARSE_REG_C_INC
	
	;; INC PITCH CARRY FROM FINE-TUNE REG 
	;; +1 to COASE TUNE REG 
	incf AY_TONE_C_TUNE_COARSE_MIDI_PITCH_BEND_TMP, F
	
		  ;; GO ON WITH COASE TUNE CHECKING
		  rgoto MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_C

;; -----------------------------------------------------------------------------





MIDI_EVNT_IS_Ex_WRITE_PITCH_BEND_TO_AY_CHIP_TONE_C


	;; -------------[SEND TUNE TONE A DATA TO AY CHIP]--------------
	;; SEND TUNE C TO AY CHIP
	movlw AY_CHIP_ADR_05_TONE_C_TONE_PERIOD_COARSE	; ADRESS => AY REGISTER
	movwf AY_REG_ADDRESS 				; ADDRESS FOR => AY_SR_Write
	
	movf  AY_TONE_C_TUNE_COARSE_MIDI_PITCH_BEND_TMP, W	; DATA FOR AY REG X
	movwf AY_REG_DATA 				; FOR => AY_SR_Write (WRITE DATA TO AY REG)
	
		call LABEL_AY_SR_Write			; WRITING 8BIT DATA 
							;(AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE	

	movlw AY_CHIP_ADR_04_TONE_C_FREQUENCY_PERIOD_FINE	; ADRESS => AY REGISTER
	movwf AY_REG_ADDRESS 				; ADDRESS FOR => AY_SR_Write

	movf  AY_TONE_C_TUNE_FINE_MIDI_PITCH_BEND_TMP, W		; DATA FOR AY REG X
	movwf AY_REG_DATA 				; FOR => AY_SR_Write (WRITE DATA TO AY REG)
	
		call LABEL_AY_SR_Write			; WRITING 8BIT DATA 
							;; (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE


;; --------------------[END: CHECK TONE A B C MIDI CHANNEL]-----------------

MIDI_EVNT_IS_Ex_EXIT	
	
	;; Exit
	return
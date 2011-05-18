;; ----------------------------------------
;; # note_on_pipeline_a.inc                #
;; ----------------------------------------
;;
;; FUNCTION:
;; ---------
;; DO *NOTE ON* PROCESSING @ TONE A 
;; WITH ALL necessary parameters
;;
;; 
;; DETAILS:
;; --------
;; THERE HAD BEEN A *NOTE ON* MIDI EVENT
;; JUMP IN HERE FROM note_to_hz.inc
;; TUNE WAS WRITTEN TO MIOS_PARAMETER1/2
;; COARSE TUNE TO MIOS_PARAMETER1
;; FINE  TUNE TO MIOS_PARAMETER2
;;
;; 
;; PIPELINE WORKFLOW:
;; ------------------
;; * Check MIDI CH. = Tone A
;;      IF MIDI CH. MATCH: SWITCH TONE A (+ USER NOISE A) ON
;;
;; * CHECK IF USER ENVELOPE MODE TONE A IS ON
;; 	ON => WRITE ENVELOPE SHAPE TO AY CHIP
;; 	OFF=> DO NOT WRITE ENVELOPE SHAPE TO AY CHIP
;;
;; * CHECK DETUNE (PITCH BEND)
;; 	* Coarse
;; 	* Fine 
;;
;; * SEND TUNE TONE A to AY CHIP (incl. Detune (PITCH BEND))
;;
;; * CHECK IF VELOCITY TO VOLUME IS ON
;; 	yes: write VELOCITY to VOLUME A
;; 	no:  write USER VOLUME TO VOLUME TONE A
;;
;;
;; 		TONE A, B, C WORKFLOW
;; 		---------------------
;; 	midi_evnt_note_on_pipeline_tone_a.inc
;; 			||
;;			\/
;;	midi_evnt_note_on_pipeline_tone_b.inc
;; 			||
;;			\/
;;	midi_evnt_note_on_pipeline_tone_c.inc
;;			||
;;			\/
;;		note_on_write_ay_reg7.inc

MIDI_EVNT_NOTE_ON_CHECK_MIDI_CHANNEL_TONE_A_B_C

;; ---------[START TONE A WORKFLOW]------------	
MIDI_EVNT_NOTE_ON_CHECK_MIDI_CHANNEL_A
 	;; CHECK IF NOTE ON EVENT = TONE A MIDI CHANNEL
 	;; IS MIDI EVENT MIDI CHANNEL = MIDI CHANNEL OF TONE A?
 	movf MIDI_EVNT_CHANNEL, W
 	cpfseq AY_TONE_A_MIDI_CHANNEL_USER
			
			; NO, NOT MIDI CH USER TONE A  - GO AND CHECK B
			goto MIDI_EVNT_NOTE_ON_CHECK_MIDI_CHANNEL_B
 		
 		;; YES
 		;; THERE IS A NOTE ON MIDI EVENT @ THE TONE A MIDI CHANNEL
		;; WRITE MIDI Hz VALUE to TUNE TONE A 
		movff MIOS_PARAMETER1, AY_TONE_A_TUNE_COARSE_MIDI
		movff MIOS_PARAMETER2, AY_TONE_A_TUNE_FINE_MIDI
		
		;; MIDI FILTER:
		;; MIDI SWITCH TONE A and NOISE A *ON*
		;; CLEAR BIT0, BIT3
		;; => FILTER FOR REG 7
		;; => SWITCH ON TONE A, NOISE A  
		bcf	AY_TONE_ABC_MIDI_ON_OFF, BIT0_TONE_A_ON_OFF
		bcf	AY_TONE_ABC_MIDI_ON_OFF, BIT3_NOISE_A_ON_OFF

		;; WRITE CURRENT *NOTE ON VALUE* @ MIDI Ch Tone A
		;; FOR CHCKING if the Note OFF value correlates with the last
		;; NOTE ON value (importend for MIDI KEYBOARD HANDLING of delayed NOTE OFF values) 
		;; processing @ note_off.inc
      		movff     MIDI_EVNT1, CURRENT_MIDI_EVENT_NOTE_ON_OFF_A


	;; CHECK IF FX A = ON or OFF
	btfss FX_USER_ON_OFF_ABC, BIT0_FX_ON_OFF_TONE_A
			;; NO, BIT0 IS NOT SET - Fx @ TONE A = off
			;; DO NOT PERFORM Fx Note On Routines
			rgoto  MIDI_EVNT_NOTE_ON_TONE_A_CHCK_ENVELOPE_MODE
	
		;; YES - DO Fx Note On Routines 
		;; #####################################################
		;; ### hier noch FX USER ON / OFF TONE ABC einbauen ####
		;; For Fx Tunes #123
		;; Save the last 3 Note Values
		;; => @ fx_pipeline.inc
		call 	WRITE_FX_TUNE_1_2_3	

		;; EVERY NEW NOTE ON EVENT IS A NEW Fx SESSION
		;; CHANGE (inc) THE FX SESSION (WILL RESET FX POS)
		incf FX_MIDI_NOTE_ON_SESSION, F
		
		;; SET FX MIDI NOTE ON FLAG @ TONE A
		bsf Fx_MIDI_NOTE_ON_OR_OFF, BIT0_TONE_A_ON_OFF
		
		;; ######################################################


MIDI_EVNT_NOTE_ON_TONE_A_CHCK_ENVELOPE_MODE

		;; -------------[ENVELOPE MODE?]------------------------
		;; CHECK: IS ENVELOPE MODE @ TONE A ON?
		;; BIT 4 SET 	= ENV. MODE ON
		;; BIT 4 CLEAT 	= ENV. MODE OFF
		btfsc AY_R8_CH_A_AMPLITUDE, BIT4_ENVELOPE_ON_OFF
        		;; YES - BIT 4 is SET - ENV. MODE ON
        		;; GOTO WRITE ENV REG AY CHIP
        		rgoto MIDI_EVNT_NOTE_ON_MIDI_CHANNEL_TONE_A_ENV_MODE
			;; NO - BIT 4 is CLEAR - ENV. MODE OFF
			;; NO NEED FOR WRITING AY REG 13
			;; GO ON AND CHECK TONE A DETUNE
			rgoto MIDI_EVNT_NOTE_ON_CHECK_DETUNE_A

	
MIDI_EVNT_NOTE_ON_MIDI_CHANNEL_TONE_A_ENV_MODE
		;; -------------[WRITE ENVELOPE MODE ON]------------------------
		;; WRITE ENV. SHAPE CYCLE
		;; SEND ENV DATA TO AY REG 13 (ENV. SHAPE/Cycle REG)
		movlw AY_CHIP_ADR_13_ENVELOPE_SHAPE_AND_CYCLE ; REG ADRESS of AY REGISTER
		movwf AY_REG_ADDRESS 		
		;; WRITE ENVELOPE SHAPE CYCLE DATA TO AY CHIP
		movff AY_R13_ENV_SHAPE_CYCLE, AY_REG_DATA

		;; --------------[SEND DATA TO AY REG 13]-----------------------------------------------------
		;; WRITING 8BIT DATA (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE
		call LABEL_AY_SR_Write	
		;; ==========================================================================================
			

;; -------------[DETUNE A]------------------
MIDI_EVNT_NOTE_ON_CHECK_DETUNE_A


;; -------------[CHECK DETUNE A (PITCH BEND)]------------------------

;; * CHECK DETUNE (PITCH BEND)
;; 	* Coarse
;; 	* Fine 

;; -------------[CHECK COARSE DETUNE TONE A]---------------------------------------
MIDI_EVNT_NOTE_ON_CHECK_TONE_A_COARSE_DETUNE
	;; CHECK USER COARSE DETUNE @ TONE A?
	;: USER COARSE RANGE:
	;; (-) RANGE = [0 to 6]|OFFSET/ZERO = [7]| (+) RANGE = [8 to 15]
	;;
	;; AY_TONE_A_TUNE_COARSE_USER | COARSE DETUNE
	;; ...
	;; 3 ========================>| -4
	;; 4 ========================>| -3
	;; 5 ========================>| -2
	;; 6 ========================>| -1
	;; 7 ========================>|  0
	;; 8 ========================>| +1
	;; 9 ========================>| +2
	
	;; IS USER COARSE TUNE = [7] ?
	movlw	OFFSET_COARSE_TUNE_IS_7
	cpfseq 	AY_TONE_A_TUNE_COARSE_USER	
		;; NO: NOT 7, SO COARSE USER *DETUNE IS GIVEN*
		rgoto MIDI_EVNT_NOTE_ON_TONE_A_CHECK_COARSE_DETUNE_PLUS_OR_MINUS
		;; YES: COARSE DETUNE = 7, SO *NO COARSE DETUNE IS GIVEN*
		;; GO ON WITH DETUNE FINE
		goto 	MIDI_EVNT_NOTE_ON_CHECK_TONE_A_DETUNE_FINE


MIDI_EVNT_NOTE_ON_TONE_A_CHECK_COARSE_DETUNE_PLUS_OR_MINUS
		;; CHECK COARSE DETUNE = (+) or (-)
		;; COARSE TUNE IS <> 7 SO COARSE REG DETUNE
		;; IS GIVEN @ TONE A
		;; RANGE (-) = [0-6] |(No DETUNE) = [7] | (+) = [8-15]
		movlw	PROOF_POSITIVE_OR_NEGATIVE_VIA_0X06
		cpfsgt 	AY_TONE_A_TUNE_COARSE_USER	
			;; NO 
			;; SO COARSE DETUNE = (-) = RANGE [0 to 6]
			rgoto MIDI_EVNT_NOTE_ON_TONE_A_COARSE_DETUNE_IS_MINUS
			;; YES
			;; SO COARSE DETUNE = (+) = RANGE [8 to 15]
			rgoto MIDI_EVNT_NOTE_ON_TONE_A_COARSE_DETUNE_IS_PLUS
			

MIDI_EVNT_NOTE_ON_TONE_A_COARSE_DETUNE_IS_MINUS
	;; DETUNE COARSE IS NEGATIVE
	;; -------------------------
	;; calculate COARSE DETUNE (-) VALUE:
	;; WREG [(0x07 (+1 [PLUS_1_CARRY_BIT_KILLER])] - F [(0x00 to 0x06)| (+1 Carry BIT (of subfwb))] 
	;; WRITE RESULT TO => [WREG (0x07 to 0x01)]
	;; TO GET THE (-) COARSE TUNE RESULT [RANGE: 0x07 to 0x01]
	
	
	;; (1) MOVE OFFSET TO WREG and
	;; (3)Subtract f from WREG 
	;; the CARRY bit will allway be set
	;; because WREG is (allways in this case) > f) 
	;; (2) SO WE NEED TO ADD +1 TO WREG
	;; for [+1 WREG] - [+1 Carry BIT] = 0 (the needed offset)
	movlw	OFFSET_COARSE_TUNE_IS_7 ;; (1)
	addlw 	PLUS_1_CARRY_BIT_KILLER ;; (2)
	subfwb	AY_TONE_A_TUNE_COARSE_USER, W ;; (3)
	
	;; ADD (*) COARSE MINUS DETUNE [WREG (RANGE 0x01 to 0x07)] 
	;; TO THE COARSE "NOTE ON VALUE" 
	;; DON'T BE CONFUSED (*):
	;; DETUNE NEGATIVE => LOWER  FREQ = HIGHER TUNE REG VALUE
	;; DETUNE ADDITIVE => HIGHER FREQ = LOWER TUNE REG VALUE
	addwf	AY_TONE_A_TUNE_COARSE_MIDI, F
	
		;; TUNE COARSE TUNE RANGE = BIN 00000000 to 00001111 (DEC. 0 to 15)
		;; TUNE COARSE TUNE > BIN 00001111? 
		movlw	NIBBLE_B00001111
		cpfsgt 	AY_TONE_A_TUNE_COARSE_MIDI	
						;; NO
						;; OK, GO ON WITH DETUNE FINE
						goto 	MIDI_EVNT_NOTE_ON_CHECK_TONE_A_DETUNE_FINE

			;; YES - COASE TUNE REG VALUE IS > 0x0F NO VALID VALUE FOR THE AY CHIP!
			;; SWITCH TUNE COARSE REG TO 0x0F
			;; GO AND WRITE MAXIMUM VALUE TO COARSE and FINE REG
			rgoto 	MIDI_EVNT_NOTE_ON_DETUNE_NEGATIVE_SET_COARSE_TUNE_A_TO_MAX_VALUE


MIDI_EVNT_NOTE_ON_DETUNE_NEGATIVE_SET_COARSE_TUNE_A_TO_MAX_VALUE
 				;; WRITE MAXIMUM VALUE TO COARSE and FINE REG
 				movlw COARSE_TUNE_MAX_VALUE_B00001111
 				movwf AY_TONE_A_TUNE_COARSE_MIDI
 				movlw FINE_TUNE_MAX_VALUE_B11010010
 				movwf AY_TONE_A_TUNE_FINE_MIDI

		    				;; GO ON WITH DETUNE FINE
						rgoto 	MIDI_EVNT_NOTE_ON_CHECK_TONE_A_DETUNE_FINE

;; ------------------------[DETUNE COARSE POSITIVE]----------------------------

MIDI_EVNT_NOTE_ON_TONE_A_COARSE_DETUNE_IS_PLUS
	;; DETUNE IS POSITIVE
	movlw	OFFSET_COARSE_TUNE_IS_7
	subwf	AY_TONE_A_TUNE_COARSE_USER, W		; - 0x07 (OFFSET IN W REG)
	movwf	AY_DETUNE_TEMP				; SAVE (+) COARSE DETUNE VALUE

	;; NOW COARSE DETUNE IS IN WREG
	;; (+) COARSE DETUNE RANGE => [0x01 to 0x08]		
	;; COMPARE W REG WITH COARSE TUNE MIDI VALUE
	;; IS THE COASE MIDI VALUE > COASE DETUNE VALUE IN W REG
	;; NEXT STEP: SUBTRACT [(+) DETUNE COARSE] FROM [MIDI COARSE TUNE]
	;; BUT WE MUST FIRS CHECK IF THERE WILL BE A VALID VALUE
	;; COMPARE W REG [(+) DETUNE COARSE] WITH [COARSE TUNE MIDI] 
	;; IS (F) [MIDI COARSE TUNE] > (W) [(+) DETUNE COARSE]?
	cpfsgt 	AY_TONE_A_TUNE_COARSE_MIDI	
		;; IS (F) [MIDI COARSE TUNE] > (W) [(+) DETUNE COARSE]?
		;; NO - SO SET TUNE REGS TO MIN. VALUE	= HIGHEST TUNE
		rgoto 	MIDI_EVNT_NOTE_ON_SET_MIDI_TUNE_A_TO_HIGHEST_TUNE

		;; IS (F) [MIDI COARSE TUNE] > (W) [(+) DETUNE COARSE]?
		;; YES - OK GO ON
		rgoto 	MIDI_EVNT_NOTE_ON_TONE_A_COARSE_DETUNE_ADDITIVE_GO_ON


MIDI_EVNT_NOTE_ON_SET_MIDI_TUNE_A_TO_HIGHEST_TUNE
			;; SET TUNE REGS TO HIGHEST FREQUENCY POSSIBLE
			;; THAT MEANS TO SET TUNE REGS TO MIN. VALUE
			;; MIN VALUE = HIGHEST TUNE
			movlw  COARSE_TUNE_MIN_VALUE_B00000000
			movwf  AY_TONE_A_TUNE_COARSE_MIDI
			movlw  FINE_TUNE_MIN_VALUE_B00001010
			movwf  AY_TONE_A_TUNE_FINE_MIDI
						;; GO ON WITH DETUNE FINE
						rgoto 	MIDI_EVNT_NOTE_ON_CHECK_TONE_A_DETUNE_FINE

MIDI_EVNT_NOTE_ON_TONE_A_COARSE_DETUNE_ADDITIVE_GO_ON
			;; ADD THE (+) USER COARSE DETUNE FREQUENCY VALUE NOW
			;; THIS MEANS TO SUBTRACT COARSE DETUNE VALUE from the COARSE "NOTE ON" MIDI VALUE 
			;; YES THE POSITIVE VALUE WILL BE SUBTRACTED (DON'T BE CONFUSED;)
			;; TUNE FREQUENCY "+" = "-" @ TUNE REGISTER
			movf 	AY_DETUNE_TEMP, W
			subwf	AY_TONE_A_TUNE_COARSE_MIDI, F
					
						;; GO ON WITH DETUNE FINE
						rgoto 	MIDI_EVNT_NOTE_ON_CHECK_TONE_A_DETUNE_FINE

;; -------------[END OF DETUNE COASE TONE A ]--------------	

;; -------------[CHECK DETUNE FINE Tone A   ]---------------
MIDI_EVNT_NOTE_ON_CHECK_TONE_A_DETUNE_FINE
	;;CHECK USER DETUNE (PITCH BEND)
	movlw	OFFSET_FINE_TUNE_IS_128
	;; TONE A FINE TUNE = 128? 
	;; 128 = INITIAL VALUE = NO USER DETUNE
	cpfseq 	AY_TONE_A_TUNE_FINE_USER 	
			;; NO, NOT 128 - SO *DETUNE IS GIVEN*
			;; START WITH TONE A - CHECK USER TONE A - FINE TUNE
			rgoto MIDI_EVNT_NOTE_ON_CHECK_DETUNE_A_FINE_IS_PLUS_OR_MINUS

			;; YES AY_TONE_A_TUNE_FINE_USER = 128 *NO DETUNE IS GIVEN*
			;; Go AND WRITE TUNE TO AY CHIP
			rgoto MIDI_EVNT_NOTE_ON_TONE_A_SEND_TUNE_TO_AY_CHIP


MIDI_EVNT_NOTE_ON_CHECK_DETUNE_A_FINE_IS_PLUS_OR_MINUS
	;; CHECK IF USER DETUNE IS (+) OR (-)
	movlw	PROOF_POSITIVE_OR_NEGATIVE_VIA_0X7F
	;; TONE A FINE TUNE > 127? 
	cpfsgt 	AY_TONE_A_TUNE_FINE_USER	

			;; NO => USER FINE DETUNE => (-)
			rgoto MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_MINUS
			
			;; YES => USER FINE DETUNE => (+)
			rgoto MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_PLUS

;; -----------[PITCH BEND TONE A == NEGATIVE]--------------
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_MINUS	
	;; DETUNE IS NEGATIVE - LOWER FREQUENCY
	;; (-) RANGE OF: AY_TONE_A_TUNE_FINE_USER = [0   to 127] DETUNE IS NEGATIVE (HERE)
	;; (+) RANGE OF: AY_TONE_A_TUNE_FINE_USER = [128 to 255] DETUNE IS POSITIVE
	;; (NO DETUNE) : AY_TONE_A_TUNE_FINE_USER = [128]
	
	;; WRITE 128 TO WREG
	;; WREG [(128) + (1 (CARRY KILLER))] - [[AY_TONE_A_TUNE_FINE_USER |(0 to 127)] + [+1 (CARRY)]]
	;; WRITE RESULT TO => [WREG]
	movlw	OFFSET_FINE_TUNE_IS_128	
	addlw 	PLUS_1_CARRY_BIT_KILLER
	subfwb	AY_TONE_A_TUNE_FINE_USER, W 
	;; WRITE RESULT TO [WREG] TO => [AY_DETUNE_TEMP]
	movwf	AY_DETUNE_TEMP
	;; [AY_DETUNE_TEMP] RANGE => [1 to 128]
	
	;; So the [USER DETUNE RANGE] => [-1 to -128] 
	;; Expand the (-) RANGE to 8BIT (255):
	;; 2x (-1 to -128) => (-2 to -256(!))
	addwf	AY_DETUNE_TEMP, F
	;; -1 | => (1 to 255)
	decf	AY_DETUNE_TEMP, F
	;; WRITE [(-) DETUNE FINE] TO [WREG]
	;; (-) RANGE => [1 to 255]

;; ------[DETUNE NEGATIVE RATIO CHANGE?]------------------

	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; CHECK IF MIDI TUNE COARSE REG > 3 
	;; 4 to 15 => NO RATIO CHANGE
	movlw	0x03	 
	cpfsgt 	AY_TONE_A_TUNE_COARSE_MIDI	

			;; NO [MIDI TUNE COARSE REG = 0 to 3]
			;; THERE MUST BE A PITCH BEND RATIO CONVERSATION
			rgoto MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE
			
			;; YES [MIDI TUNE COARSE REG > 3]
			;; THERE MUST BE *NO* PITCH BEND RATIO CHANGE
			rgoto MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_GO_ON	

MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE
	;; 0) PITCH BEND /16 ==> IF MIDI TUNE COARSE REG == 0
	;; 1) PITCH BEND / 8 ==> IF MIDI TUNE COARSE REG == 1
	;; 2) PITCH BEND / 4 ==> IF MIDI TUNE COARSE REG == 2
	;; 3) PITCH BEND / 2 ==> IF MIDI TUNE COARSE REG == 3
	movf AY_TONE_A_TUNE_COARSE_MIDI, W
	JUMPTABLE_2BYTES 4
		rgoto        MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE_DIVIDE_16x 	;; 0  ==> PITCH BAND VALUE /16
		rgoto        MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE_DIVIDE_8x 	;; 1  ==> PITCH BAND VALUE /8
		rgoto        MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE_DIVIDE_4x 	;; 2  ==> PITCH BAND VALUE /4
		rgoto        MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE_DIVIDE_2x 	;; 3  ==> PITCH BAND VALUE /2
	
;; ADJUST PITCH BEND RATIO
;; JUMP IN HERE = PITCH BAND /16
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE_DIVIDE_16x
		rrncf	AY_DETUNE_TEMP, F
		bcf	AY_DETUNE_TEMP, 7
;; JUMP IN HERE = PITCH BAND /8
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE_DIVIDE_8x
		rrncf	AY_DETUNE_TEMP, F
		bcf	AY_DETUNE_TEMP, 7
;; JUMP IN HERE = PITCH BAND /4
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE_DIVIDE_4x
		rrncf	AY_DETUNE_TEMP, F
		bcf	AY_DETUNE_TEMP, 7
;; JUMP IN HERE = PITCH BAND /2
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_RATIO_CHANGE_DIVIDE_2x
		rrncf	AY_DETUNE_TEMP, F
		bcf	AY_DETUNE_TEMP, 7
	
;; ------[DETUNE RATIO CHANGE END]------------------

MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_NEGATIVE_GO_ON	
	;; >> ADD (-) DETUNE to "NOTE ON" VALUE <<
	;; DON'T BE CONFUSED: 
	;; DETUNE NEGATIVE => LOWER  FREQ = HIGHER TUNE REG VALUE
	;; DETUNE ADDITIVE => HIGHER FREQ = LOWER TUNE REG VALUE
	clrc	;; CLEAR CARRY BIT
	movf	AY_DETUNE_TEMP, W
	addwf 	AY_TONE_A_TUNE_FINE_MIDI, F
	    
	    ;;  *carry flag* is set when an instruction overflows a register.
	    ;;  branch if a carry flag is true - INC the 4 BIT COARSE TUNE REG
 	    bc MIDI_EVNT_NOTE_ON_FINE_DETUNE_NEGATIVE_REG_OVERFLOW_COARSE_REG_A_INC
			
				;; Go AND WRITE TUNE TO AY CHIP
		  		rgoto MIDI_EVNT_NOTE_ON_TONE_A_SEND_TUNE_TO_AY_CHIP

MIDI_EVNT_NOTE_ON_FINE_DETUNE_NEGATIVE_REG_OVERFLOW_COARSE_REG_A_INC
	;; THE CARRY FLAG HAS BEEN SET (OVERFLOW OF FINE TUNE REG)
	;; CHECK MIDI COASE REG = 0x0F ? 
	;; IS COARSE TUNE REG > BIN xxxx1110 ? => 14 (15 = higest Value) 
	movlw	COARSE_TUNE_MAX_MINUS_1_B00001110
	cpfsgt 	AY_TONE_A_TUNE_COARSE_MIDI	

			;; NO - COARSE REG TUNE RANGE IS [0 to 14]
			;; OK SO COASE REG IS VALID
			rgoto MIDI_EVNT_NOTE_ON_CARRY_COARSE_REG_A_INC

			;; YES - NO INC OF COARSE REG POSSIBLE
			;; WRITE MAXIMUM VALUE TO COARSE and FINE REG. 
			rgoto MIDI_EVNT_NOTE_ON_WRITE_MAXIMUM_VALUE_TO_FINE_AND_COARSE_REG_A


MIDI_EVNT_NOTE_ON_CARRY_COARSE_REG_A_INC	
	;; INC PITCH CARRY FROM FINE-TUNE REG 
	;; +1 to COASE TUNE REG 
	incf AY_TONE_A_TUNE_COARSE_MIDI, F
	
		  		;; Go AND WRITE TUNE TO AY CHIP
		  		rgoto MIDI_EVNT_NOTE_ON_TONE_A_SEND_TUNE_TO_AY_CHIP

MIDI_EVNT_NOTE_ON_WRITE_MAXIMUM_VALUE_TO_FINE_AND_COARSE_REG_A
	;; WRITE MAXIMUM VALUE TO COARSE and FINE REG
	movlw  COARSE_TUNE_MAX_VALUE_B00001111
	movwf  AY_TONE_A_TUNE_COARSE_MIDI
	movlw  FINE_TUNE_MAX_VALUE_B11010010
	movwf  AY_TONE_A_TUNE_FINE_MIDI
	
		 		;; Go AND WRITE TUNE TO AY CHIP
		  		rgoto MIDI_EVNT_NOTE_ON_TONE_A_SEND_TUNE_TO_AY_CHIP

; 			
		
;; -----------[PITCH BEND FINE TONE A == POSITIVE]--------------
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_PLUS
	;; DETUNE IS POSITIVE - HIGHER FREQUENCY
	;; (+) RANGE OF: AY_TONE_A_TUNE_FINE_USER = [129 to 255] DETUNE IS POSITIVE (HERE)
	;; (-) RANGE OF: AY_TONE_A_TUNE_FINE_USER = [0   to 127] DETUNE IS NEGATIVE 
	;; (NO DETUNE) : AY_TONE_A_TUNE_FINE_USER = [128]
	
	;; OFFSET JUSTAGE
	;; WRITE 128 TO WREG
	movlw	OFFSET_FINE_TUNE_IS_128
	;; {[AY_TONE_A_TUNE_FINE_USER | (129 to 255)] - [WREG|(128)]} WRITE TO => [WREG]
	subwf	AY_TONE_A_TUNE_FINE_USER, W		; - 0x80 = OFFSET
		;; RANGE JUSTAGE
		;; WRITE [WREG] TO => [AY_DETUNE_TEMP]
		;; RANGE == [+1 to +128]
		movwf	AY_DETUNE_TEMP
		;; 2x => (+2 to +256)
		addwf	AY_DETUNE_TEMP, F
		;; -1 => (+1 to +255)
		decf	AY_DETUNE_TEMP, F

;; ------[DETUNE RATIO CHANGE?]------------------
	;; CHECK IF WE NEED TO CHANGE THE PITCH BEND RATIO
	;; CHECK IF MIDI TUNE COARSE REG > 3 
	;; 4 to 15 => NO RATIO CHANGE
	movlw	0x03	 
	cpfsgt 	AY_TONE_A_TUNE_COARSE_MIDI	

			;; NO [MIDI TUNE COARSE REG = 0 to 3]
			;; THERE MUST BE A PITCH BEND RATIO CONVERSATION
			rgoto MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE
			
			;; YES [MIDI TUNE COARSE REG > 3]
			;; THERE MUST BE *NO* PITCH BEND RATIO CHANGE
			rgoto MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_GO_ON

MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE	
	;; 0) PITCH BEND /16 ==> IF MIDI TUNE COARSE REG == 0
	;; 1) PITCH BEND / 8 ==> IF MIDI TUNE COARSE REG == 1
	;; 2) PITCH BEND / 4 ==> IF MIDI TUNE COARSE REG == 2
	;; 3) PITCH BEND / 2 ==> IF MIDI TUNE COARSE REG == 3
	movf AY_TONE_A_TUNE_COARSE_MIDI, W
	JUMPTABLE_2BYTES 4
		rgoto        MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE_DIVIDE_16x 	;; 0  ==> PITCH BAND VALUE /16
		rgoto        MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE_DIVIDE_8x 	;; 1  ==> PITCH BAND VALUE /8
		rgoto        MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE_DIVIDE_4x 	;; 2  ==> PITCH BAND VALUE /4
		rgoto        MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE_DIVIDE_2x 	;; 3  ==> PITCH BAND VALUE /2
	
	
	
;; ADJUST PITCH BEND RATIO
;; JUMP IN HERE = PITCH BAND /16
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE_DIVIDE_16x 
		rrncf	AY_DETUNE_TEMP, F
		bcf	AY_DETUNE_TEMP, 7
;; JUMP IN HERE = PITCH BAND /8
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE_DIVIDE_8x
		rrncf	AY_DETUNE_TEMP, F
		bcf	AY_DETUNE_TEMP, 7
;; JUMP IN HERE = PITCH BAND /4
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE_DIVIDE_4x
		rrncf	AY_DETUNE_TEMP, F
		bcf	AY_DETUNE_TEMP, 7
;; JUMP IN HERE = PITCH BAND /2
MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_RATIO_CHANGE_DIVIDE_2x
		rrncf	AY_DETUNE_TEMP, F
		bcf	AY_DETUNE_TEMP, 7

;; ------[DETUNE RATIO CHANGE END]------------------

MIDI_EVNT_NOTE_ON_TONE_A_FINE_DETUNE_POSITIVE_GO_ON
;; ------WRITE DETUNE TO MIDI TUNE FINE REG
	
		;; CHECK: DO WE NEED TO SUBTRACT THE NEGATIVE CARRY BIT
		;; FROM THE MIDI TUNE COARSE REG?
		;; IS [DETUNE FINE] > W [TONE FINE MIDI] ?
		;; // [DETUNE FINE] MUST BE = or < THEN [TONE FINE MIDI]
		;; // otherwise WE HAVE DO DEC -1 @ [COARSE MIDI REG]
		movf 	AY_TONE_A_TUNE_FINE_MIDI, W 
		cpfsgt	AY_DETUNE_TEMP		 	
						
			;; NO
			;; W [MIDI FINE REG] WAS > F [DETUNE FINE]
			;; or W [MIDI FINE REG]  = F [DETUNE FINE]
			;; SO WE CAN GO ON 
			rgoto MIDI_EVNT_NOTE_ON_FINE_DETUNE_POSITIVE_WRITE_DETUNE_TO_MIDI_VALUE_TONE_A
		
			;; YES 
			;; F [PITCH BEND] WAS > W [MIDI FINE REG]
			;; SO WE HAVE DO DEC -1 [COARSE MIDI REG]
			rgoto MIDI_EVNT_NOTE_ON_FINE_DETUNE_POSITIVE_COARSE_REG_A_DEC	


MIDI_EVNT_NOTE_ON_FINE_DETUNE_POSITIVE_WRITE_DETUNE_TO_MIDI_VALUE_TONE_A	
	;; WRITE THE POSITIVE PITCH BEND TO THE "NOTE ON MIDI VALUE" [FINE TUNE + COARSE TUNE REG]
	;; SUBTRACT DETUNE (THE POSITIVE PITCH BEND) from "NOTE ON" MIDI VALUE 
	;; THE POSITIVE VALUE WILL BE SUBTRACTED (DON'T BE CONFUSED;)
	;; TUNE "+" = "-" @ TUNE REG (LOGIC => AY SOUND CHIP)
	movf	AY_DETUNE_TEMP, W
	subwf	AY_TONE_A_TUNE_FINE_MIDI, F
							;; OK, FINE DETUNE IS DONE
							;; Go AND WRITE TUNE TO AY CHIP
							rgoto MIDI_EVNT_NOTE_ON_TONE_A_SEND_TUNE_TO_AY_CHIP



MIDI_EVNT_NOTE_ON_FINE_DETUNE_POSITIVE_COARSE_REG_A_DEC
	;; FIRST: WRITE THE POSITIVE PITCH BEND TO THE "NOTE ON MIDI VALUE" [FINE TUNE + COARSE TUNE REG]
	;; SUBTRACT DETUNE (THE POSITIVE PITCH BEND) from "NOTE ON" MIDI VALUE 
	;; THE POSITIVE VALUE WILL BE SUBTRACTED (DON'T BE CONFUSED;)
	;; TUNE "+" = "-" @ TUNE REG (LOGIC => AY SOUND CHIP)
	movf	AY_DETUNE_TEMP, W
	subwf	AY_TONE_A_TUNE_FINE_MIDI, F
	
				;; WE HAVE TO DEC THE VALUE OF COARSE REG -1
				;; BUT CHECK MIDI COASE REG = 0x00 ? 
				;; BECAUSE => 0x00 = INVALID VALUE 
				movlw	0x00
				cpfseq 	AY_TONE_A_TUNE_COARSE_MIDI

					;; NO - OK COARSE REG IS > 0 - SO GO ON WITH DEC COASE TUNE REG | -1
					rgoto MIDI_EVNT_NOTE_ON_FINE_DETUNE_POSITIVE_CARRYBIT_DEC_COARSE_REG_A_GO_ON

					;; YES - COARSE REG = 0 
					;; WE CAN NOT DEC. COARSE REG (ALLREADY 0x00)
					;; SO WRITE THE highest PITCH BEND DATA as possible TO THE 
					;; FINE AND COARSE REG instead
					rgoto MIDI_EVNT_NOTE_ON_FINE_DETUNE_POSITIVE_WRITE_HIGHEST_VALUE_PITCH_A


MIDI_EVNT_NOTE_ON_FINE_DETUNE_POSITIVE_CARRYBIT_DEC_COARSE_REG_A_GO_ON	
	
						;; DEC DETUNE CARRY FROM FINETUNE REG (MINUS CARY) 
						;; -1 to COASE TUNE REG 
						decf AY_TONE_A_TUNE_COARSE_MIDI, F
	
						  	;; Go AND WRITE TUNE TO AY CHIP
							rgoto MIDI_EVNT_NOTE_ON_TONE_A_SEND_TUNE_TO_AY_CHIP


MIDI_EVNT_NOTE_ON_FINE_DETUNE_POSITIVE_WRITE_HIGHEST_VALUE_PITCH_A
	
						;; THE TUNE WOULD BE OUT OF RANGE 
						;; SO SET FINE TUNE REG TO 0x0A (highest value that is VALID)
						;; COARSE TUNE REG IS ALLREADY 0x00
						movlw 	FINE_TUNE_MIN_VALUE_B00001010
						movwf	AY_TONE_A_TUNE_FINE_MIDI
	
							;; Go AND WRITE TUNE TO AY CHIP
							rgoto MIDI_EVNT_NOTE_ON_TONE_A_SEND_TUNE_TO_AY_CHIP

;; -------------[END OF DETUNE TONE A FINE ]--------------		


;; -------------[SEND TUNE TONE A DATA TO AY CHIP]--------------
MIDI_EVNT_NOTE_ON_TONE_A_SEND_TUNE_TO_AY_CHIP
	;; SEND TUNE A TO AY CHIP
	movlw  AY_CHIP_ADR_01_TONE_A_FREQUENCY_PERIOD_COARSE
	movwf  AY_REG_ADDRESS 			; ADDRESS FOR => AY_SR_Write
	
	movf  AY_TONE_A_TUNE_COARSE_MIDI, W	; DATA FOR AY REG X
	movwf AY_REG_DATA 			; FOR => AY_SR_Write (WRITE DATA TO AY REG)
	
		call LABEL_AY_SR_Write		; WRITING 8BIT DATA 
						;(AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE	

	movlw  AY_CHIP_ADR_00_TONE_A_FREQUENCY_FINE
	movwf  AY_REG_ADDRESS 			; ADDRESS FOR => AY_SR_Write

	movf  AY_TONE_A_TUNE_FINE_MIDI, W	; DATA FOR AY REG X
	movwf AY_REG_DATA 			; FOR => AY_SR_Write (WRITE DATA TO AY REG)
	
		call LABEL_AY_SR_Write		; WRITING 8BIT DATA 
						;; (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE

;; -------------------------------[END OF DETUNE TONE A ]--------------------------------------------

;; ----------------------------[CHECK VELOCITY TO NOISE PERIOD @ TONE A]-------------------------

	;; CHECK IF BIT3 is SET
	btfss AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT3_VELOCITY_TO_NOISE_PERIOD_ON_OFF
		;; NO, BIT3 IS NOT SET
		;; THERE IS NO VELOCITY TO NOISE PERIOD 
		;; SO QUIT HERE AND GO ON WITCH CHECKING THE VELOCITY TO VOLUME @ TONE A
		rgoto  MIDI_EVNT_TONE_A_CHECK_VELOCITY
	
		;; YES - BIT3 IS SET - CHECK IF VELOCITY IS @ TONE A
		rgoto  MIDI_EVNT_TONE_A_CHECK_VELOCITY_TO_NOISE_PERIOD

MIDI_EVNT_TONE_A_CHECK_VELOCITY_TO_NOISE_PERIOD
	;; YES - BIT3 IS SET [VELOCITY TO NOISE PERIOD = ON]
	;; CHECK IF VELOCITY IS @ TONE A => BIT5
	btfss AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT5_VELOCITY_A_TO_NOISE_PERIOD_ON_OFF
		;; NO, BIT5 IS NOT SET
		;; THERE IS NO VELOCITY TO NOISE PERIOD @ TONE A 
		;; SO QUIT HERE AND GO ON WITCH CHECKING THE VELOCITY TO VOLUME @ TONE A
		rgoto MIDI_EVNT_TONE_A_CHECK_VELOCITY
	
		;; YES - BIT5 IS SET - WRITE VELOCITY TONE A TO NOISE PERIOD 
		rgoto MIDI_EVNT_TONE_A_WRITE_VELOCITY_TO_NOISE_PERIOD

MIDI_EVNT_TONE_A_WRITE_VELOCITY_TO_NOISE_PERIOD
	;; CONVERT MIDI DATA 7BIT (0-127) TO NOISE PERIOD 5BIT(0-31)
	;; {NOISE TONE 5BIT} = {MIDI DATA 7BIT}/4

	;; WRITE MIDI DATA BYTE2 0-127 
	;; TO AY_MIDI_VELOCITY_TO_VOLUME
	movff	MIDI_EVNT_VALUE, AY_MIDI_VELOCITY_TO_NOISE_PERIOD
	      
	          
	      ;; convert AY_MIDI_VELOCITY_TO_NOISE_PERIOD 8bit to 5bit (0-31 dec.)
	      ;; divide ==> (MIDI DATA)/4
	      rrncf 	AY_MIDI_VELOCITY_TO_NOISE_PERIOD, F	 ;; /2
	      bcf 	AY_MIDI_VELOCITY_TO_NOISE_PERIOD, 7
	      rrncf 	AY_MIDI_VELOCITY_TO_NOISE_PERIOD, F	 ;; /4
	      bcf 	AY_MIDI_VELOCITY_TO_NOISE_PERIOD, 7
	      

	      
	      movlw 0x1F ;; BIN 0001 1111
	      andwf AY_MIDI_VELOCITY_TO_NOISE_PERIOD, F

	      ;; NOW THE VELOCITY IS IN THE 5 LOWER BITS (0-31 dec.)
	      ;; AY_MIDI_VELOCITY_TO_NOISE_PERIOD => BIN '000V VVVV'
	      
	      movlw 0x20 ;; BIN 0010 0000 (32 dec.)
	      subfwb AY_MIDI_VELOCITY_TO_NOISE_PERIOD, F

		movlw 0x1F
		cpfsgt AY_MIDI_VELOCITY_TO_NOISE_PERIOD

		      ;; NO, OK
		      rgoto MIDI_EVNT_TONE_A_WRITE_VELOCITY_TO_NOISE_PERIOD_NOW
	
		      ;; YES - MAKE  AY_MIDI_VELOCITY_TO_NOISE_PERIOD VALID
		      rgoto MIDI_EVNT_TONE_A_MAKE_VALID_VELOCITY_TO_NOISE_PERIOD

MIDI_EVNT_TONE_A_MAKE_VALID_VELOCITY_TO_NOISE_PERIOD
	;; MAKE VELOCITY VALUE VALID [xxxV VVVV]
	movlw 0x1F 
	movwf AY_MIDI_VELOCITY_TO_NOISE_PERIOD
	      
MIDI_EVNT_TONE_A_WRITE_VELOCITY_TO_NOISE_PERIOD_NOW	      
	;; -------------[SEND VELOCITY TO NOISE PERIOD REG 6]------------------------
	movlw AY_CHIP_ADR_06_NOISE_PERIOD	; REG ADRESS 	=> AY REGISTER
	movwf AY_REG_ADDRESS 			; ADDRESS FOR 	=> AY_SR_Write
        
	;; WRITE AY_MIDI_VELOCITY_TO_VOLUME TO AY_REG_DATA
	movff AY_MIDI_VELOCITY_TO_NOISE_PERIOD, AY_REG_DATA

		;; --------------[SEND DATA TO AY REG X]-----------------------------------------------------
		call LABEL_AY_SR_Write	; WRITING 8BIT DATA (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE
		;; ==========================================================================================

			;; NEXT Check Velocity
			rgoto MIDI_EVNT_TONE_A_CHECK_VELOCITY 


;; ----------------------------[VELOCITY TONE A]-------------------------
;; ----------------------------------------------------------------------------
MIDI_EVNT_TONE_A_CHECK_VELOCITY

	;; WRITE VELOYTY TO VOLUME IF BIT 0 OF 
	;; AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF = SET
	btfsc AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT0_VELOCITY_ON_OFF_TONE_A ;; CHK BIT0
		
		;; NO - BIT0 = SET SO => DO WRITE VELOCITY TO VOLUME
		rgoto  MIDI_EVNT_TONE_A_SEND_VELOCITY_TO_VOLUME
		
		
		;; YES - BIT0 = CLEAR => DO NOT WRITE VELOCITY TO VOLUME
		rgoto MIDI_EVNT_TONE_A_SEND_VELOCITY_NOT_TO_VOLUME


MIDI_EVNT_TONE_A_SEND_VELOCITY_NOT_TO_VOLUME
		;; DO NOT WRITE VELOCITY TO TONE A VOLUME
		;; WRITE USER VOLUME TO TONE A

	;; -------------[SEND REG8 AMPLITUDE TO TONE A - USER VOLUME 0-15]------------------------
	movlw AY_CHIP_ADR_08_TONE_A_VOLUME_ENV_MODE_ON_OFF  ; REG ADRESS 	=> AY REGISTER
	movwf AY_REG_ADDRESS 		; ADDRESS FOR 	=> AY_SR_Write
        
	;; WRITE AY_R8_CH_A_AMPLITUDE TO AY_REG_DATA
	movff AY_R8_CH_A_AMPLITUDE, AY_REG_DATA

	;; --------------[SEND DATA TO AY REG 13]-----------------------------------------------------
	call LABEL_AY_SR_Write	; WRITING 8BIT DATA (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE
	;; ==========================================================================================
		
					;; NEXT TONE B
					goto MIDI_EVNT_NOTE_ON_CHECK_MIDI_CHANNEL_B

;; --------------------------------------------------------------------

MIDI_EVNT_TONE_A_SEND_VELOCITY_TO_VOLUME
	;; CONVERT MIDI DATA 7BIT (0-127) TO VOLUME TONE A 4BIT(0-15)
	;; {VOLUME TONE 4BIT} = {MIDI DATA 7BIT}/8

	;; WRITE MIDI DATA BYTE2 0-127 
	;; TO AY_MIDI_VELOCITY_TO_VOLUME
	movff	MIDI_EVNT_VALUE, AY_MIDI_VELOCITY_TO_VOLUME
	      
	          
	      ;; convert AY_MIDI_VELOCITY_TO_VOLUME
	      ;; divide ==> (MIDI DATA)/8
	      rrncf 	AY_MIDI_VELOCITY_TO_VOLUME, F	 ;; /2
	      bcf 	AY_MIDI_VELOCITY_TO_VOLUME, 7
	      rrncf 	AY_MIDI_VELOCITY_TO_VOLUME, F	 ;; /4
	      bcf 	AY_MIDI_VELOCITY_TO_VOLUME, 7
	      rrncf 	AY_MIDI_VELOCITY_TO_VOLUME, F	 ;; /8
	      bcf 	AY_MIDI_VELOCITY_TO_VOLUME, 7

	      
	      movlw 0x0F ;; BIN 00001111
	      andwf AY_MIDI_VELOCITY_TO_VOLUME, F

	      ;; NOW THE VELOCITY IS IN THE 4 LOWER BITS (0-15 dec.)
	      ;; AY_MIDI_VELOCITY_TO_VOLUME => BIN '0000 VVVV'
	      
	      ;; COPY THE LOWER 4 BIT [BIT0-to 3] = (VELOCITY VOLUME (0-15))
	      ;; TO AY AMPLITUDE REG TONE A = REG 8
	      ;; BUT SAVE THE BIT4 = AMPLITUDE MODE!
	      
	      ;; COPY THE ENV. MODE BIT	      
	      ;; WRITE 0 TO BIT0-3 
	      movlw 0xF0 ;; BIN 1111 0000
	      andwf AY_R8_CH_A_AMPLITUDE, W

	      iorwf AY_MIDI_VELOCITY_TO_VOLUME, W
	      movwf AY_MIDI_VELOCITY_TO_VOLUME

	;; -------------[SEND VELOCITY AMPLITUDE TO TONE A]------------------------
	movlw AY_CHIP_ADR_08_TONE_A_VOLUME_ENV_MODE_ON_OFF  ; REG ADRESS 	=> AY REGISTER
	movwf AY_REG_ADDRESS 				; ADDRESS FOR 	=> AY_SR_Write
        
	;; WRITE AY_MIDI_VELOCITY_TO_VOLUME TO AY_REG_DATA
	movff AY_MIDI_VELOCITY_TO_VOLUME, AY_REG_DATA

		;; --------------[SEND DATA TO AY REG X]-----------------------------------------------------
		call LABEL_AY_SR_Write	; WRITING 8BIT DATA (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE
		;; ==========================================================================================


;; -------------[END VELOCITY TONE A]-------------
;; -------------[END TONE A WORKFLOW]-------------


				;; NEXT TONE B
				;; => note_on_pipeline_b.inc
				goto MIDI_EVNT_NOTE_ON_CHECK_MIDI_CHANNEL_B


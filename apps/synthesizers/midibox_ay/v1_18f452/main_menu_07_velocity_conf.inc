;; main_menu_07_velocity_conf.inc

;; ---------------------------------------------------------------------------------------
;; -------------------------[MB AY MENU 7: MIDI VELOCITY A B C NOISE RATE CONFIG]---------- 
;; =======================> (F6 has been pressed)


LABEL_AY_MAIN_MENU_07_VELOCITY_CONFIG

LABEL_AY_MAIN_MENU_07_VELOCITY_TONE_A
	call    MIOS_LCD_Clear
   
	;; PRINT - VELOCITY To TONE A - LCD ROW1
	TABLE_ADDR TEXT_AY_VELOCITY_CONFIG_ROW1
	call    MIOS_LCD_PrintString

	;; SET CURSOR ROW1 VELOCITY TONE A
	movlw   LCD_ROW1 + 0x0e
	call    MIOS_LCD_CursorSet
	
	;; CHECK AY_VELOCITY_ON_OFF @TONE A
	btfss AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT0_VELOCITY_ON_OFF_TONE_A
		
		;; NO, BIT IS NOT SET
		;; NO VELOCITY TO VOLUME @ TONE A
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_OFF_TONE_A
	
		;; YES - BIT IS SET
		;; VELOCITY IS SET TO VOLUME @ TONE A
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_TONE_A

LABEL_AY_MAIN_MENU_07_VELOCITY_OFF_TONE_A
	movlw   '-'
	call    MIOS_LCD_PrintChar
	movlw   '-'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_TONE_B


LABEL_AY_MAIN_MENU_07_VELOCITY_ON_TONE_A
	movlw   'O'
	call    MIOS_LCD_PrintChar
	movlw   'N'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_TONE_B
      
LABEL_AY_MAIN_MENU_07_VELOCITY_TONE_B  
	;; PRINT - VELOCITY TO TONE B - LCD ROW2
	TABLE_ADDR TEXT_AY_VELOCITY_CONFIG_ROW2
	call    MIOS_LCD_PrintString

	;; SET CURSOR ROW2 VELOCITY TONE B
	movlw   LCD_ROW2 + 0x0e
	call    MIOS_LCD_CursorSet
	
	;; CHECK AY_VELOCITY_ON_OFF @TONE B
	btfss AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT1_VELOCITY_ON_OFF_TONE_B
		
		;; NO, BIT IS NOT SET
		;; NO VELOCITY TO VOLUME @ TONE B
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_OFF_TONE_B
	
		;; YES - BIT IS SET
		;; VELOCITY IS SET TO VOLUME @ TONE B
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_TONE_B

LABEL_AY_MAIN_MENU_07_VELOCITY_OFF_TONE_B
	movlw   '-'
	call    MIOS_LCD_PrintChar
	movlw   '-'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_TONE_C


LABEL_AY_MAIN_MENU_07_VELOCITY_ON_TONE_B
	movlw   'O'
	call    MIOS_LCD_PrintChar
	movlw   'N'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_TONE_C

LABEL_AY_MAIN_MENU_07_VELOCITY_TONE_C 
	;; PRINT - VELOCITY TO TONE C-- LCD ROW3
	TABLE_ADDR TEXT_AY_VELOCITY_CONFIG_ROW3
	call    MIOS_LCD_PrintString

	;; SET CURSOR ROW3 VELOCITY TONE C
	movlw   LCD_ROW3 + 0x0e
	call    MIOS_LCD_CursorSet
	
	;; CHECK AY_VELOCITY_ON_OFF @TONE C
	btfss AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT2_VELOCITY_ON_OFF_TONE_C
		
		;; NO, BIT IS NOT SET
		;; NO VELOCITY TO VOLUME @ TONE C
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_OFF_TONE_C
	
		;; YES - BIT IS SET
		;; VELOCITY IS SET TO VOLUME @ TONE C
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_TONE_C

LABEL_AY_MAIN_MENU_07_VELOCITY_OFF_TONE_C
	movlw   '-'
	call    MIOS_LCD_PrintChar
	movlw   '-'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_NOISE_RATE


LABEL_AY_MAIN_MENU_07_VELOCITY_ON_TONE_C
	movlw   'O'
	call    MIOS_LCD_PrintChar
	movlw   'N'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_NOISE_RATE

LABEL_AY_MAIN_MENU_07_VELOCITY_NOISE_RATE
	;; PRINT - VELOCITY TO NOISE RATE - LCD ROW4
	TABLE_ADDR TEXT_AY_VELOCITY_CONFIG_ROW4
	call    MIOS_LCD_PrintString

	
	
;;------------ CHECK AY_VELOCITY_ON_OFF @NOISE PERIOD]--------
	btfss AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT3_VELOCITY_TO_NOISE_PERIOD_ON_OFF
		
		;; NO, BIT IS NOT SET
		;; NO VELOCITY TO RATE @ NOISE
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_OFF_NOISE_RATE
	
		;; YES - BIT IS SET
		;; VELOCITY IS SET TO RATE @ NOISE
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE

LABEL_AY_MAIN_MENU_07_VELOCITY_OFF_NOISE_RATE
	;; SET CURSOR ROW4 VELOCITY TO NOISE RATE
	movlw   LCD_ROW4 + 0x0e
	call    MIOS_LCD_CursorSet
	movlw   '-'
	call    MIOS_LCD_PrintChar
	movlw   '-'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_1


LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE

	;; CHECK VELOCITY NOISE RATE = TONE A
	btfss AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT5_VELOCITY_A_TO_NOISE_PERIOD_ON_OFF
		
		;; NO, BIT5 IS NOT SET
		;; CHECK TONE B
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_CHK_TONE_B
	
		;; YES - BIT5 IS SET
		;; VELOCITY IS @ TONE A
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_IS_TONE_A


LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_IS_TONE_A
	;; PRINT @ VELOCITY NOISE PERIOD: A ON 
	movlw   LCD_ROW4 + 0x0c
	call    MIOS_LCD_CursorSet
	movlw   'A'
	call    MIOS_LCD_PrintChar
	
	movlw   LCD_ROW4 + 0x0e
	call    MIOS_LCD_CursorSet
	movlw   'O'
	call    MIOS_LCD_PrintChar
	movlw   'N'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_1


LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_CHK_TONE_B
	;; CHECK VELOCITY NOISE RATE = TONE B
	btfss AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT6_VELOCITY_B_TO_NOISE_PERIOD_ON_OFF
		
		;; NO, BIT6 IS NOT SET
		;; CHECK TONE C
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_CHK_TONE_C
	
		;; YES - BIT6 IS SET
		;; VELOCITY IS @ TONE b
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_IS_TONE_B

LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_IS_TONE_B
	;; PRINT @ VELOCITY NOISE PERIOD: A ON 
	movlw   LCD_ROW4 + 0x0c
	call    MIOS_LCD_CursorSet
	movlw   'B'
	call    MIOS_LCD_PrintChar
	
	movlw   LCD_ROW4 + 0x0e
	call    MIOS_LCD_CursorSet
	movlw   'O'
	call    MIOS_LCD_PrintChar
	movlw   'N'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_1


LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_CHK_TONE_C
	;; CHECK VELOCITY NOISE RATE = TONE C
	btfss AY_VELOCITY_TO_ABC_NOISE_PERIOD_ON_OFF, BIT7_VELOCITY_C_TO_NOISE_PERIOD_ON_OFF
		
		;; NO, BIT7 IS NOT SET
		;; ERROR
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_ERROR
	
		;; YES - BIT7 IS SET
		;; VELOCITY IS @ TONE C
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_IS_TONE_C

LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_ERROR
	;; ERROR - DONT WRITE TO LCD BUT GO ON
	rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_1


LABEL_AY_MAIN_MENU_07_VELOCITY_ON_NOISE_RATE_IS_TONE_C
	;; PRINT @ VELOCITY NOISE PERIOD: A ON 
	movlw   LCD_ROW4 + 0x0c
	call    MIOS_LCD_CursorSet
	movlw   'C'
	call    MIOS_LCD_PrintChar
	
	movlw   LCD_ROW4 + 0x0e
	call    MIOS_LCD_CursorSet
	movlw   'O'
	call    MIOS_LCD_PrintChar
	movlw   'N'
	call    MIOS_LCD_PrintChar
	      rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_1
	
	
;; -------------[CHECK EDITING MODE]----------

LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_1
	;; EDITING MODE @ VELOCITY TONE A?
	;; IS AY_LCD_COURSER_POS_MAIN_MENU_VELOCITY_CONFIG = 1?
	movff AY_LCD_COURSER_POS_MAIN_MENU_VELOCITY_CONFIG, MIOS_PARAMETER1
	movlw MENU_ITEM_POS1	; WRITE 1 TO WREG
	cpfseq MIOS_PARAMETER1 ;; COMPARE F WITH WREG
			
		;; NO
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_NOT_ITEM_TONE_A

		;; YES
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_IS_ITEM_TONE_A


LABEL_AY_MAIN_MENU_07_VELOCITY_IS_ITEM_TONE_A
	;; EDITING MODE @ VELOCITY TONE A
	;; PRINT "*" ON EDITING MODE POSITION
	movlw 	LCD_ROW1 + 10
	call    MIOS_LCD_CursorSet
	movlw   '*'
	      call    MIOS_LCD_PrintChar
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_2


LABEL_AY_MAIN_MENU_07_VELOCITY_NOT_ITEM_TONE_A
	;; NO EDITING MODE @ VELOCITY TONE A
	;; PRINT ":" ON EDIT POSITION1
	movlw   LCD_ROW1 + 10
	call    MIOS_LCD_CursorSet
	movlw   ':'
	      call    MIOS_LCD_PrintChar
        		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_2

;;------------------

LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_2
	;; EDITING MODE @ VELOCITY TONE B?
	;; IS AY_LCD_COURSER_POS_MAIN_MENU_VELOCITY_CONFIG = 2?
	movff AY_LCD_COURSER_POS_MAIN_MENU_VELOCITY_CONFIG, MIOS_PARAMETER1
	movlw MENU_ITEM_POS2	; WRITE 2 TO WREG
	cpfseq MIOS_PARAMETER1 ;; COMPARE F WITH WREG
			
		;; NO
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_NOT_ITEM_TONE_B

		;; YES
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_IS_ITEM_TONE_B


LABEL_AY_MAIN_MENU_07_VELOCITY_IS_ITEM_TONE_B
	;; EDITING MODE @ VELOCITY TONE B
	;; PRINT "*" ON EDITING MODE POSITION
	movlw 	LCD_ROW2 + 10
	call    MIOS_LCD_CursorSet
	movlw   '*'
	      call    MIOS_LCD_PrintChar
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_3


LABEL_AY_MAIN_MENU_07_VELOCITY_NOT_ITEM_TONE_B
	;; NO EDITING MODE @ VELOCITY TONE B
	;; PRINT ":" ON EDIT POSITION2
	movlw   LCD_ROW2 + 10
	call    MIOS_LCD_CursorSet
	movlw   ':'
	      call    MIOS_LCD_PrintChar
        		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_3

;; ------------

LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_3
	;; EDITING MODE @ VELOCITY TONE C?
	;; IS AY_LCD_COURSER_POS_MAIN_MENU_VELOCITY_CONFIG = 3?
	movff AY_LCD_COURSER_POS_MAIN_MENU_VELOCITY_CONFIG, MIOS_PARAMETER1
	movlw MENU_ITEM_POS3	; WRITE 3 TO WREG
	cpfseq MIOS_PARAMETER1 ;; COMPARE F WITH WREG
			
		;; NO
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_NOT_ITEM_TONE_C

		;; YES
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_IS_ITEM_TONE_C


LABEL_AY_MAIN_MENU_07_VELOCITY_IS_ITEM_TONE_C
	;; EDITING MODE @ VELOCITY TONE C
	;; PRINT "*" ON EDITING MODE POSITION
	movlw   LCD_ROW3 + 10
	call    MIOS_LCD_CursorSet
	movlw   '*'
	      call    MIOS_LCD_PrintChar
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_4


LABEL_AY_MAIN_MENU_07_VELOCITY_NOT_ITEM_TONE_C
	;; NO EDITING MODE @ VELOCITY TONE C
	;; PRINT ":" ON EDIT POSITION3
	movlw   LCD_ROW3 + 10
	call    MIOS_LCD_CursorSet
	movlw   ':'
	      call    MIOS_LCD_PrintChar
        		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_4

;; ------------

LABEL_AY_MAIN_MENU_07_VELOCITY_CHECK_EDITING_MODE_ITEM_4

	;; EDITING MODE @ NOISE RATE?
	;; IS AY_LCD_COURSER_POS_MAIN_MENU_VELOCITY_CONFIG = 4?
	movff AY_LCD_COURSER_POS_MAIN_MENU_VELOCITY_CONFIG, MIOS_PARAMETER1
	movlw MENU_ITEM_POS4; WRITE 4 TO WREG
	cpfseq MIOS_PARAMETER1 ;; COMPARE F WITH WREG
			
		;; NO
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_NOT_ITEM_NOISE_RATE

		;; YES
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_IS_ITEM_NOISE_RATE


LABEL_AY_MAIN_MENU_07_VELOCITY_IS_ITEM_NOISE_RATE
	;; EDITING MODE @ NOISE RATE
	;; PRINT "*" ON EDITING MODE POSITION
	movlw   LCD_ROW4 + 10
	call    MIOS_LCD_CursorSet
	movlw   '*'
	      call    MIOS_LCD_PrintChar
		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CONFIG_END


LABEL_AY_MAIN_MENU_07_VELOCITY_NOT_ITEM_NOISE_RATE
	;; NO EDITING MODE @ NOISE RATE
	;; PRINT ":" ON EDIT POSITION
	movlw   LCD_ROW4 + 10
	call    MIOS_LCD_CursorSet
	movlw   ':'
	      call    MIOS_LCD_PrintChar
        		rgoto LABEL_AY_MAIN_MENU_07_VELOCITY_CONFIG_END


;; ------------

LABEL_AY_MAIN_MENU_07_VELOCITY_CONFIG_END	
		return

;; ------------------------[END OF MAIN MENU 7 FUNCTIONS]----------------------------------

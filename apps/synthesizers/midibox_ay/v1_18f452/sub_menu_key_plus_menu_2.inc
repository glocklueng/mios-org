;; sub_menu_key_plus_menu_2.inc

;; --------[PLUS @ MAIN MENU2]------------------

PLUS_KEY_SUBROUTINE_AT_MAIN_MENU2
;; jumped in here from sub_menu_key_plus.inc
	;; MAIN MENU2 = TUNE MENU
	;; PLUS HAD BEEN PRESSED
	;;
	;; 1) CHECK WHICH ITEM (AY REG) IS 
	;; IN EDITING MODE "*"
	;; VIA AY_LCD_COURSER_POS_MAIN_MENU_ABC_TUNE
	;;
	;; 2) INC ITEM 

;; --[ 1) CHECK ITEM]-------

	;; CHECK LOCATION VIA EDITING MODE "*"
	;; COPY THE VALUE OF EDITING MODE TO  MIOS_PARAMETER1
	movff 	AY_LCD_COURSER_POS_MAIN_MENU_ABC_TUNE, MIOS_PARAMETER1

LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM1	
	movlw 	MENU_ITEM_POS1
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 1?

		;; NO
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM2

		;; YES
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM1
	

LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM2

	movlw 	MENU_ITEM_POS2
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 2?

		;; NO
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM3

		;; YES
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM2	


LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM3
	
	movlw 	MENU_ITEM_POS3
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 3?

		;; NO
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM4

		;; YES
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM3	




LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM4

	movlw 	MENU_ITEM_POS4
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  =4?

		;; NO
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM5

		;; YES
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM4	


LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM5

	movlw 	MENU_ITEM_POS5
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 5?

		;; NO
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM6

		;; YES
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM5	


LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_CHK_ITEM6

	movlw 	MENU_ITEM_POS6
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 6?

		;; NO - THERE IS NO ITEM LEFT OVER - SO QUIT
		goto LABEL_MAIN_MENUE_SWITCH

		;; YES
		rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM6	




;;---[ 2) INC ITEM [MAIN MENU2 - [1-6]]]--------

;;---[ 2) INC ITEM1 [MAIN MENU2]--------
LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM1
	;; INC ITEM1
	;; ITEM1 => USER CH. A COASE TUNE 4BIT (!)
	;; => RANGE 0-15 DEC.
	;; => RANGE 0-F  HEX
		;; CHEK ITEM VALUE 
		;; ITEM1 = 4BIT = 0x0F = 15 DEC
		;; compare f with WREG, skip if f > 14
		movlw 	0x0e
		cpfsgt 	AY_TONE_A_TUNE_COARSE_USER
		
			;; NO
			rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM1_OK

			;; YES
			goto LABEL_MAIN_MENUE_SWITCH




LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM1_OK
	;; ITEM = ITEM +1
	incf AY_TONE_A_TUNE_COARSE_USER, F
		;; SWITCH MAIN MENU TO: TUNE MENU
		goto LABEL_MAIN_MENUE_SWITCH


;;---[ 2) INC ITEM2 [MAIN MENU2]--------

LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM2
	;; INC ITEM2
	;; ITEM2 => USER CH. A FINE TUNE 8BIT 
	;; => RANGE 0-255 DEC.
	;; => RANGE 0-FF  HEX.
		;; CHEK ITEM VALUE 
		;; ITEM2 = 8BIT = 0xFF = 0-255 DEC
		;; compare f with WREG, skip >
		movlw 	0xFE
		;; IS AY REG > 0xFE ? 
		cpfsgt 	AY_TONE_A_TUNE_FINE_USER
		
			;; NO
			rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM2_OK

				;; YES (F = 0xFF = 255) SO SKIP SUB ROUTINE HERE
				goto LABEL_MAIN_MENUE_SWITCH


LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM2_OK
			;; ITEM = ITEM +1
			incf AY_TONE_A_TUNE_FINE_USER, F
	
				;; SWITCH MAIN MENU TO: TUNE MENU
				goto LABEL_MAIN_MENUE_SWITCH



;;---[ 2) INC ITEM3 [MAIN MENU2]--------

LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM3
	;; INC ITEM3
	;; ITEM3 => USER CH. B COASE TUNE 4BIT 
	;; => RANGE 0-15 DEC.
	;; => RANGE 0-0F  HEX.
		;; CHEK ITEM VALUE 
		;; ITEM3 = 4BIT = 0x0F = 0-15 DEC
		;; compare f with WREG, skip IF >
		;; AY REG > 0x0E?
		movlw 	0x0E
		cpfsgt 	AY_TONE_B_TUNE_COARSE_USER
		
			;; NO
			rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM3_OK

			;; YES
			goto LABEL_MAIN_MENUE_SWITCH


LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM3_OK
	;; ITEM = ITEM +1
	incf AY_TONE_B_TUNE_COARSE_USER, F
	
		;; SWITCH MAIN MENU TO: TUNE MENU
		goto LABEL_MAIN_MENUE_SWITCH


;;---[ 2) INC ITEM4 [MAIN MENU2]--------

LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM4
	;; INC ITEM4
	;; ITEM4 => USER CH. B FINE TUNE 8BIT 
	;; => RANGE 0-255 DEC.
	;; => RANGE 0-FF  HEX.

		;; CHEK ITEM VALUE 
		;; ITEM4 = 8BIT = 0xFF = 0-255 DEC
		;; compare f with WREG, skip IF >
		;; AY REG > 0xFE?
		movlw 	0xFE
		cpfsgt 	AY_TONE_B_TUNE_FINE_USER
		
			;; NO
			rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM4_OK

			;; YES
			goto LABEL_MAIN_MENUE_SWITCH


LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM4_OK
	;; ITEM = ITEM +1
	incf AY_TONE_B_TUNE_FINE_USER, F
		;; SWITCH BACK TO MAIN MENU
		goto LABEL_MAIN_MENUE_SWITCH



;;---[ 2) INC ITEM5 [MAIN MENU2]]--------

LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM5
	;; INC ITEM5
	;; ITEM3 => AY REG 5 = CH. C COASE TUNE 4BIT 
	;; => RANGE 0-15 DEC.
	;; => RANGE 0-0F  HEX.

		;; CHEK ITEM VALUE 
		;; ITEM5 = 4BIT = 0x0F = 0-15 DEC
		;; compare f with WREG, skip IF >
		;; AY REG > 0x0E?
		movlw 	0x0E
		cpfsgt 	AY_TONE_C_TUNE_COARSE_USER
		
			;; NO
			rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM5_OK

			;; YES - SKIP SUB ROUTINE
			goto LABEL_MAIN_MENUE_SWITCH


LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM5_OK
	;; ITEM = ITEM +1
	incf AY_TONE_C_TUNE_COARSE_USER, F
		;; SWITCH BACK TO MAIN MENU TUNE
		goto LABEL_MAIN_MENUE_SWITCH




;;---[ 2) INC ITEM6 [MAIN MENU2]--------

LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM6
	;; INC ITEM6
	;; ITEM6 => AY REG 4 = CH. C FINE TUNE 8BIT 
	;; => RANGE 0-255 DEC.
	;; => RANGE 0-FF  HEX.
		;; CHEK ITEM VALUE 
		;; ITEM4 = 8BIT = 0xFF = 0-255 DEC
		;; compare f with WREG, skip IF >
		;; AY REG > 0xFE?
		movlw 	0xFE
		cpfsgt 	AY_TONE_C_TUNE_FINE_USER
		
			;; NO
			rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM6_OK

			;; YES
			goto LABEL_MAIN_MENUE_SWITCH


LABEL_AY_SUB_MENU_PLUS_MAIN_MENU2_INC_ITEM6_OK

	
	;; ITEM = ITEM +1
	incf AY_TONE_C_TUNE_FINE_USER, F
	
		;; SWITCH BACK TO MAIN MENU: TUNE MENU
		goto LABEL_MAIN_MENUE_SWITCH

			
				

;;---[END INC ITEMS [MAIN MENU2]]--------


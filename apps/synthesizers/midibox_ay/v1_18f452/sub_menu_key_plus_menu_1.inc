;; sub_menu_key_plus_menu_1.inc


;; --------[PLUS @ MAIN MENU1 - PATCH MENU]------------------

PLUS_KEY_SUBROUTINE_AT_MAIN_MENU1
	;; Jumped in here from sub_menu_key_plus.inc
	
	;; 1) CHECK ITEM = EDITING MODE "*"
	;;
	;; 2) INC ITEM 

;; --[ 1) CHECK ITEM]-------

	;; CHECK LOCATION VIA EDITING MODE "*"
	;; COPY THE VALUE OF EDITING MODE TO  MIOS_PARAMETER1
	movff 	AY_LCD_COURSER_POS_MAIN_MENU_PATCH_INFO, MIOS_PARAMETER1

	;; check: pos ?
	movlw 	MENU_ITEM_POS2
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 2?

				;; NO
				;; Exit here
				return

		;; YES
		;; INC ITEM2
		;; ITEM2 => PATCH NUMBER [INT(0) - 1-128 (BANKSTICK])
		;; => RANGE 0    - 128   DEC.
		;; => RANGE 0x00 - 0x80  HEX.
		;; CHEK ITEM VALUE 
		;; compare f with WREG, 
		;; skip if CURRENT_PATCH_NR = PATCH_NUMBER_VALUE_MAX
		movlw 	PATCH_NUMBER_VALUE_MAX
		cpfseq 	BROWSE_PATCH_NR
		
			;; NO
			;; CURRENT_PATCH_NR < PATCH_NUMBER_VALUE_MAX
			rgoto LABEL_AY_SUB_MENU_PLUS_MAIN_MENU1_INC_ITEM2

				;; YES 
				;; CURRENT_PATCH_NR = PATCH_NUMBER_VALUE_MAX
				;; Exit Here
				return


LABEL_AY_SUB_MENU_PLUS_MAIN_MENU1_INC_ITEM2
			;; ITEM [PATCH NUMBER] = ITEM +1
			incf BROWSE_PATCH_NR, F
	
	;; PATCH MUST BE > 0 [+]KEY IS PRESSED 
	;; BROWSE PATCH = INTERNAL PATCH
	;; PATCH_MENU_STATE_FLAGS
	;; BIT2 = 0 = LOAD EEPROM PATCH (PIC INTERNAL PATCH)
	;; BIT2 = 1 = LOAD BANKSTICK PATCH
	bsf	PATCH_MENU_STATE_FLAGS, BIT2_SELECTED_PATCH_BANKSTICK_OR_INTERNAL

	;; Another PATCH NAME WILL BE LOADED BY THE MAIN MENU1
	;; THIS PATCH NAME IS NOT EDITED (yet) BY THE USER
	;; SO CLEAR BIT 5
	bcf 	PATCH_MENU_STATE_FLAGS, BIT5_PATCH_NAME_IS_NEW
	
	;; -----------------------[exit here]------------------------------
	;; Redraw LCD Main Menu
	goto LABEL_AY_MAIN_MENU_01_PATCH_INFO


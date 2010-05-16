;; lcd_text.inc
;; MIDIBOX AY - TEXT MESSAGES / MENU TEXT
;; ========================================

;; LCD - CLEAR ROW 1-4
LCD_CLEAR_ROW1				STRING 16, LCD_ROW1, "                "
LCD_CLEAR_ROW2				STRING 16, LCD_ROW2, "                "
LCD_CLEAR_ROW3				STRING 16, LCD_ROW3, "                "
LCD_CLEAR_ROW4				STRING 16, LCD_ROW4, "                "

;; LCD TEXT - Start Screen
TEXT_AY_START_SCREEN_ROW1		STRING 7,  LCD_ROW1, "MIDIBOX"
TEXT_AY_START_SCREEN_ROW2		STRING 9,  LCD_ROW2, "AY-3-8912"
TEXT_AY_START_SCREEN_ROW3		STRING 16, LCD_ROW3, "V1.00(RC1a) 2009"
TEXT_AY_START_SCREEN_ROW4		STRING 16, LCD_ROW4, "BY LEMONHORSE   "


;; LCD TEXT - LABEL_AY_MAIN_MENU_00_MENU_SWITCH
TEXT_AY_MB_AY_MENUE_SWITCH_ROW1		STRING 16, LCD_ROW1, "F1-PATCH F2-TUNE"
TEXT_AY_MB_AY_MENUE_SWITCH_ROW2 	STRING 16, LCD_ROW2, "F3-MIXER F4-VOL."
TEXT_AY_MB_AY_MENUE_SWITCH_ROW3 	STRING 16, LCD_ROW3, "F5-ENVEL F6-MIDI" 
TEXT_AY_MB_AY_MENUE_SWITCH_ROW4 	STRING 14, LCD_ROW4, "F7-VELOC F8-Fx" 


;; LCD TEXT - LABEL_AY_MAIN_MENU_01_PATCH_INFO
TEXT_AY_MB_AY_PATCH_NAME		STRING 16, LCD_ROW1, 	"NAME:   --------"
TEXT_AY_MB_AY_BANKSTICK_NOT_FORMATED	STRING 16, LCD_ROW1, 	"[-FORMATTING?!-]"
TEXT_AY_MB_AY_PATCH_NO_BS		STRING 16, LCD_ROW1, 	"[-NO BANSTICK1-]"
TEXT_AY_MB_AY_PATCH_NR 			STRING  3, LCD_ROW2, 	"NR:"
TEXT_AY_MB_AY_PATCH_INT_PATCH		STRING  8, LCD_ROW2+8,  "INTERNAL"
TEXT_AY_MB_AY_PATCH_BS_PATCH		STRING  7, LCD_ROW2+9, 	"B.STCK1"
TEXT_AY_MB_AY_PATCH_DO	 		STRING 16, LCD_ROW3, 	"DO:  [L] [W] [F]"
TEXT_AY_MB_AY_PATCH_EXE 		STRING 16, LCD_ROW4, 	"Load Wrte Format"
TEXT_AY_MB_AY_PATCH_EXE_NO_FORMAT	STRING 16, LCD_ROW4, 	"Load Wrte ------"
TEXT_AY_MB_AY_PATCH_EXE_NO_LT_ERT_FMT	STRING 16, LCD_ROW4, 	"---- ---- ------"
TEXT_AY_MB_AY_PATCH_EXE_JUST_FORMAT	STRING 16, LCD_ROW4, 	"---- ---- Format"
TEXT_AY_MB_AY_PATCH_WRITE_OK 		STRING 5,  LCD_ROW4+10, 	"W: OK"
TEXT_AY_MB_AY_PATCH_LOAD_OK 		STRING 5,  LCD_ROW4+10, 	"L: OK"
TEXT_AY_MB_AY_PATCH_ERROR 		STRING 5,  LCD_ROW4+10, 	"ERROR"
TEXT_AY_MB_AY_PATCH_FORMATTING_BS	STRING 2,  LCD_ROW4+10, 	"F:"

;; LCD TEXT - LABEL_AY_MAIN_MENU_02_ABC_TUNE
TEXT_AY_MENU_ABC_TUNE        		STRING 16, LCD_ROW1, "TUNE COARSE FINE"
TEXT_AY_MENU_ABC_TUNE_CHA_TUNE  	STRING 04, LCD_ROW2, "CH.A"
TEXT_AY_MENU_ABC_TUNE_CHB_TUNE		STRING 04, LCD_ROW3, "CH.B"
TEXT_AY_MENU_ABC_TUNE_CHC_TUNE		STRING 04, LCD_ROW4, "CH.C"

;; LCD TEXT - LABEL_AY_MAIN_MENU_03_ABC_MIXER
TEXT_AY_MENU_MIXER_FX_ON_OFF		STRING  6, LCD_ROW1, "Fx ABC"
TEXT_AY_MENU3_FX_A_OFF			STRING 01, LCD_ROW1 + 13, "-"
TEXT_AY_MENU3_FX_A_ON			STRING 01, LCD_ROW1 + 13, "A"
TEXT_AY_MENU3_FX_B_OFF			STRING 01, LCD_ROW1 + 14, "-"
TEXT_AY_MENU3_FX_B_ON			STRING 01, LCD_ROW1 + 14, "B"
TEXT_AY_MENU3_FX_C_OFF			STRING 01, LCD_ROW1 + 15, "-"
TEXT_AY_MENU3_FX_C_ON			STRING 01, LCD_ROW1 + 15, "C"

TEXT_AY_MENU_TONE_ABC_NOISE_MIX		STRING  8, LCD_ROW2, "TONE ABC"
TEXT_AY_MENU_TONE_ABC_MIX_A_NOT		STRING 01, LCD_ROW2 + 13, "-"
TEXT_AY_MENU_TONE_ABC_MIX_A_SET		STRING 01, LCD_ROW2 + 13, "A"
TEXT_AY_MENU_TONE_ABC_MIX_B_NOT		STRING 01, LCD_ROW2 + 14, "-"
TEXT_AY_MENU_TONE_ABC_MIX_B_SET		STRING 01, LCD_ROW2 + 14, "B"
TEXT_AY_MENU_TONE_ABC_MIX_C_NOT		STRING 01, LCD_ROW2 + 15, "-"
TEXT_AY_MENU_TONE_ABC_MIX_C_SET		STRING 01, LCD_ROW2 + 15, "C"

TEXT_AY_MENU_TONE_ABC_NOISE_MIX2	STRING  9, LCD_ROW3, "NOISE ABC"
TEXT_AY_MENU_TONE_ABC_MIX_NOISE_A_NOT	STRING 01, LCD_ROW3 + 13, "-"
TEXT_AY_MENU_TONE_ABC_MIX_NOISE_A_SET	STRING 01, LCD_ROW3 + 13, "A"
TEXT_AY_MENU_TONE_ABC_MIX_NOISE_B_NOT	STRING 01, LCD_ROW3 + 14, "-"
TEXT_AY_MENU_TONE_ABC_MIX_NOISE_B_SET	STRING 01, LCD_ROW3 + 14, "B"
TEXT_AY_MENU_TONE_ABC_MIX_NOISE_C_NOT	STRING 01, LCD_ROW3 + 15, "-"
TEXT_AY_MENU_TONE_ABC_MIX_NOISE_C_SET	STRING 01, LCD_ROW3 + 15, "C"

TEXT_AY_MENU_NOISE_PERIOD		STRING 11, LCD_ROW4, "NOISE FREQ."
TEXT_AY_MENU_NOISE_PERIOD_VELOCITY_A	STRING 3,  LCD_ROW4 + 13, "[A]"
TEXT_AY_MENU_NOISE_PERIOD_VELOCITY_B	STRING 3,  LCD_ROW4 + 13, "[B]"
TEXT_AY_MENU_NOISE_PERIOD_VELOCITY_C	STRING 3,  LCD_ROW4 + 13, "[C]"

;; LCD TEXT - LABEL_AY_MAIN_MENU_04_ABC_AMPLITUDE
TEXT_AY_MENU_AMPLITUDE_HEADLINE		STRING 16, LCD_ROW1, "VOLUME/AMPLITUDE"
TEXT_AY_MENU_AMPLITUDE_CH_A		STRING 7,  LCD_ROW2, "TONE A "
TEXT_AY_MENU_AMPLITUDE_CH_B		STRING 7,  LCD_ROW3, "TONE B "
TEXT_AY_MENU_AMPLITUDE_CH_C		STRING 7,  LCD_ROW4, "TONE C "

TEXT_AY_MENU_AMPLITUDE_CH_A_ENV		STRING 8, LCD_ROW2 + 8, "[ENV.ON]"
TEXT_AY_MENU_AMPLITUDE_CH_B_ENV		STRING 8, LCD_ROW3 + 8, "[ENV.ON]"
TEXT_AY_MENU_AMPLITUDE_CH_C_ENV		STRING 8, LCD_ROW4 + 8, "[ENV.ON]"

TEXT_AY_MENU_AMPLITUDE_CH_A_VELOC		STRING 8, LCD_ROW2 + 8, "[VELCTY]"
TEXT_AY_MENU_AMPLITUDE_CH_B_VELOC		STRING 8, LCD_ROW3 + 8, "[VELCTY]"
TEXT_AY_MENU_AMPLITUDE_CH_C_VELOC		STRING 8, LCD_ROW4 + 8, "[VELCTY]"


;; LCD TEXT - LABEL_AY_MAIN_MENU_05_ABC_ENVELOPE
TEXT_AY_MENU_ENVELOPE_COASE		STRING 10, LCD_ROW1,  "ENV.PERIOD"
TEXT_AY_MENU_ENVELOPE_FINE		STRING 10, LCD_ROW2,  "ENV.P.FINE"
TEXT_AY_MENU_ENVELOPE_SHAPE		STRING 5, LCD_ROW3,   "SHAPE"
TEXT_AY_MENU_ENVELOPE_MODE		STRING 10, LCD_ROW4,  "ENV.[ABC] "
TEXT_AY_MENU_ENVELOPE_MODE_SET_A	STRING 1, LCD_ROW4 + 11, "A"
TEXT_AY_MENU_ENVELOPE_MODE_SET_B	STRING 1, LCD_ROW4 + 13, "B"
TEXT_AY_MENU_ENVELOPE_MODE_SET_C	STRING 1, LCD_ROW4 + 15, "C"
TEXT_AY_MENU_ENVELOPE_MODE_NOT_SET_A	STRING 1, LCD_ROW4 + 11, "-"
TEXT_AY_MENU_ENVELOPE_MODE_NOT_SET_B	STRING 1, LCD_ROW4 + 13, "-"
TEXT_AY_MENU_ENVELOPE_MODE_NOT_SET_C	STRING 1, LCD_ROW4 + 15, "-"
TEXT_AY_MENU_ENVELOPE_SHAPE_0_3		STRING 4, LCD_ROW3 + 7,	 "down"
TEXT_AY_MENU_ENVELOPE_SHAPE_4_7		STRING 7, LCD_ROW3 + 7,	 "up down"
TEXT_AY_MENU_ENVELOPE_SHAPE_8		STRING 8, LCD_ROW3 + 7,	 "dwn cont"
TEXT_AY_MENU_ENVELOPE_SHAPE_10		STRING 9, LCD_ROW3 + 7,	 "dwn cont2"
TEXT_AY_MENU_ENVELOPE_SHAPE_11		STRING 6, LCD_ROW3 + 7,	 "dwn up"
TEXT_AY_MENU_ENVELOPE_SHAPE_12		STRING 7, LCD_ROW3 + 7,	 "up cont"
TEXT_AY_MENU_ENVELOPE_SHAPE_13		STRING 2, LCD_ROW3 + 7,	 "up"
TEXT_AY_MENU_ENVELOPE_SHAPE_14		STRING 8, LCD_ROW3 + 7,	 "up cont2"


;; LCD TEXT - LABEL_AY_MAIN_MENU_06_MIDI_CONFIG (MAIN MENU)
TEXT_AY_MIDI_CONFIG_ROW1		STRING 16, LCD_ROW1, "MIDI CH CONFIG. "
TEXT_AY_MIDI_CONFIG_ROW2		STRING 16, LCD_ROW2, "MIDI CH A       "
TEXT_AY_MIDI_CONFIG_ROW3		STRING 16, LCD_ROW3, "MIDI CH B       "
TEXT_AY_MIDI_CONFIG_ROW4		STRING 16, LCD_ROW4, "MIDI CH C       "


;; LCD TEXT - LABEL_AY_MAIN_MENU_07_VELOCITY_CONFIG (MAIN MENU)
TEXT_AY_VELOCITY_CONFIG_ROW1		STRING 10, LCD_ROW1, "VELOCITY A"
TEXT_AY_VELOCITY_CONFIG_ROW2		STRING 10, LCD_ROW2, "VELOCCIT B"
TEXT_AY_VELOCITY_CONFIG_ROW3		STRING 10, LCD_ROW3, "VELOCITY C"
TEXT_AY_VELOCITY_CONFIG_ROW4		STRING 10, LCD_ROW4, "NOISE RATE"

;; LCD TEXT - FX MENU 08
TEXT_MB_AY_MENUE_FX_ROW1		STRING 6, LCD_ROW1, "Fx POS"
TEXT_MB_AY_MENUE_FX_ROW2 		STRING 8, LCD_ROW2, "Fx DELAY"
TEXT_MB_AY_MENUE_FX_ROW3 		STRING 2, LCD_ROW3, "Fx"
TEXT_MB_AY_MENUE_FX_ROW4 		STRING 7, LCD_ROW4, "Fx DATA"

TEXT_MB_AY_MENUE_FX_FUNC0		STRING 7, LCD_ROW3 + PLUS_POS_Fx, "Fx STOP"
TEXT_MB_AY_MENUE_FX_FUNC1		STRING 5, LCD_ROW3 + PLUS_POS_Fx, "ON  A"
TEXT_MB_AY_MENUE_FX_FUNC2		STRING 5, LCD_ROW3 + PLUS_POS_Fx, "OFF A"
TEXT_MB_AY_MENUE_FX_FUNC3		STRING 5, LCD_ROW3 + PLUS_POS_Fx, "ON  B"
TEXT_MB_AY_MENUE_FX_FUNC4		STRING 5, LCD_ROW3 + PLUS_POS_Fx, "OFF B"
TEXT_MB_AY_MENUE_FX_FUNC5		STRING 5, LCD_ROW3 + PLUS_POS_Fx, "ON  C"
TEXT_MB_AY_MENUE_FX_FUNC6		STRING 5, LCD_ROW3 + PLUS_POS_Fx, "OFF C"
TEXT_MB_AY_MENUE_FX_FUNC7		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Tune A+DATA"
TEXT_MB_AY_MENUE_FX_FUNC8		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Tune A-DATA"
TEXT_MB_AY_MENUE_FX_FUNC9		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Tune B+DATA"
TEXT_MB_AY_MENUE_FX_FUNC10		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Tune B-DATA"
TEXT_MB_AY_MENUE_FX_FUNC11		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Tune C+DATA"
TEXT_MB_AY_MENUE_FX_FUNC12		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Tune C-DATA"
TEXT_MB_AY_MENUE_FX_FUNC13		STRING 11, LCD_ROW3 + PLUS_POS_Fx,"Vol. A DATA"
TEXT_MB_AY_MENUE_FX_FUNC14		STRING 11, LCD_ROW3 + PLUS_POS_Fx,"Vol. B DATA"
TEXT_MB_AY_MENUE_FX_FUNC15		STRING 11, LCD_ROW3 + PLUS_POS_Fx,"Vol. C DATA"
TEXT_MB_AY_MENUE_FX_FUNC16		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Noise ON  A"
TEXT_MB_AY_MENUE_FX_FUNC17		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Noise OFF A"
TEXT_MB_AY_MENUE_FX_FUNC18		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Noise ON  B"
TEXT_MB_AY_MENUE_FX_FUNC19		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Noise OFF B"
TEXT_MB_AY_MENUE_FX_FUNC20		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Noise ON  C"
TEXT_MB_AY_MENUE_FX_FUNC21		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Noise OFF C"
TEXT_MB_AY_MENUE_FX_FUNC22		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "N.Frq.:0-31"
TEXT_MB_AY_MENUE_FX_FUNC23		STRING 10, LCD_ROW3 + PLUS_POS_Fx,"Env. ON  A" 
TEXT_MB_AY_MENUE_FX_FUNC24		STRING 10, LCD_ROW3 + PLUS_POS_Fx,"Env. OFF A"
TEXT_MB_AY_MENUE_FX_FUNC25		STRING 10, LCD_ROW3 + PLUS_POS_Fx,"Env. ON  B" 
TEXT_MB_AY_MENUE_FX_FUNC26		STRING 10, LCD_ROW3 + PLUS_POS_Fx,"Env. OFF B"
TEXT_MB_AY_MENUE_FX_FUNC27		STRING 10, LCD_ROW3 + PLUS_POS_Fx,"Env. ON  C" 
TEXT_MB_AY_MENUE_FX_FUNC28		STRING 10, LCD_ROW3 + PLUS_POS_Fx,"Env. OFF C"
TEXT_MB_AY_MENUE_FX_FUNC29		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Env.Shp:1-8"
TEXT_MB_AY_MENUE_FX_FUNC30		STRING  9,LCD_ROW3 + PLUS_POS_Fx, "Env. Fine"
TEXT_MB_AY_MENUE_FX_FUNC31		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Env. Coarse"
TEXT_MB_AY_MENUE_FX_FUNC32		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Note#1 => A"
TEXT_MB_AY_MENUE_FX_FUNC33		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Note#1 => B"
TEXT_MB_AY_MENUE_FX_FUNC34		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Note#1 => C"
TEXT_MB_AY_MENUE_FX_FUNC35		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Note#2 => A"
TEXT_MB_AY_MENUE_FX_FUNC36		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Note#2 => B"
TEXT_MB_AY_MENUE_FX_FUNC37		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Note#2 => C"
TEXT_MB_AY_MENUE_FX_FUNC38		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Note#3 => A"
TEXT_MB_AY_MENUE_FX_FUNC39		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Note#3 => B"
TEXT_MB_AY_MENUE_FX_FUNC40		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "Note#3 => C"
TEXT_MB_AY_MENUE_FX_FUNC41		STRING 11,LCD_ROW3 + PLUS_POS_Fx, "GoPos=>DATA"	

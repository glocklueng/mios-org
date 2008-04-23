; $Id$
;
; Control Surface Menu Tables Structures
; (outsourced as they are really unreadable ;-)
;
; ==========================================================================
;
;  Copyright 1998-2007 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================


; ==========================================================================
;  CS_MENU_STRUCT contains the structure of a menu entry
; ==========================================================================
CS_MENU_HEADER_ENTRIES_OFFSET	EQU	0
CS_MENU_HEADER_ENTRIES_LEN	EQU	2
CS_MENU_HEADER_NAME_FUNC_OFFSET	EQU	CS_MENU_HEADER_ENTRIES_OFFSET+CS_MENU_HEADER_ENTRIES_LEN
CS_MENU_HEADER_NAME_FUNC_LEN	EQU	2
CS_MENU_HEADER_SEL_FUNC_OFFSET  EQU	CS_MENU_HEADER_NAME_FUNC_OFFSET+CS_MENU_HEADER_NAME_FUNC_LEN
CS_MENU_HEADER_SEL_FUNC_LEN	EQU	2
CS_MENU_HEADER_LED_FUNC_OFFSET	EQU	CS_MENU_HEADER_SEL_FUNC_OFFSET+CS_MENU_HEADER_SEL_FUNC_LEN
CS_MENU_HEADER_LED_FUNC_LEN	EQU	2
CS_MENU_HEADER_MSG_FUNC_OFFSET  EQU	CS_MENU_HEADER_LED_FUNC_OFFSET+CS_MENU_HEADER_LED_FUNC_LEN
CS_MENU_HEADER_MSG_FUNC_LEN	EQU	2

CS_MENU_HEADER_LEN		EQU	CS_MENU_HEADER_MSG_FUNC_OFFSET+CS_MENU_HEADER_MSG_FUNC_LEN

CS_MENU_HEADER MACRO entries, name_func, select_func, led_func, msg_func
	db	entries, 0x00
	dw	name_func
	dw	select_func
	dw	led_func
	dw	msg_func
	ENDM


CS_MENU_ENTRY_NAME_OFFSET	EQU	0
CS_MENU_ENTRY_NAME_LEN		EQU	14
CS_MENU_ENTRY_INIT_FUNC_OFFSET	EQU	CS_MENU_ENTRY_NAME_OFFSET+CS_MENU_ENTRY_NAME_LEN
CS_MENU_ENTRY_INIT_FUNC_LEN	EQU	2
CS_MENU_ENTRY_TICK_FUNC_OFFSET	EQU	CS_MENU_ENTRY_INIT_FUNC_OFFSET+CS_MENU_ENTRY_INIT_FUNC_LEN
CS_MENU_ENTRY_TICK_FUNC_LEN	EQU	2
CS_MENU_ENTRY_EXIT_FUNC_OFFSET	EQU	CS_MENU_ENTRY_TICK_FUNC_OFFSET+CS_MENU_ENTRY_TICK_FUNC_LEN
CS_MENU_ENTRY_EXIT_FUNC_LEN	EQU	2
CS_MENU_ENTRY_SEL_FUNC_OFFSET	EQU	CS_MENU_ENTRY_EXIT_FUNC_OFFSET+CS_MENU_ENTRY_EXIT_FUNC_LEN
CS_MENU_ENTRY_SEL_FUNC_LEN	EQU	2

CS_MENU_ENTRY_LEN		EQU	CS_MENU_ENTRY_SEL_FUNC_OFFSET+CS_MENU_ENTRY_SEL_FUNC_LEN

CS_MENU_ENTRY MACRO name, init_func, tick_func, exec_func, select_func
	db	name
	dw	init_func
	dw	tick_func
	dw	exec_func
	dw	select_func
	ENDM

	;; the first entry contains the pointers to the menu handler itself,
	;; the following entries the pointers to the routines which are executed within the menu pages

	;; we are using the following structure for every entry:
	;;   o 16 characters for the menu label
	;;   o function which initialies the menu page
	;;   o function which is called on every "tick"
	;;   o function which is called when left button pressed
	;;   o function which is called when select button pressed
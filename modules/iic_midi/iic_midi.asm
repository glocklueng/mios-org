;
;  MIDI Driver for MBHP_IIC_MIDI module
;
; ==========================================================================
;
;  Copyright 2006 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

	radix	dec
#include <mios.h>
#include <mios_vectors.inc>
#include <macros.h>

; ==========================================================================

	;; export lables
	global	IIC_MIDI_Init
	global	IIC_MIDI_Receive
	global	IIC_MIDI_Transmit
	global	IIC_MIDI_TransmitStart
	global	IIC_MIDI_Transmit
	global	IIC_MIDI_TransmitStop

	global	_IIC_MIDI_Init		; (for C, declaration in iic_midi.h)
	global	_IIC_MIDI_Receive
	global	_IIC_MIDI_Transmit
	global	_IIC_MIDI_TransmitStart
	global	_IIC_MIDI_TransmitByte
	global	_IIC_MIDI_TransmitStop

	global	_iic_midi_available_slaves
	global	_iic_midi_slave

	global	_iic_midi_rx_package
	global	_iic_midi_tx_package

	;; import lables
	extern	_sysex_owner
	extern	_ROUTER_Rx_IIC0
	extern	_ROUTER_Rx_IIC1
	extern	_ROUTER_Rx_IIC2
	extern	_ROUTER_Rx_IIC3

; ==========================================================================
; Compile time options (can be added via -D<name>=<value>
;   IIC_MIDI_BASE_ADDR: IIC base address
;   IIC_MIDI_MAX_NUMBER: max number of IIC slaves
;   IIC_MIDI_USE_RI: use Receive Interrupt lines for faster polling
;   *_RI_N_SLAVEx: allow to change the pinning
;   IIC_MIDI_DONT_USE_J5_INPUTS: if J5 of core module shouldn't be used for RI signals
; ==========================================================================

;; base address and max number of IIC slaves
#ifndef IIC_MIDI_BASE_ADDR
#define IIC_MIDI_BASE_ADDR	0x10
#endif

#ifndef IIC_MIDI_MAX_NUMBER
#define IIC_MIDI_MAX_NUMBER	4
#endif

;; use Receive Interrupt lines for faster polling?
#ifndef IIC_MIDI_USE_RI
#define IIC_MIDI_USE_RI		1
#endif

;; don't use J5 of the core module as digital inputs or RI signals
#ifndef IIC_MIDI_DONT_USE_J5_INPUTS
#define IIC_MIDI_DONT_USE_J5_INPUTS 0
#endif

;; RI_N lines (note: ADC will be turned off in IIC_MIDI_Init)
#ifndef PORT_RI_N_SLAVE0
PORT_RI_N_SLAVE0	EQU     PORTA
#endif
#ifndef TRIS_RI_N_SLAVE0
TRIS_RI_N_SLAVE0	EQU	TRISA
#endif
#ifndef PIN_RI_N_SLAVE0
PIN_RI_N_SLAVE0		EQU     0
#endif

#ifndef PORT_RI_N_SLAVE1
PORT_RI_N_SLAVE1	EQU     PORTA
#endif
#ifndef TRIS_RI_N_SLAVE1
TRIS_RI_N_SLAVE1	EQU	TRISA
#endif
#ifndef PIN_RI_N_SLAVE1
PIN_RI_N_SLAVE1		EQU     1
#endif

#ifndef PORT_RI_N_SLAVE2
PORT_RI_N_SLAVE2	EQU     PORTA
#endif
#ifndef TRIS_RI_N_SLAVE2
TRIS_RI_N_SLAVE2	EQU	TRISA
#endif
#ifndef PIN_RI_N_SLAVE2
PIN_RI_N_SLAVE2		EQU     2
#endif

#ifndef PORT_RI_N_SLAVE3
PORT_RI_N_SLAVE3	EQU     PORTA
#endif
#ifndef TRIS_RI_N_SLAVE3
TRIS_RI_N_SLAVE3	EQU	TRISA
#endif
#ifndef PIN_RI_N_SLAVE3
PIN_RI_N_SLAVE3		EQU     3
#endif

; ==========================================================================

accessram		udata_acs
_iic_midi_available_slaves res	1
_iic_midi_slave		res	1

IIC_MIDI_TMP		res	1
TX_RETRY_CTR		res	1
BYTES_TO_SEND		res	1

_iic_midi_rx_package	res	4
_iic_midi_tx_package	res	4

; ==========================================================================
IIC_MIDI code
; ==========================================================================

;; this table contains the number of bytes which have to be sent within a MIDI packet
BYTES_TO_SEND_TABLE
	;;	taken from Table 4-1 of USB MIDI spec v1.0:
	;;      +------------------------------- 0: invalid/reserved event
	;;      | +----------------------------- 1: invalid/reserved event
	;;      | | +--------------------------- 2: two-byte system common messages like MTC, Song Select, etc.
	;;      | | | +------------------------- 3: three-byte system common messages like SPP, etc.
	;;      | | | | +----------------------- 4: SysEx starts or continues
	;;      | | | | | +--------------------- 5: Sysex ends with following single byte
	;;      | | | | | | +------------------- 6: SysEx ends with following two bytes
	;;      | | | | | | | +----------------- 7: SysEx ends with following three bytes
	;;      | | | | | | | | +--------------- 8: Note Off
	;;      | | | | | | | | | +------------- 9: Note On
	;;      | | | | | | | | | | +----------- a: Poly-Key Press
	;;      | | | | | | | | | | | +--------- b: Control Change
	;;      | | | | | | | | | | | | +------- c: Program Change
	;;      | | | | | | | | | | | | | +----- d: Channel Pressure
	;;      | | | | | | | | | | | | | | +--- e: PitchBend Change
	;;      | | | | | | | | | | | | | | | +- f: single byte like MIDI Clock/Start/Stop/Continue
	;;      | | | | | | | | | | | | | | | |
	db	0,0,2,3,3,1,2,3,3,3,3,3,2,2,3,1

;; --------------------------------------------------------------------------
;;  FUNCTION: IIC_MIDI_Init
;;  DECLARATION: void IIC_MIDI_Init(void)
;;  DESCRIPTION: should be called after core reset to determine, which
;;  IIC MIDI slaves are connected to the core
;;  IN:	  -
;;  OUT:  detected slaves in _iic_midi_available_slaves
;;  USES: -
;; --------------------------------------------------------------------------
_IIC_MIDI_Init			; (for C, declaration in iic_midi.h)
IIC_MIDI_Init
	;; enable clock stretching
	movlw	0x01
	call	MIOS_IIC_CtrlSet

	;; stop IIC (set SDC/SCL high)
	call	MIOS_IIC_Stop

#if IIC_MIDI_USE_RI
#if IIC_MIDI_DONT_USE_J5_INPUTS
	;; disable the ADC which allocates the analog pins
	;; these pins are used to poll the RI_N lines
#if PIC_DERIVATIVE_NEW_ADC      ; defined in mios.h 
	movlw	0x0f		; PIC18F4550, 4685, etc...
#else
	movlw	0x07		; PIC18F452
#endif
	movwf	ADCON1
#endif

	;; enable inputs
	bsf	TRIS_RI_N_SLAVE0, PIN_RI_N_SLAVE0
	bsf	TRIS_RI_N_SLAVE1, PIN_RI_N_SLAVE1
	bsf	TRIS_RI_N_SLAVE2, PIN_RI_N_SLAVE2
	bsf	TRIS_RI_N_SLAVE3, PIN_RI_N_SLAVE3
#endif
	
	;; detect all available slaves	
	clrf	_iic_midi_available_slaves
	clrf	_iic_midi_slave

IIC_MIDI_Init_DetectLoop
	;; try to detect the slave three times
	call	IIC_MIDI_Receive_Internal
	btfsc	MIOS_BOX_STAT, MIOS_BOX_STAT_BS_AVAILABLE
	rgoto	IIC_MIDI_Init_DetectLoop_Avail

	call	IIC_MIDI_Receive_Internal
	btfsc	MIOS_BOX_STAT, MIOS_BOX_STAT_BS_AVAILABLE
	rgoto	IIC_MIDI_Init_DetectLoop_Avail

	call	IIC_MIDI_Receive_Internal
	btfsc	MIOS_BOX_STAT, MIOS_BOX_STAT_BS_AVAILABLE
	rgoto	IIC_MIDI_Init_DetectLoop_Avail

	rgoto	IIC_MIDI_Init_DetectLoop_Next

IIC_MIDI_Init_DetectLoop_Avail
	;; set appr. flag
	movf	_iic_midi_slave, W
	call	IIC_MIDI_GetSlaveMask
	iorwf	_iic_midi_available_slaves, F

IIC_MIDI_Init_DetectLoop_Next
	incf	_iic_midi_slave, F
	movlw	IIC_MIDI_MAX_NUMBER-1
	cpfsgt	_iic_midi_slave, ACCESS
	rgoto	IIC_MIDI_Init_DetectLoop

	return


;; --------------------------------------------------------------------------
;;  FUNCTION: IIC_MIDI_Receive
;;  DECLARATION: unsigned char IIC_MIDI_Receive(unsigned char slave)
;;  DESCRIPTION: receives a package from a MBHP_IIC_MIDI slave
;;  IN:	  MIDI slave number (0-3) in _iic_midi_slave
;;  OUT:  4 bytes in _iic_midi_rx_package,
;;        WREG contains _iic_midi_rx_package+0
;;        if WREG/_iic_midi_rx_package+0 == 0, no data has been received
;;  USES: -
;;  EXAMPLE:
;; --------------------------------------------------------------------------
_IIC_MIDI_Receive		; (for C, declaration in iic_midi.h)
	movwf	_iic_midi_slave

IIC_MIDI_Receive
	;; clear package content
	clrf	_iic_midi_rx_package+0
	clrf	_iic_midi_rx_package+1
	clrf	_iic_midi_rx_package+2
	clrf	_iic_midi_rx_package+3

	;; skip if slave not available
	call	IIC_MIDI_GetSlaveMask
	andwf	_iic_midi_available_slaves, W
	bz	IIC_MIDI_Receive_Disabled

	;; check RI line
	call	IIC_MIDI_GetRI
	bz	IIC_MIDI_Receive_NoRI

IIC_MIDI_Receive_Internal
	call	MIOS_IIC_Start		; start IIC
	rlf	_iic_midi_slave, W	; send address | 1 (read transfer)
	andlw	0x0e
	addlw	IIC_MIDI_BASE_ADDR | 1
	call	MIOS_IIC_ByteSend

	btfss	MIOS_BOX_STAT, MIOS_BOX_STAT_BS_AVAILABLE ; skip if IIC slave not available
	rgoto	IIC_MIDI_Receive_NotAvail

	call	MIOS_IIC_ByteReceive	; read byte #0
	movwf	_iic_midi_rx_package+0
	bz	IIC_MIDI_Receive_BufferEmpty	; -> got 0: package is empty
	call	MIOS_IIC_AckSend	; send acknowledge

	call	MIOS_IIC_ByteReceive	; read byte #1
	movwf	_iic_midi_rx_package+1
	call	MIOS_IIC_AckSend	; send acknowledge

	call	MIOS_IIC_ByteReceive	; read byte #2
	movwf	_iic_midi_rx_package+2
	call	MIOS_IIC_AckSend	; send acknowledge

	call	MIOS_IIC_ByteReceive	; read byte #3
	movwf	_iic_midi_rx_package+3

IIC_MIDI_Receive_BufferEmpty
 	call	MIOS_IIC_NakSend	; send Nak to abort transfer
IIC_MIDI_Receive_NotAvail
	call	MIOS_IIC_Stop		; stop IIC
IIC_MIDI_Receive_Disabled
IIC_MIDI_Receive_NoRI
	movf	_iic_midi_rx_package+0, W
	return

;; --------------------------------------------------------------------------
;;  FUNCTION: IIC_MIDI_Transmit
;;  DECLARATION: unsigned char IIC_MIDI_Transmit(unsigned char port, unsigned char ptype, unsigned char evnt0, unsigned char evnt1, unsigned char evnt2) __wparam
;;  DESCRIPTION: sends a package to a IIC slave
;;  IN:	  MIDI slave number (0-3) in _iic_midi_slave
;;        package in _iic_midi_tx_package
;;  OUT:  returns 0 if invalid package, returns 1 if transmission ok or slave not available!
;;  USES: -
;;  EXAMPLE:
;; --------------------------------------------------------------------------
_IIC_MIDI_Transmit			; (for C, declaration in iic_midi.h)
	movwf	_iic_midi_slave

	movff	FSR0L, FSR2L		; get package content from stack
	movff	PREINC2, _iic_midi_tx_package+0
	movff	PREINC2, _iic_midi_tx_package+1
	movff	PREINC2, _iic_midi_tx_package+2
	movff	PREINC2, _iic_midi_tx_package+3

IIC_MIDI_Transmit
	;; skip if slave not available
	call	IIC_MIDI_GetSlaveMask
	andwf	_iic_midi_available_slaves, W
	bz	IIC_MIDI_Transmit_SlaveNotAvail

	TABLE_ADDR BYTES_TO_SEND_TABLE ; get number of bytes -> TABLAT
	movf	_iic_midi_tx_package+0, W
	andlw	0x0f
	TABLE_ADD_W
	tblrd*

	movf	TABLAT, W		; skip checks below if no byte to send
	bz	IIC_MIDI_Transmit_End
	movwf	BYTES_TO_SEND

	clrf	TX_RETRY_CTR		; retry 256 times
	;; check if buffer free (returns 0 if not -> retry!), and start the transfer
IIC_MIDI_Transmit_Retry
	call	IIC_MIDI_TransmitStart
	bnz	IIC_MIDI_Transmit_StartOk
	decfsz	TX_RETRY_CTR, F
	rgoto	IIC_MIDI_Transmit_Retry
	andlw	0x00			; abort transfer after 256 retries, set ZERO flag
	rgoto	IIC_MIDI_Transmit_End
IIC_MIDI_Transmit_StartOk

	movlw	0			; send first byte
	cpfsgt	BYTES_TO_SEND, ACCESS
 	rgoto	IIC_MIDI_Transmit_LT1
	movf	_iic_midi_tx_package+1, W
	call	IIC_MIDI_TransmitByte
IIC_MIDI_Transmit_LT1

	movlw	1			; send second byte
	cpfsgt	BYTES_TO_SEND, ACCESS
 	rgoto	IIC_MIDI_Transmit_LT2
	movf	_iic_midi_tx_package+2, W
	call	IIC_MIDI_TransmitByte
IIC_MIDI_Transmit_LT2

	movlw	2			; send third byte
	cpfsgt	BYTES_TO_SEND, ACCESS
	rgoto	IIC_MIDI_Transmit_LT3
	movf	_iic_midi_tx_package+3, W
	call	IIC_MIDI_TransmitByte
IIC_MIDI_Transmit_LT3

	call	IIC_MIDI_TransmitStop

IIC_MIDI_Transmit_SlaveNotAvail
	iorlw	0xff		; ensure that ZERO flag not set!

IIC_MIDI_Transmit_End
	return

;; --------------------------------------------------------------------------
;;  FUNCTION: IIC_MIDI_TransmitStart
;;  DECLARATION: unsigned char IIC_MIDI_TransmitStart(unsigned char slave)
;;  DESCRIPTION: starts a transmission
;;  IN:	  MIDI slave number (0-3) in _iic_midi_slave
;;  OUT:  returns 0 if slave not available (or buffer full)
;;  USES: -
;;  EXAMPLE:
;; --------------------------------------------------------------------------
_IIC_MIDI_TransmitStart			; (for C, declaration in iic_midi.h)
	movwf	_iic_midi_slave

IIC_MIDI_TransmitStart
	;; skip if slave not available
	call	IIC_MIDI_GetSlaveMask
	andwf	_iic_midi_available_slaves, W
	bz	IIC_MIDI_TransmitStart_Disabled

	call	MIOS_IIC_Start		; start IIC
	rlf	_iic_midi_slave, W	; send address (write transfer)
	andlw	0x0e
	addlw	IIC_MIDI_BASE_ADDR
	call	MIOS_IIC_ByteSend

	btfss	MIOS_BOX_STAT, MIOS_BOX_STAT_BS_AVAILABLE ; return 0 if no acknowledge
	rgoto	IIC_MIDI_TransmitStart_NA

	iorlw	0xff			; return 0xff (ensure that ZERO flag not set!)
	return

IIC_MIDI_TransmitStart_NA		; received no acknowledge
	rcall	IIC_MIDI_TransmitStop	; stop IIC
IIC_MIDI_TransmitStart_Disabled
	andlw	0x00			; return 0 (ensure that ZERO flag set!)
	return

;; --------------------------------------------------------------------------
;;  FUNCTION: IIC_MIDI_TransmitByte
;;  DECLARATION: void IIC_MIDI_TransmitByte(unsigned char value)
;;  DESCRIPTION: transmits a byte 
;;  IN:	  byte in WREG, MIDI slave number (0-3) in _iic_midi_slave
;;  OUT:  -
;;  USES: -
;;  EXAMPLE:
;; --------------------------------------------------------------------------
_IIC_MIDI_TransmitByte			; (for C, declaration in iic_midi.h)
IIC_MIDI_TransmitByte
	movwf	IIC_MIDI_TMP		; temporary store value

	;; check if 0xff (control byte) should be sent - if so, we have to
	;; send it twice (one for entering command mode, one for exiting
	;; command mode + sending a 0xff at MIDI Out)
	xorlw	0xff
	bnz	IIC_MIDI_TransmitByte_NotFF	
IIC_MIDI_TransmitByte_FF
	call	IIC_MIDI_TransmitByte_FFOne	; first time
	;; second time...

IIC_MIDI_TransmitByte_FFOne
IIC_MIDI_TransmitByte_NotFF
	clrf	TX_RETRY_CTR			; clear timeout counter (256 tries - more than enough!)

IIC_MIDI_TransmitByteRetry
	decfsz	TX_RETRY_CTR, F
	rgoto	IIC_MIDI_TransmitByteTry
	rgoto	IIC_MIDI_TransmitByte_End	; give up!

IIC_MIDI_TransmitByteTry
	movf	IIC_MIDI_TMP, W
	call	MIOS_IIC_ByteSend
	btfsc	MIOS_BOX_STAT, MIOS_BOX_STAT_BS_AVAILABLE ; branch to end if acknowledge received
	rgoto	IIC_MIDI_TransmitByte_End

IIC_MIDI_TransmitByteRestart
	rcall	IIC_MIDI_TransmitStop	; restart until slaves acknowledges again
	rcall	IIC_MIDI_TransmitStart
	bnz	IIC_MIDI_TransmitByteRetry

	decfsz	TX_RETRY_CTR, F
	rgoto	IIC_MIDI_TransmitByteRestart
	;; give up!

IIC_MIDI_TransmitByte_End
	return


;; --------------------------------------------------------------------------
;;  FUNCTION: IIC_MIDI_TransmitStop
;;  DECLARATION: void IIC_MIDI_TransmitStop(void)
;;  DESCRIPTION: sends a stop condition to the slave
;;  IN:	  -
;;  OUT:  -
;;  USES: -
;;  EXAMPLE:
;; --------------------------------------------------------------------------
_IIC_MIDI_TransmitStop			; (for C, declaration in iic_midi.h)
IIC_MIDI_TransmitStop
	goto	MIOS_IIC_Stop

;; --------------------------------------------------------------------------
;; IN: slave number in _iic_midi_slave
;; OUT: bit mask which selects the slave
IIC_MIDI_GetSlaveMask
	btfsc	_iic_midi_slave, 2
	rgoto	IIC_MIDI_GetSlaveMask_4567
IIC_MIDI_GetSlaveMask_0123
	btfsc	_iic_midi_slave, 1
	rgoto	IIC_MIDI_GetSlaveMask_23
IIC_MIDI_GetSlaveMask_01
	btfss	_iic_midi_slave, 0
	retlw	1 << 0
	retlw	1 << 1

IIC_MIDI_GetSlaveMask_23
	btfss	_iic_midi_slave, 0
	retlw	1 << 2
	retlw	1 << 3

IIC_MIDI_GetSlaveMask_4567
	btfsc	_iic_midi_slave, 1
	rgoto	IIC_MIDI_GetSlaveMask_67
IIC_MIDI_GetSlaveMask_45
	btfss	_iic_midi_slave, 0
	retlw	1 << 4
	retlw	1 << 5

IIC_MIDI_GetSlaveMask_67
	btfss	_iic_midi_slave, 0
	retlw	1 << 6
	retlw	1 << 7

;; --------------------------------------------------------------------------
;; IN: slave number in _iic_midi_slave
;; OUT: receive status: 0x00 if RI_N of the appr. slave is not active (=1)
IIC_MIDI_GetRI
#if IIC_MIDI_USE_RI == 0
	iorlw	0xff		; (use andlw/iorlw to control the ZERO flag)
	return			; always active
#else
	andlw	0x00		; (use andlw/iorlw to control the ZERO flag)
	btfsc	_iic_midi_slave, 2
	rgoto	IIC_MIDI_GetRI_4567
IIC_MIDI_GetRI_0123
	btfsc	_iic_midi_slave, 1
	rgoto	IIC_MIDI_GetRI_23
IIC_MIDI_GetRI_01
	btfsc	_iic_midi_slave, 0
	rgoto	IIC_MIDI_GetRI_1
IIC_MIDI_GetRI_0
#if IIC_MIDI_MAX_NUMBER >= 1
	btfss	PORT_RI_N_SLAVE0, PIN_RI_N_SLAVE0	; the RI signal is low-active
	iorlw	0xff
#endif
	return
IIC_MIDI_GetRI_1
#if IIC_MIDI_MAX_NUMBER >= 2
	btfss	PORT_RI_N_SLAVE1, PIN_RI_N_SLAVE1	; the RI signal is low-active
	iorlw	0xff
#endif
	return

IIC_MIDI_GetRI_23
	btfsc	_iic_midi_slave, 0
	rgoto	IIC_MIDI_GetRI_3
IIC_MIDI_GetRI_2
#if IIC_MIDI_MAX_NUMBER >= 3
	btfss	PORT_RI_N_SLAVE2, PIN_RI_N_SLAVE2	; the RI signal is low-active
	iorlw	0xff
#endif
	return
IIC_MIDI_GetRI_3
#if IIC_MIDI_MAX_NUMBER >= 4
	btfss	PORT_RI_N_SLAVE3, PIN_RI_N_SLAVE3	; the RI signal is low-active
	iorlw	0xff
#endif
	return

IIC_MIDI_GetRI_4567
	btfsc	_iic_midi_slave, 1
	rgoto	IIC_MIDI_GetRI_67
IIC_MIDI_GetRI_45
	btfsc	_iic_midi_slave, 0
	rgoto	IIC_MIDI_GetRI_5
IIC_MIDI_GetRI_4
#if IIC_MIDI_MAX_NUMBER >= 5
	btfss	PORT_RI_N_SLAVE4, PIN_RI_N_SLAVE4	; the RI signal is low-active
	iorlw	0xff
#endif
	return
IIC_MIDI_GetRI_5
#if IIC_MIDI_MAX_NUMBER >= 6
	btfss	PORT_RI_N_SLAVE5, PIN_RI_N_SLAVE5	; the RI signal is low-active
	iorlw	0xff
#endif
	return

IIC_MIDI_GetRI_67
	btfsc	_iic_midi_slave, 0
	rgoto	IIC_MIDI_GetRI_7
IIC_MIDI_GetRI_6
#if IIC_MIDI_MAX_NUMBER >= 7
	btfss	PORT_RI_N_SLAVE6, PIN_RI_N_SLAVE6	; the RI signal is low-active
	iorlw	0xff
#endif
	return
IIC_MIDI_GetRI_7
#if IIC_MIDI_MAX_NUMBER >= 8
	btfss	PORT_RI_N_SLAVE7, PIN_RI_N_SLAVE7	; the RI signal is low-active
	iorlw	0xff
#endif
	return
#endif

; ==========================================================================
	END

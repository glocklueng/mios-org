/*
 * Header file for MIDI Rx/Tx LED Routines
 *
 * ==========================================================================
 *
 *  Copyright 2006 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 *
 * ==========================================================================
 */

#ifndef _MIDI_RXTX_LEDS_H
#define _MIDI_RXTX_LEDS_H

/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Global Types
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

extern void MIDI_RXTX_LEDS_NotifyRx(void) __wparam;
extern void MIDI_RXTX_LEDS_NotifyTx(void) __wparam;
extern void MIDI_RXTX_LEDS_Handler(void) __wparam;

/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////

#endif /* _MIDI_RXTX_LEDS_H */

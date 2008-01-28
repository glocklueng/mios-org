/*
 * Header file for internal MIDI Routines
 *
 * ==========================================================================
 *
 *  Copyright 2006 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 *
 * ==========================================================================
 */

#ifndef _INT_MIDI_H
#define _INT_MIDI_H

/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Global Types
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////
extern void INT_MIDI_Init(void) __wparam;
extern void INT_MIDI_Parse(unsigned char value) __wparam;
extern unsigned char INT_MIDI_Receive(unsigned char port) __wparam;
extern unsigned char INT_MIDI_Transmit(unsigned char port, unsigned char ptype, unsigned char evnt0, unsigned char evnt1, unsigned char evnt2) __wparam;

/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////

extern unsigned char int_midi_rx_package[4];
extern unsigned char int_midi_tx_package[4];

#endif /* _INT_MIDI_H */

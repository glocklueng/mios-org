/*
 * Header file for DIN velocity module
 *
 * ==========================================================================
 *
 *  Copyright (C) 2005 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _DIN_VEL_H
#define _DIN_VEL_H

/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////

#define NUMBER_OF_DIN_VEL   16   // 1..64 - note that each button allocates two DIN pins

/////////////////////////////////////////////////////////////////////////////
// Global Types
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Export functions
/////////////////////////////////////////////////////////////////////////////

void DIN_VEL_Init(void);
void DIN_VEL_Tick(void);
void DIN_VEL_NotifyToggle(unsigned char pin, unsigned char pin_value);

unsigned char DIN_VEL_LastButtonGet(void);
unsigned char DIN_VEL_LastVelocityGet(void);

/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////

// none

#endif /* _DIN_VEL_H */
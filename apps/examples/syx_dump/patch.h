// $Id$
/*
 * Patch Layer
 *
 * ==========================================================================
 *
 *  Copyright (C) 2008 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _PATCH_H
#define _PATCH_H

/////////////////////////////////////////////////////////////////////////////
// Exported variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// global definitions
/////////////////////////////////////////////////////////////////////////////

// 0: use EEPROM, 1: use BankStick as patch storage
#define PATCH_USE_BANKSTICK   0


/////////////////////////////////////////////////////////////////////////////
// Type definitions
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

void PATCH_Init(void);

unsigned char PATCH_ReadByte(unsigned char addr);
void PATCH_WriteByte(unsigned char addr, unsigned char byte);

unsigned char PATCH_Load(unsigned char bank, unsigned char patch);
unsigned char PATCH_Store(unsigned char bank, unsigned char patch);

#endif /* _PATCH_H */

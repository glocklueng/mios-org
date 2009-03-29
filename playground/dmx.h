/*
 * Header file for MBHP_DMX module driver
 *
 * ==========================================================================
 *
 *  Copyright (C) 2009 Phil Taylor (phil@taylor.org.uk)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _DMX_H
#define _DMX_H

/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////
s32 DMX_Init(u32 mode);
s32 DMX_SetChannel(u16 channel, u8 value);
s32 DMX_GetChannel(u16 channel);

#endif /* _DMX_H */

/*
 * EG program module definitions
 *
 * ==========================================================================
 *
 * Copyright (C) 2005  Thorsten Klose (tk@midibox.org)
 * 
 * ==========================================================================
 * 
 * This file is part of a MIOS application
 *
 * This application is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This application is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with This application; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * ==========================================================================
 */

#ifndef _EG_H
#define _EG_H

/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Global Types
/////////////////////////////////////////////////////////////////////////////

// EG state definition
typedef enum {
  IDLE, ATTACK, DECAY, SUSTAIN, RELEASE
} eg_state_e;

// EG internal state type
typedef union {
  struct {
    unsigned ALL:8;
  };
  struct {
    eg_state_e STATE:4;
    unsigned LAST_GATE:1;
  };
} eg_int_state_t;

// EG external state type
typedef union {
  struct {
    unsigned ALL:8;
  };
  struct {
    unsigned GATE:1;
  };
} eg_state_t;

/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

void EG_Init(void);
void EG_Tick(void);

/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////

// in order to achive best performance, we are NOT using arrays here!
extern eg_state_t    eg0;
extern unsigned int  eg0_value;
extern unsigned char eg0_attack, eg0_decay, eg0_sustain, eg0_release;

#endif /* _EG_H */

/*
 * pic18f4685.c - device specific definitions
 *
 * This file is part of the GNU PIC library for SDCC,
 * originally devised by Vangelis Rokas <vrokas AT otenet.gr>
 *
 * It has been automatically generated by inc2h-pic16.pl,
 * (c) 2007 by Raphael Neider <rneider AT web.de>
 *
 * #include "pic18f4680.c" removed and just pasted in here, and include for header file renamed
 *
 * Modified by stryd.one@gmail for MIOS SDCC wrapper compliance: FSR0 registers swapped with FSR1
 *
 */
 
#include "pic18f4685.h"


__sfr __at (0xD60) RXF6SIDH;
volatile __RXF6SIDHbits_t __at (0xD60) RXF6SIDHbits;

__sfr __at (0xD61) RXF6SIDL;
volatile __RXF6SIDLbits_t __at (0xD61) RXF6SIDLbits;

__sfr __at (0xD62) RXF6EIDH;
volatile __RXF6EIDHbits_t __at (0xD62) RXF6EIDHbits;

__sfr __at (0xD63) RXF6EIDL;
volatile __RXF6EIDLbits_t __at (0xD63) RXF6EIDLbits;

__sfr __at (0xD64) RXF7SIDH;
volatile __RXF7SIDHbits_t __at (0xD64) RXF7SIDHbits;

__sfr __at (0xD65) RXF7SIDL;
volatile __RXF7SIDLbits_t __at (0xD65) RXF7SIDLbits;

__sfr __at (0xD66) RXF7EIDH;
volatile __RXF7EIDHbits_t __at (0xD66) RXF7EIDHbits;

__sfr __at (0xD67) RXF7EIDL;
volatile __RXF7EIDLbits_t __at (0xD67) RXF7EIDLbits;

__sfr __at (0xD68) RXF8SIDH;
volatile __RXF8SIDHbits_t __at (0xD68) RXF8SIDHbits;

__sfr __at (0xD69) RXF8SIDL;
volatile __RXF8SIDLbits_t __at (0xD69) RXF8SIDLbits;

__sfr __at (0xD6A) RXF8EIDH;
volatile __RXF8EIDHbits_t __at (0xD6A) RXF8EIDHbits;

__sfr __at (0xD6B) RXF8EIDL;
volatile __RXF8EIDLbits_t __at (0xD6B) RXF8EIDLbits;

__sfr __at (0xD70) RXF9SIDH;
volatile __RXF9SIDHbits_t __at (0xD70) RXF9SIDHbits;

__sfr __at (0xD71) RXF9SIDL;
volatile __RXF9SIDLbits_t __at (0xD71) RXF9SIDLbits;

__sfr __at (0xD72) RXF9EIDH;
volatile __RXF9EIDHbits_t __at (0xD72) RXF9EIDHbits;

__sfr __at (0xD73) RXF9EIDL;
volatile __RXF9EIDLbits_t __at (0xD73) RXF9EIDLbits;

__sfr __at (0xD74) RXF10SIDH;
volatile __RXF10SIDHbits_t __at (0xD74) RXF10SIDHbits;

__sfr __at (0xD75) RXF10SIDL;
volatile __RXF10SIDLbits_t __at (0xD75) RXF10SIDLbits;

__sfr __at (0xD76) RXF10EIDH;
volatile __RXF10EIDHbits_t __at (0xD76) RXF10EIDHbits;

__sfr __at (0xD77) RXF10EIDL;
volatile __RXF10EIDLbits_t __at (0xD77) RXF10EIDLbits;

__sfr __at (0xD78) RXF11SIDH;
volatile __RXF11SIDHbits_t __at (0xD78) RXF11SIDHbits;

__sfr __at (0xD79) RXF11SIDL;
volatile __RXF11SIDLbits_t __at (0xD79) RXF11SIDLbits;

__sfr __at (0xD7A) RXF11EIDH;
volatile __RXF11EIDHbits_t __at (0xD7A) RXF11EIDHbits;

__sfr __at (0xD7B) RXF11EIDL;
volatile __RXF11EIDLbits_t __at (0xD7B) RXF11EIDLbits;

__sfr __at (0xD80) RXF12SIDH;
volatile __RXF12SIDHbits_t __at (0xD80) RXF12SIDHbits;

__sfr __at (0xD81) RXF12SIDL;
volatile __RXF12SIDLbits_t __at (0xD81) RXF12SIDLbits;

__sfr __at (0xD82) RXF12EIDH;
volatile __RXF12EIDHbits_t __at (0xD82) RXF12EIDHbits;

__sfr __at (0xD83) RXF12EIDL;
volatile __RXF12EIDLbits_t __at (0xD83) RXF12EIDLbits;

__sfr __at (0xD84) RXF13SIDH;
volatile __RXF13SIDHbits_t __at (0xD84) RXF13SIDHbits;

__sfr __at (0xD85) RXF13SIDL;
volatile __RXF13SIDLbits_t __at (0xD85) RXF13SIDLbits;

__sfr __at (0xD86) RXF13EIDH;
volatile __RXF13EIDHbits_t __at (0xD86) RXF13EIDHbits;

__sfr __at (0xD87) RXF13EIDL;
volatile __RXF13EIDLbits_t __at (0xD87) RXF13EIDLbits;

__sfr __at (0xD88) RXF14SIDH;
volatile __RXF14SIDHbits_t __at (0xD88) RXF14SIDHbits;

__sfr __at (0xD89) RXF14SIDL;
volatile __RXF14SIDLbits_t __at (0xD89) RXF14SIDLbits;

__sfr __at (0xD8A) RXF14EIDH;
volatile __RXF14EIDHbits_t __at (0xD8A) RXF14EIDHbits;

__sfr __at (0xD8B) RXF14EIDL;
volatile __RXF14EIDLbits_t __at (0xD8B) RXF14EIDLbits;

__sfr __at (0xD90) RXF15SIDH;
volatile __RXF15SIDHbits_t __at (0xD90) RXF15SIDHbits;

__sfr __at (0xD91) RXF15SIDL;
volatile __RXF15SIDLbits_t __at (0xD91) RXF15SIDLbits;

__sfr __at (0xD92) RXF15EIDH;
volatile __RXF15EIDHbits_t __at (0xD92) RXF15EIDHbits;

__sfr __at (0xD93) RXF15EIDL;
volatile __RXF15EIDLbits_t __at (0xD93) RXF15EIDLbits;

__sfr __at (0xDD4) RXFCON0;
volatile __RXFCON0bits_t __at (0xDD4) RXFCON0bits;

__sfr __at (0xDD5) RXFCON1;
volatile __RXFCON1bits_t __at (0xDD5) RXFCON1bits;

__sfr __at (0xDD8) SDFLC;
volatile __SDFLCbits_t __at (0xDD8) SDFLCbits;

__sfr __at (0xDE0) RXFBCON0;
volatile __RXFBCON0bits_t __at (0xDE0) RXFBCON0bits;

__sfr __at (0xDE1) RXFBCON1;
volatile __RXFBCON1bits_t __at (0xDE1) RXFBCON1bits;

__sfr __at (0xDE2) RXFBCON2;
volatile __RXFBCON2bits_t __at (0xDE2) RXFBCON2bits;

__sfr __at (0xDE3) RXFBCON3;
volatile __RXFBCON3bits_t __at (0xDE3) RXFBCON3bits;

__sfr __at (0xDE4) RXFBCON4;
volatile __RXFBCON4bits_t __at (0xDE4) RXFBCON4bits;

__sfr __at (0xDE5) RXFBCON5;
volatile __RXFBCON5bits_t __at (0xDE5) RXFBCON5bits;

__sfr __at (0xDE6) RXFBCON6;
volatile __RXFBCON6bits_t __at (0xDE6) RXFBCON6bits;

__sfr __at (0xDE7) RXFBCON7;
volatile __RXFBCON7bits_t __at (0xDE7) RXFBCON7bits;

__sfr __at (0xDF0) MSEL0;
volatile __MSEL0bits_t __at (0xDF0) MSEL0bits;

__sfr __at (0xDF1) MSEL1;
volatile __MSEL1bits_t __at (0xDF1) MSEL1bits;

__sfr __at (0xDF2) MSEL2;
volatile __MSEL2bits_t __at (0xDF2) MSEL2bits;

__sfr __at (0xDF3) MSEL3;
volatile __MSEL3bits_t __at (0xDF3) MSEL3bits;

__sfr __at (0xDF8) BSEL0;
volatile __BSEL0bits_t __at (0xDF8) BSEL0bits;

__sfr __at (0xDFA) BIE0;
volatile __BIE0bits_t __at (0xDFA) BIE0bits;

__sfr __at (0xDFC) TXBIE;
volatile __TXBIEbits_t __at (0xDFC) TXBIEbits;

__sfr __at (0xE20) B0CON;
volatile __B0CONbits_t __at (0xE20) B0CONbits;

__sfr __at (0xE21) B0SIDH;
volatile __B0SIDHbits_t __at (0xE21) B0SIDHbits;

__sfr __at (0xE22) B0SIDL;
volatile __B0SIDLbits_t __at (0xE22) B0SIDLbits;

__sfr __at (0xE23) B0EIDH;
volatile __B0EIDHbits_t __at (0xE23) B0EIDHbits;

__sfr __at (0xE24) B0EIDL;
volatile __B0EIDLbits_t __at (0xE24) B0EIDLbits;

__sfr __at (0xE25) B0DLC;
volatile __B0DLCbits_t __at (0xE25) B0DLCbits;

__sfr __at (0xE26) B0D0;
volatile __B0D0bits_t __at (0xE26) B0D0bits;

__sfr __at (0xE27) B0D1;
volatile __B0D1bits_t __at (0xE27) B0D1bits;

__sfr __at (0xE28) B0D2;
volatile __B0D2bits_t __at (0xE28) B0D2bits;

__sfr __at (0xE29) B0D3;
volatile __B0D3bits_t __at (0xE29) B0D3bits;

__sfr __at (0xE2A) B0D4;
volatile __B0D4bits_t __at (0xE2A) B0D4bits;

__sfr __at (0xE2B) B0D5;
volatile __B0D5bits_t __at (0xE2B) B0D5bits;

__sfr __at (0xE2C) B0D6;
volatile __B0D6bits_t __at (0xE2C) B0D6bits;

__sfr __at (0xE2D) B0D7;
volatile __B0D7bits_t __at (0xE2D) B0D7bits;

__sfr __at (0xE2E) CANSTAT_RO9;
volatile __CANSTAT_RO9bits_t __at (0xE2E) CANSTAT_RO9bits;

__sfr __at (0xE2F) CANCON_RO9;
volatile __CANCON_RO9bits_t __at (0xE2F) CANCON_RO9bits;

__sfr __at (0xE30) B1CON;
volatile __B1CONbits_t __at (0xE30) B1CONbits;

__sfr __at (0xE31) B1SIDH;
volatile __B1SIDHbits_t __at (0xE31) B1SIDHbits;

__sfr __at (0xE32) B1SIDL;
volatile __B1SIDLbits_t __at (0xE32) B1SIDLbits;

__sfr __at (0xE33) B1EIDH;
volatile __B1EIDHbits_t __at (0xE33) B1EIDHbits;

__sfr __at (0xE34) B1EIDL;
volatile __B1EIDLbits_t __at (0xE34) B1EIDLbits;

__sfr __at (0xE35) B1DLC;
volatile __B1DLCbits_t __at (0xE35) B1DLCbits;

__sfr __at (0xE36) B1D0;
volatile __B1D0bits_t __at (0xE36) B1D0bits;

__sfr __at (0xE37) B1D1;
volatile __B1D1bits_t __at (0xE37) B1D1bits;

__sfr __at (0xE38) B1D2;
volatile __B1D2bits_t __at (0xE38) B1D2bits;

__sfr __at (0xE39) B1D3;
volatile __B1D3bits_t __at (0xE39) B1D3bits;

__sfr __at (0xE3A) B1D4;
volatile __B1D4bits_t __at (0xE3A) B1D4bits;

__sfr __at (0xE3B) B1D5;
volatile __B1D5bits_t __at (0xE3B) B1D5bits;

__sfr __at (0xE3C) B1D6;
volatile __B1D6bits_t __at (0xE3C) B1D6bits;

__sfr __at (0xE3D) B1D7;
volatile __B1D7bits_t __at (0xE3D) B1D7bits;

__sfr __at (0xE3E) CANSTAT_RO8;
volatile __CANSTAT_RO8bits_t __at (0xE3E) CANSTAT_RO8bits;

__sfr __at (0xE3F) CANCON_RO8;
volatile __CANCON_RO8bits_t __at (0xE3F) CANCON_RO8bits;

__sfr __at (0xE40) B2CON;
volatile __B2CONbits_t __at (0xE40) B2CONbits;

__sfr __at (0xE41) B2SIDH;
volatile __B2SIDHbits_t __at (0xE41) B2SIDHbits;

__sfr __at (0xE42) B2SIDL;
volatile __B2SIDLbits_t __at (0xE42) B2SIDLbits;

__sfr __at (0xE43) B2EIDH;
volatile __B2EIDHbits_t __at (0xE43) B2EIDHbits;

__sfr __at (0xE44) B2EIDL;
volatile __B2EIDLbits_t __at (0xE44) B2EIDLbits;

__sfr __at (0xE45) B2DLC;
volatile __B2DLCbits_t __at (0xE45) B2DLCbits;

__sfr __at (0xE46) B2D0;
volatile __B2D0bits_t __at (0xE46) B2D0bits;

__sfr __at (0xE47) B2D1;
volatile __B2D1bits_t __at (0xE47) B2D1bits;

__sfr __at (0xE48) B2D2;
volatile __B2D2bits_t __at (0xE48) B2D2bits;

__sfr __at (0xE49) B2D3;
volatile __B2D3bits_t __at (0xE49) B2D3bits;

__sfr __at (0xE4A) B2D4;
volatile __B2D4bits_t __at (0xE4A) B2D4bits;

__sfr __at (0xE4B) B2D5;
volatile __B2D5bits_t __at (0xE4B) B2D5bits;

__sfr __at (0xE4C) B2D6;
volatile __B2D6bits_t __at (0xE4C) B2D6bits;

__sfr __at (0xE4D) B2D7;
volatile __B2D7bits_t __at (0xE4D) B2D7bits;

__sfr __at (0xE4E) CANSTAT_RO7;
volatile __CANSTAT_RO7bits_t __at (0xE4E) CANSTAT_RO7bits;

__sfr __at (0xE4F) CANCON_RO7;
volatile __CANCON_RO7bits_t __at (0xE4F) CANCON_RO7bits;

__sfr __at (0xE50) B3CON;
volatile __B3CONbits_t __at (0xE50) B3CONbits;

__sfr __at (0xE51) B3SIDH;
volatile __B3SIDHbits_t __at (0xE51) B3SIDHbits;

__sfr __at (0xE52) B3SIDL;
volatile __B3SIDLbits_t __at (0xE52) B3SIDLbits;

__sfr __at (0xE53) B3EIDH;
volatile __B3EIDHbits_t __at (0xE53) B3EIDHbits;

__sfr __at (0xE54) B3EIDL;
volatile __B3EIDLbits_t __at (0xE54) B3EIDLbits;

__sfr __at (0xE55) B3DLC;
volatile __B3DLCbits_t __at (0xE55) B3DLCbits;

__sfr __at (0xE56) B3D0;
volatile __B3D0bits_t __at (0xE56) B3D0bits;

__sfr __at (0xE57) B3D1;
volatile __B3D1bits_t __at (0xE57) B3D1bits;

__sfr __at (0xE58) B3D2;
volatile __B3D2bits_t __at (0xE58) B3D2bits;

__sfr __at (0xE59) B3D3;
volatile __B3D3bits_t __at (0xE59) B3D3bits;

__sfr __at (0xE5A) B3D4;
volatile __B3D4bits_t __at (0xE5A) B3D4bits;

__sfr __at (0xE5B) B3D5;
volatile __B3D5bits_t __at (0xE5B) B3D5bits;

__sfr __at (0xE5C) B3D6;
volatile __B3D6bits_t __at (0xE5C) B3D6bits;

__sfr __at (0xE5D) B3D7;
volatile __B3D7bits_t __at (0xE5D) B3D7bits;

__sfr __at (0xE5E) CANSTAT_RO6;
volatile __CANSTAT_RO6bits_t __at (0xE5E) CANSTAT_RO6bits;

__sfr __at (0xE5F) CANCON_RO6;
volatile __CANCON_RO6bits_t __at (0xE5F) CANCON_RO6bits;

__sfr __at (0xE60) B4CON;
volatile __B4CONbits_t __at (0xE60) B4CONbits;

__sfr __at (0xE61) B4SIDH;
volatile __B4SIDHbits_t __at (0xE61) B4SIDHbits;

__sfr __at (0xE62) B4SIDL;
volatile __B4SIDLbits_t __at (0xE62) B4SIDLbits;

__sfr __at (0xE63) B4EIDH;
volatile __B4EIDHbits_t __at (0xE63) B4EIDHbits;

__sfr __at (0xE64) B4EIDL;
volatile __B4EIDLbits_t __at (0xE64) B4EIDLbits;

__sfr __at (0xE65) B4DLC;
volatile __B4DLCbits_t __at (0xE65) B4DLCbits;

__sfr __at (0xE66) B4D0;
volatile __B4D0bits_t __at (0xE66) B4D0bits;

__sfr __at (0xE67) B4D1;
volatile __B4D1bits_t __at (0xE67) B4D1bits;

__sfr __at (0xE68) B4D2;
volatile __B4D2bits_t __at (0xE68) B4D2bits;

__sfr __at (0xE69) B4D3;
volatile __B4D3bits_t __at (0xE69) B4D3bits;

__sfr __at (0xE6A) B4D4;
volatile __B4D4bits_t __at (0xE6A) B4D4bits;

__sfr __at (0xE6B) B4D5;
volatile __B4D5bits_t __at (0xE6B) B4D5bits;

__sfr __at (0xE6C) B4D6;
volatile __B4D6bits_t __at (0xE6C) B4D6bits;

__sfr __at (0xE6D) B4D7;
volatile __B4D7bits_t __at (0xE6D) B4D7bits;

__sfr __at (0xE6E) CANSTAT_RO5;
volatile __CANSTAT_RO5bits_t __at (0xE6E) CANSTAT_RO5bits;

__sfr __at (0xE6F) CANCON_RO5;
volatile __CANCON_RO5bits_t __at (0xE6F) CANCON_RO5bits;

__sfr __at (0xE70) B5CON;
volatile __B5CONbits_t __at (0xE70) B5CONbits;

__sfr __at (0xE71) B5SIDH;
volatile __B5SIDHbits_t __at (0xE71) B5SIDHbits;

__sfr __at (0xE72) B5SIDL;
volatile __B5SIDLbits_t __at (0xE72) B5SIDLbits;

__sfr __at (0xE73) B5EIDH;
volatile __B5EIDHbits_t __at (0xE73) B5EIDHbits;

__sfr __at (0xE74) B5EIDL;
volatile __B5EIDLbits_t __at (0xE74) B5EIDLbits;

__sfr __at (0xE75) B5DLC;
volatile __B5DLCbits_t __at (0xE75) B5DLCbits;

__sfr __at (0xE76) B5D0;
volatile __B5D0bits_t __at (0xE76) B5D0bits;

__sfr __at (0xE77) B5D1;
volatile __B5D1bits_t __at (0xE77) B5D1bits;

__sfr __at (0xE78) B5D2;
volatile __B5D2bits_t __at (0xE78) B5D2bits;

__sfr __at (0xE79) B5D3;
volatile __B5D3bits_t __at (0xE79) B5D3bits;

__sfr __at (0xE7A) B5D4;
volatile __B5D4bits_t __at (0xE7A) B5D4bits;

__sfr __at (0xE7B) B5D5;
volatile __B5D5bits_t __at (0xE7B) B5D5bits;

__sfr __at (0xE7C) B5D6;
volatile __B5D6bits_t __at (0xE7C) B5D6bits;

__sfr __at (0xE7D) B5D7;
volatile __B5D7bits_t __at (0xE7D) B5D7bits;

__sfr __at (0xE7E) CANSTAT_RO4;
volatile __CANSTAT_RO4bits_t __at (0xE7E) CANSTAT_RO4bits;

__sfr __at (0xE7F) CANCON_RO4;
volatile __CANCON_RO4bits_t __at (0xE7F) CANCON_RO4bits;

__sfr __at (0xF00) RXF0SIDH;
volatile __RXF0SIDHbits_t __at (0xF00) RXF0SIDHbits;

__sfr __at (0xF01) RXF0SIDL;
volatile __RXF0SIDLbits_t __at (0xF01) RXF0SIDLbits;

__sfr __at (0xF02) RXF0EIDH;
volatile __RXF0EIDHbits_t __at (0xF02) RXF0EIDHbits;

__sfr __at (0xF03) RXF0EIDL;
volatile __RXF0EIDLbits_t __at (0xF03) RXF0EIDLbits;

__sfr __at (0xF04) RXF1SIDH;
volatile __RXF1SIDHbits_t __at (0xF04) RXF1SIDHbits;

__sfr __at (0xF05) RXF1SIDL;
volatile __RXF1SIDLbits_t __at (0xF05) RXF1SIDLbits;

__sfr __at (0xF06) RXF1EIDH;
volatile __RXF1EIDHbits_t __at (0xF06) RXF1EIDHbits;

__sfr __at (0xF07) RXF1EIDL;
volatile __RXF1EIDLbits_t __at (0xF07) RXF1EIDLbits;

__sfr __at (0xF08) RXF2SIDH;
volatile __RXF2SIDHbits_t __at (0xF08) RXF2SIDHbits;

__sfr __at (0xF09) RXF2SIDL;
volatile __RXF2SIDLbits_t __at (0xF09) RXF2SIDLbits;

__sfr __at (0xF0A) RXF2EIDH;
volatile __RXF2EIDHbits_t __at (0xF0A) RXF2EIDHbits;

__sfr __at (0xF0B) RXF2EIDL;
volatile __RXF2EIDLbits_t __at (0xF0B) RXF2EIDLbits;

__sfr __at (0xF0C) RXF3SIDH;
volatile __RXF3SIDHbits_t __at (0xF0C) RXF3SIDHbits;

__sfr __at (0xF0D) RXF3SIDL;
volatile __RXF3SIDLbits_t __at (0xF0D) RXF3SIDLbits;

__sfr __at (0xF0E) RXF3EIDH;
volatile __RXF3EIDHbits_t __at (0xF0E) RXF3EIDHbits;

__sfr __at (0xF0F) RXF3EIDL;
volatile __RXF3EIDLbits_t __at (0xF0F) RXF3EIDLbits;

__sfr __at (0xF10) RXF4SIDH;
volatile __RXF4SIDHbits_t __at (0xF10) RXF4SIDHbits;

__sfr __at (0xF11) RXF4SIDL;
volatile __RXF4SIDLbits_t __at (0xF11) RXF4SIDLbits;

__sfr __at (0xF12) RXF4EIDH;
volatile __RXF4EIDHbits_t __at (0xF12) RXF4EIDHbits;

__sfr __at (0xF13) RXF4EIDL;
volatile __RXF4EIDLbits_t __at (0xF13) RXF4EIDLbits;

__sfr __at (0xF14) RXF5SIDH;
volatile __RXF5SIDHbits_t __at (0xF14) RXF5SIDHbits;

__sfr __at (0xF15) RXF5SIDL;
volatile __RXF5SIDLbits_t __at (0xF15) RXF5SIDLbits;

__sfr __at (0xF16) RXF5EIDH;
volatile __RXF5EIDHbits_t __at (0xF16) RXF5EIDHbits;

__sfr __at (0xF17) RXF5EIDL;
volatile __RXF5EIDLbits_t __at (0xF17) RXF5EIDLbits;

__sfr __at (0xF18) RXM0SIDH;
volatile __RXM0SIDHbits_t __at (0xF18) RXM0SIDHbits;

__sfr __at (0xF19) RXM0SIDL;
volatile __RXM0SIDLbits_t __at (0xF19) RXM0SIDLbits;

__sfr __at (0xF1A) RXM0EIDH;
volatile __RXM0EIDHbits_t __at (0xF1A) RXM0EIDHbits;

__sfr __at (0xF1B) RXM0EIDL;
volatile __RXM0EIDLbits_t __at (0xF1B) RXM0EIDLbits;

__sfr __at (0xF1C) RXM1SIDH;
volatile __RXM1SIDHbits_t __at (0xF1C) RXM1SIDHbits;

__sfr __at (0xF1D) RXM1SIDL;
volatile __RXM1SIDLbits_t __at (0xF1D) RXM1SIDLbits;

__sfr __at (0xF1E) RXM1EIDH;
volatile __RXM1EIDHbits_t __at (0xF1E) RXM1EIDHbits;

__sfr __at (0xF1F) RXM1EIDL;
volatile __RXM1EIDLbits_t __at (0xF1F) RXM1EIDLbits;

__sfr __at (0xF20) TXB2CON;
volatile __TXB2CONbits_t __at (0xF20) TXB2CONbits;

__sfr __at (0xF21) TXB2SIDH;
volatile __TXB2SIDHbits_t __at (0xF21) TXB2SIDHbits;

__sfr __at (0xF22) TXB2SIDL;
volatile __TXB2SIDLbits_t __at (0xF22) TXB2SIDLbits;

__sfr __at (0xF23) TXB2EIDH;
volatile __TXB2EIDHbits_t __at (0xF23) TXB2EIDHbits;

__sfr __at (0xF24) TXB2EIDL;
volatile __TXB2EIDLbits_t __at (0xF24) TXB2EIDLbits;

__sfr __at (0xF25) TXB2DLC;
volatile __TXB2DLCbits_t __at (0xF25) TXB2DLCbits;

__sfr __at (0xF26) TXB2D0;
volatile __TXB2D0bits_t __at (0xF26) TXB2D0bits;

__sfr __at (0xF27) TXB2D1;
volatile __TXB2D1bits_t __at (0xF27) TXB2D1bits;

__sfr __at (0xF28) TXB2D2;
volatile __TXB2D2bits_t __at (0xF28) TXB2D2bits;

__sfr __at (0xF29) TXB2D3;
volatile __TXB2D3bits_t __at (0xF29) TXB2D3bits;

__sfr __at (0xF2A) TXB2D4;
volatile __TXB2D4bits_t __at (0xF2A) TXB2D4bits;

__sfr __at (0xF2B) TXB2D5;
volatile __TXB2D5bits_t __at (0xF2B) TXB2D5bits;

__sfr __at (0xF2C) TXB2D6;
volatile __TXB2D6bits_t __at (0xF2C) TXB2D6bits;

__sfr __at (0xF2D) TXB2D7;
volatile __TXB2D7bits_t __at (0xF2D) TXB2D7bits;

__sfr __at (0xF2E) CANSTAT_RO3;
volatile __CANSTAT_RO3bits_t __at (0xF2E) CANSTAT_RO3bits;

__sfr __at (0xF2F) CANCON_RO3;
volatile __CANCON_RO3bits_t __at (0xF2F) CANCON_RO3bits;

__sfr __at (0xF30) TXB1CON;
volatile __TXB1CONbits_t __at (0xF30) TXB1CONbits;

__sfr __at (0xF31) TXB1SIDH;
volatile __TXB1SIDHbits_t __at (0xF31) TXB1SIDHbits;

__sfr __at (0xF32) TXB1SIDL;
volatile __TXB1SIDLbits_t __at (0xF32) TXB1SIDLbits;

__sfr __at (0xF33) TXB1EIDH;
volatile __TXB1EIDHbits_t __at (0xF33) TXB1EIDHbits;

__sfr __at (0xF34) TXB1EIDL;
volatile __TXB1EIDLbits_t __at (0xF34) TXB1EIDLbits;

__sfr __at (0xF35) TXB1DLC;
volatile __TXB1DLCbits_t __at (0xF35) TXB1DLCbits;

__sfr __at (0xF36) TXB1D0;
volatile __TXB1D0bits_t __at (0xF36) TXB1D0bits;

__sfr __at (0xF37) TXB1D1;
volatile __TXB1D1bits_t __at (0xF37) TXB1D1bits;

__sfr __at (0xF38) TXB1D2;
volatile __TXB1D2bits_t __at (0xF38) TXB1D2bits;

__sfr __at (0xF39) TXB1D3;
volatile __TXB1D3bits_t __at (0xF39) TXB1D3bits;

__sfr __at (0xF3A) TXB1D4;
volatile __TXB1D4bits_t __at (0xF3A) TXB1D4bits;

__sfr __at (0xF3B) TXB1D5;
volatile __TXB1D5bits_t __at (0xF3B) TXB1D5bits;

__sfr __at (0xF3C) TXB1D6;
volatile __TXB1D6bits_t __at (0xF3C) TXB1D6bits;

__sfr __at (0xF3D) TXB1D7;
volatile __TXB1D7bits_t __at (0xF3D) TXB1D7bits;

__sfr __at (0xF3E) CANSTAT_RO2;
volatile __CANSTAT_RO2bits_t __at (0xF3E) CANSTAT_RO2bits;

__sfr __at (0xF3F) CANCON_RO2;
volatile __CANCON_RO2bits_t __at (0xF3F) CANCON_RO2bits;

__sfr __at (0xF40) TXB0CON;
volatile __TXB0CONbits_t __at (0xF40) TXB0CONbits;

__sfr __at (0xF41) TXB0SIDH;
volatile __TXB0SIDHbits_t __at (0xF41) TXB0SIDHbits;

__sfr __at (0xF42) TXB0SIDL;
volatile __TXB0SIDLbits_t __at (0xF42) TXB0SIDLbits;

__sfr __at (0xF43) TXB0EIDH;
volatile __TXB0EIDHbits_t __at (0xF43) TXB0EIDHbits;

__sfr __at (0xF44) TXB0EIDL;
volatile __TXB0EIDLbits_t __at (0xF44) TXB0EIDLbits;

__sfr __at (0xF45) TXB0DLC;
volatile __TXB0DLCbits_t __at (0xF45) TXB0DLCbits;

__sfr __at (0xF46) TXB0D0;
volatile __TXB0D0bits_t __at (0xF46) TXB0D0bits;

__sfr __at (0xF47) TXB0D1;
volatile __TXB0D1bits_t __at (0xF47) TXB0D1bits;

__sfr __at (0xF48) TXB0D2;
volatile __TXB0D2bits_t __at (0xF48) TXB0D2bits;

__sfr __at (0xF49) TXB0D3;
volatile __TXB0D3bits_t __at (0xF49) TXB0D3bits;

__sfr __at (0xF4A) TXB0D4;
volatile __TXB0D4bits_t __at (0xF4A) TXB0D4bits;

__sfr __at (0xF4B) TXB0D5;
volatile __TXB0D5bits_t __at (0xF4B) TXB0D5bits;

__sfr __at (0xF4C) TXB0D6;
volatile __TXB0D6bits_t __at (0xF4C) TXB0D6bits;

__sfr __at (0xF4D) TXB0D7;
volatile __TXB0D7bits_t __at (0xF4D) TXB0D7bits;

__sfr __at (0xF4E) CANSTAT_RO1;
volatile __CANSTAT_RO1bits_t __at (0xF4E) CANSTAT_RO1bits;

__sfr __at (0xF4F) CANCON_RO1;
volatile __CANCON_RO1bits_t __at (0xF4F) CANCON_RO1bits;

__sfr __at (0xF50) RXB1CON;
volatile __RXB1CONbits_t __at (0xF50) RXB1CONbits;

__sfr __at (0xF51) RXB1SIDH;
volatile __RXB1SIDHbits_t __at (0xF51) RXB1SIDHbits;

__sfr __at (0xF52) RXB1SIDL;
volatile __RXB1SIDLbits_t __at (0xF52) RXB1SIDLbits;

__sfr __at (0xF53) RXB1EIDH;
volatile __RXB1EIDHbits_t __at (0xF53) RXB1EIDHbits;

__sfr __at (0xF54) RXB1EIDL;
volatile __RXB1EIDLbits_t __at (0xF54) RXB1EIDLbits;

__sfr __at (0xF55) RXB1DLC;
volatile __RXB1DLCbits_t __at (0xF55) RXB1DLCbits;

__sfr __at (0xF56) RXB1D0;
volatile __RXB1D0bits_t __at (0xF56) RXB1D0bits;

__sfr __at (0xF57) RXB1D1;
volatile __RXB1D1bits_t __at (0xF57) RXB1D1bits;

__sfr __at (0xF58) RXB1D2;
volatile __RXB1D2bits_t __at (0xF58) RXB1D2bits;

__sfr __at (0xF59) RXB1D3;
volatile __RXB1D3bits_t __at (0xF59) RXB1D3bits;

__sfr __at (0xF5A) RXB1D4;
volatile __RXB1D4bits_t __at (0xF5A) RXB1D4bits;

__sfr __at (0xF5B) RXB1D5;
volatile __RXB1D5bits_t __at (0xF5B) RXB1D5bits;

__sfr __at (0xF5C) RXB1D6;
volatile __RXB1D6bits_t __at (0xF5C) RXB1D6bits;

__sfr __at (0xF5D) RXB1D7;
volatile __RXB1D7bits_t __at (0xF5D) RXB1D7bits;

__sfr __at (0xF5E) CANSTAT_RO0;
volatile __CANSTAT_RO0bits_t __at (0xF5E) CANSTAT_RO0bits;

__sfr __at (0xF5F) CANCON_RO0;
volatile __CANCON_RO0bits_t __at (0xF5F) CANCON_RO0bits;

__sfr __at (0xF60) RXB0CON;
volatile __RXB0CONbits_t __at (0xF60) RXB0CONbits;

__sfr __at (0xF61) RXB0SIDH;
volatile __RXB0SIDHbits_t __at (0xF61) RXB0SIDHbits;

__sfr __at (0xF62) RXB0SIDL;
volatile __RXB0SIDLbits_t __at (0xF62) RXB0SIDLbits;

__sfr __at (0xF63) RXB0EIDH;
volatile __RXB0EIDHbits_t __at (0xF63) RXB0EIDHbits;

__sfr __at (0xF64) RXB0EIDL;
volatile __RXB0EIDLbits_t __at (0xF64) RXB0EIDLbits;

__sfr __at (0xF65) RXB0DLC;
volatile __RXB0DLCbits_t __at (0xF65) RXB0DLCbits;

__sfr __at (0xF66) RXB0D0;
volatile __RXB0D0bits_t __at (0xF66) RXB0D0bits;

__sfr __at (0xF67) RXB0D1;
volatile __RXB0D1bits_t __at (0xF67) RXB0D1bits;

__sfr __at (0xF68) RXB0D2;
volatile __RXB0D2bits_t __at (0xF68) RXB0D2bits;

__sfr __at (0xF69) RXB0D3;
volatile __RXB0D3bits_t __at (0xF69) RXB0D3bits;

__sfr __at (0xF6A) RXB0D4;
volatile __RXB0D4bits_t __at (0xF6A) RXB0D4bits;

__sfr __at (0xF6B) RXB0D5;
volatile __RXB0D5bits_t __at (0xF6B) RXB0D5bits;

__sfr __at (0xF6C) RXB0D6;
volatile __RXB0D6bits_t __at (0xF6C) RXB0D6bits;

__sfr __at (0xF6D) RXB0D7;
volatile __RXB0D7bits_t __at (0xF6D) RXB0D7bits;

__sfr __at (0xF6E) CANSTAT;
volatile __CANSTATbits_t __at (0xF6E) CANSTATbits;

__sfr __at (0xF6F) CANCON;
volatile __CANCONbits_t __at (0xF6F) CANCONbits;

__sfr __at (0xF70) BRGCON1;
volatile __BRGCON1bits_t __at (0xF70) BRGCON1bits;

__sfr __at (0xF71) BRGCON2;
volatile __BRGCON2bits_t __at (0xF71) BRGCON2bits;

__sfr __at (0xF72) BRGCON3;
volatile __BRGCON3bits_t __at (0xF72) BRGCON3bits;

__sfr __at (0xF73) CIOCON;
volatile __CIOCONbits_t __at (0xF73) CIOCONbits;

__sfr __at (0xF74) COMSTAT;
volatile __COMSTATbits_t __at (0xF74) COMSTATbits;

__sfr __at (0xF75) RXERRCNT;
volatile __RXERRCNTbits_t __at (0xF75) RXERRCNTbits;

__sfr __at (0xF76) TXERRCNT;
volatile __TXERRCNTbits_t __at (0xF76) TXERRCNTbits;

__sfr __at (0xF77) ECANCON;
volatile __ECANCONbits_t __at (0xF77) ECANCONbits;

__sfr __at (0xF80) PORTA;
volatile __PORTAbits_t __at (0xF80) PORTAbits;

__sfr __at (0xF81) PORTB;
volatile __PORTBbits_t __at (0xF81) PORTBbits;

__sfr __at (0xF82) PORTC;
volatile __PORTCbits_t __at (0xF82) PORTCbits;

__sfr __at (0xF83) PORTD;
volatile __PORTDbits_t __at (0xF83) PORTDbits;

__sfr __at (0xF84) PORTE;
volatile __PORTEbits_t __at (0xF84) PORTEbits;

__sfr __at (0xF89) LATA;
volatile __LATAbits_t __at (0xF89) LATAbits;

__sfr __at (0xF8A) LATB;
volatile __LATBbits_t __at (0xF8A) LATBbits;

__sfr __at (0xF8B) LATC;
volatile __LATCbits_t __at (0xF8B) LATCbits;

__sfr __at (0xF8C) LATD;
volatile __LATDbits_t __at (0xF8C) LATDbits;

__sfr __at (0xF8D) LATE;
volatile __LATEbits_t __at (0xF8D) LATEbits;

__sfr __at (0xF92) DDRA;
volatile __DDRAbits_t __at (0xF92) DDRAbits;

__sfr __at (0xF92) TRISA;
volatile __TRISAbits_t __at (0xF92) TRISAbits;

__sfr __at (0xF93) DDRB;
volatile __DDRBbits_t __at (0xF93) DDRBbits;

__sfr __at (0xF93) TRISB;
volatile __TRISBbits_t __at (0xF93) TRISBbits;

__sfr __at (0xF94) DDRC;
volatile __DDRCbits_t __at (0xF94) DDRCbits;

__sfr __at (0xF94) TRISC;
volatile __TRISCbits_t __at (0xF94) TRISCbits;

__sfr __at (0xF95) DDRD;
volatile __DDRDbits_t __at (0xF95) DDRDbits;

__sfr __at (0xF95) TRISD;
volatile __TRISDbits_t __at (0xF95) TRISDbits;

__sfr __at (0xF96) DDRE;
volatile __DDREbits_t __at (0xF96) DDREbits;

__sfr __at (0xF96) TRISE;
volatile __TRISEbits_t __at (0xF96) TRISEbits;

__sfr __at (0xF9B) OSCTUNE;
volatile __OSCTUNEbits_t __at (0xF9B) OSCTUNEbits;

__sfr __at (0xF9D) PIE1;
volatile __PIE1bits_t __at (0xF9D) PIE1bits;

__sfr __at (0xF9E) PIR1;
volatile __PIR1bits_t __at (0xF9E) PIR1bits;

__sfr __at (0xF9F) IPR1;
volatile __IPR1bits_t __at (0xF9F) IPR1bits;

__sfr __at (0xFA0) PIE2;
volatile __PIE2bits_t __at (0xFA0) PIE2bits;

__sfr __at (0xFA1) PIR2;
volatile __PIR2bits_t __at (0xFA1) PIR2bits;

__sfr __at (0xFA2) IPR2;
volatile __IPR2bits_t __at (0xFA2) IPR2bits;

__sfr __at (0xFA3) PIE3;
volatile __PIE3bits_t __at (0xFA3) PIE3bits;

__sfr __at (0xFA4) PIR3;
volatile __PIR3bits_t __at (0xFA4) PIR3bits;

__sfr __at (0xFA5) IPR3;
volatile __IPR3bits_t __at (0xFA5) IPR3bits;

__sfr __at (0xFA6) EECON1;
volatile __EECON1bits_t __at (0xFA6) EECON1bits;

__sfr __at (0xFA7) EECON2;

__sfr __at (0xFA8) EEDATA;

__sfr __at (0xFA9) EEADR;

__sfr __at (0xFAA) EEADRH;

__sfr __at (0xFAB) RCSTA;
volatile __RCSTAbits_t __at (0xFAB) RCSTAbits;

__sfr __at (0xFAC) TXSTA;
volatile __TXSTAbits_t __at (0xFAC) TXSTAbits;

__sfr __at (0xFAD) TXREG;

__sfr __at (0xFAE) RCREG;

__sfr __at (0xFAF) SPBRG;

__sfr __at (0xFB0) SPBRGH;

__sfr __at (0xFB1) T3CON;
volatile __T3CONbits_t __at (0xFB1) T3CONbits;

__sfr __at (0xFB2) TMR3L;

__sfr __at (0xFB3) TMR3H;

__sfr __at (0xFB4) CMCON;
volatile __CMCONbits_t __at (0xFB4) CMCONbits;

__sfr __at (0xFB5) CVRCON;
volatile __CVRCONbits_t __at (0xFB5) CVRCONbits;

__sfr __at (0xFB6) ECCP1AS;
volatile __ECCP1ASbits_t __at (0xFB6) ECCP1ASbits;

__sfr __at (0xFB7) ECCP1DEL;
volatile __ECCP1DELbits_t __at (0xFB7) ECCP1DELbits;

__sfr __at (0xFB8) BAUDCON;
volatile __BAUDCONbits_t __at (0xFB8) BAUDCONbits;

__sfr __at (0xFBA) ECCP1CON;
volatile __ECCP1CONbits_t __at (0xFBA) ECCP1CONbits;

__sfr __at (0xFBB) ECCPR1;

__sfr __at (0xFBB) ECCPR1L;

__sfr __at (0xFBC) ECCPR1H;

__sfr __at (0xFBD) CCP1CON;
volatile __CCP1CONbits_t __at (0xFBD) CCP1CONbits;

__sfr __at (0xFBE) CCPR1;

__sfr __at (0xFBE) CCPR1L;

__sfr __at (0xFBF) CCPR1H;

__sfr __at (0xFC0) ADCON2;
volatile __ADCON2bits_t __at (0xFC0) ADCON2bits;

__sfr __at (0xFC1) ADCON1;
volatile __ADCON1bits_t __at (0xFC1) ADCON1bits;

__sfr __at (0xFC2) ADCON0;
volatile __ADCON0bits_t __at (0xFC2) ADCON0bits;

__sfr __at (0xFC3) ADRES;

__sfr __at (0xFC3) ADRESL;

__sfr __at (0xFC4) ADRESH;

__sfr __at (0xFC5) SSPCON2;
volatile __SSPCON2bits_t __at (0xFC5) SSPCON2bits;

__sfr __at (0xFC6) SSPCON1;
volatile __SSPCON1bits_t __at (0xFC6) SSPCON1bits;

__sfr __at (0xFC7) SSPSTAT;
volatile __SSPSTATbits_t __at (0xFC7) SSPSTATbits;

__sfr __at (0xFC8) SSPADD;

__sfr __at (0xFC9) SSPBUF;

__sfr __at (0xFCA) T2CON;
volatile __T2CONbits_t __at (0xFCA) T2CONbits;

__sfr __at (0xFCB) PR2;

__sfr __at (0xFCC) TMR2;

__sfr __at (0xFCD) T1CON;
volatile __T1CONbits_t __at (0xFCD) T1CONbits;

__sfr __at (0xFCE) TMR1L;

__sfr __at (0xFCF) TMR1H;

__sfr __at (0xFD0) RCON;
volatile __RCONbits_t __at (0xFD0) RCONbits;

__sfr __at (0xFD1) WDTCON;
volatile __WDTCONbits_t __at (0xFD1) WDTCONbits;

__sfr __at (0xFD2) HLVDCON;
volatile __HLVDCONbits_t __at (0xFD2) HLVDCONbits;

__sfr __at (0xFD2) LVDCON;
volatile __LVDCONbits_t __at (0xFD2) LVDCONbits;

__sfr __at (0xFD3) OSCCON;
volatile __OSCCONbits_t __at (0xFD3) OSCCONbits;

__sfr __at (0xFD5) T0CON;
volatile __T0CONbits_t __at (0xFD5) T0CONbits;

__sfr __at (0xFD6) TMR0L;

__sfr __at (0xFD7) TMR0H;

__sfr __at (0xFD8) STATUS;
volatile __STATUSbits_t __at (0xFD8) STATUSbits;

__sfr __at (0xFD9) FSR2L;

__sfr __at (0xFDA) FSR2H;

__sfr __at (0xFDB) PLUSW2;

__sfr __at (0xFDC) PREINC2;

__sfr __at (0xFDD) POSTDEC2;

__sfr __at (0xFDE) POSTINC2;

__sfr __at (0xFDF) INDF2;

__sfr __at (0xFE0) BSR;

__sfr __at (0xFE1) FSR0L;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFE2) FSR0H;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFE3) PLUSW0;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFE4) PREINC0;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFE5) POSTDEC0;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFE6) POSTINC0;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFE7) INDF0;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFE8) WREG;

__sfr __at (0xFE9) FSR1L;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFEA) FSR1H;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFEB) PLUSW1;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFEC) PREINC1;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFED) POSTDEC1;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFEE) POSTINC1;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFEF) INDF1;				// FSR0 and FSR1 swapped for MIOS SDCC Wrapper compatibility

__sfr __at (0xFF0) INTCON3;
volatile __INTCON3bits_t __at (0xFF0) INTCON3bits;

__sfr __at (0xFF1) INTCON2;
volatile __INTCON2bits_t __at (0xFF1) INTCON2bits;

__sfr __at (0xFF2) INTCON;
volatile __INTCONbits_t __at (0xFF2) INTCONbits;

__sfr __at (0xFF3) PROD;

__sfr __at (0xFF3) PRODL;

__sfr __at (0xFF4) PRODH;

__sfr __at (0xFF5) TABLAT;

__sfr __at (0xFF6) TBLPTR;

__sfr __at (0xFF6) TBLPTRL;

__sfr __at (0xFF7) TBLPTRH;

__sfr __at (0xFF8) TBLPTRU;

__sfr __at (0xFF9) PC;

__sfr __at (0xFF9) PCL;

__sfr __at (0xFFA) PCLATH;

__sfr __at (0xFFB) PCLATU;

__sfr __at (0xFFC) STKPTR;
volatile __STKPTRbits_t __at (0xFFC) STKPTRbits;

__sfr __at (0xFFD) TOS;

__sfr __at (0xFFD) TOSL;

__sfr __at (0xFFE) TOSH;

__sfr __at (0xFFF) TOSU;




 

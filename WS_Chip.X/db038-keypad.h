//
// Hi-Tech Lite include file for DB038 board with 16F887:
// keypad functions
//
// $Id: db038-keypad.h,v 1.3 2012/04/24 17:25:22 Wouter Exp $
//
// (c) Wouter van Ooijen - wouter@voti.nl
//
// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.
// 

#ifndef _DB038_KEYPAD_
#define _DB038_KEYPAD_

#include "db038.h"

#define KEYPAD_0         0
#define KEYPAD_1         1
#define KEYPAD_2         2
#define KEYPAD_3         3
#define KEYPAD_4         4
#define KEYPAD_5         5
#define KEYPAD_6         6
#define KEYPAD_7         7
#define KEYPAD_8         8
#define KEYPAD_9         9
#define KEYPAD_A      0x0A
#define KEYPAD_B      0x0B
#define KEYPAD_C      0x0C
#define KEYPAD_D      0x0D
#define KEYPAD_S      0x0E
#define KEYPAD_H      0x0F
#define KEYPAD_NONE   0xFF

unsigned char keypad_read( void );
unsigned char key_is_pressed( unsigned char key );
char ascii_from_key( unsigned char x );

#endif

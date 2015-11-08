//
// Hi-Tech Lite source file for DB038 board with 16F887:
// keypad functions
//
// $Id: db038-keypad.c,v 1.4 2012/04/24 17:25:21 Wouter Exp $
//
// (c) 2009 Wouter van Ooijen - wouter@voti.nl
//
// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.
// 

#include "db038-keypad.h"

#define KEY_XY( x, y ) ((((x)+4) << 4 ) + (1 << (y)))
const unsigned char keypad_location[] = {
   KEY_XY( 1, 0 ),  // KEYPAD_0
   KEY_XY( 0, 3 ),  // KEYPAD_1
   KEY_XY( 1, 3 ),  // KEYPAD_2
   KEY_XY( 2, 3 ),  // KEYPAD_3  
   KEY_XY( 0, 2 ),  // KEYPAD_4
   KEY_XY( 1, 2 ),  // KEYPAD_5
   KEY_XY( 2, 2 ),  // KEYPAD_6
   KEY_XY( 0, 1 ),  // KEYPAD_7
   KEY_XY( 1, 1 ),  // KEYPAD_8
   KEY_XY( 2, 1 ),  // KEYPAD_9
   KEY_XY( 3, 3 ),  // KEYPAD_A                  
   KEY_XY( 3, 2 ),  // KEYPAD_B                  
   KEY_XY( 3, 1 ),  // KEYPAD_C                  
   KEY_XY( 3, 0 ),  // KEYPAD_D
   KEY_XY( 0, 0 ),  // KEYPAD_S
   KEY_XY( 2, 0 ),  // KEYPAD_H
}; 

const char ascii_from_key_table[] = {
   '0',
   '1',
   '2',
   '3',
   '4',
   '5',
   '6',
   '7',
   '8',
   '9',
   'A',
   'B',
   'C',
   'D',
   '*',
   '#'
};   	            

char ascii_from_key( unsigned char x ){
   return ascii_from_key_table[ x & 0x0F ];   
}

unsigned char keypad_read( void ){
   unsigned char key, location;
   for( key = 0; key < 16; key++ ){
      location = keypad_location[ key ];
      PIN_CLEAR( PORTA, 2 ); // LEDs off
      PIN_DIRECTION( PORTA, 2, OUTPUT );
      PIN_DIRECTION( PORTA, 1, INPUT );
      disable_analog_functions();
      PORT_SET( PORTE, location >> 4 );
      PORT_SET( PORTD, location & 0x0F );
      TRISE = 0;
      TRISD = 0;
      WAIT_US( 150 );      
      if ( PORTA & 0x02 ){
         return key;
      }
   }
   return KEYPAD_NONE;
}
unsigned char key_is_pressed( unsigned char key ){
   unsigned char location = keypad_location[ key & 0x0F ];
   PIN_CLEAR( PORTA, 2 ); // LEDs off
   PIN_DIRECTION( PORTA, 2, OUTPUT );
   PIN_DIRECTION( PORTA, 1, INPUT );
   disable_analog_functions();
   PORT_SET( PORTE, location >> 4 );
   PORT_SET( PORTD, location & 0x0F );
   TRISE = 0;
   TRISD = 0;
   WAIT_US( 50 );      
   return ( PORTA & 0x02 );
}	

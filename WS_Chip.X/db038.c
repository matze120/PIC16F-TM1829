//
// Hi-Tech Lite source file for DB038 board with 16F887:
// basic functions
//
// $Id: db038.c,v 1.4 2012/04/24 17:25:31 Wouter Exp $
//
// (c) Wouter van Ooijen - wouter@voti.nl
//
// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.
// 

#include "db038.h"

#if defined(_16F887)
   __CONFIG( 0x20E2 );   // -debug, -LVP, -fcmen, -ieso, -boren,
                         // -cpd, -cp, mclre, pwtre, -wdte, HSosc
#elif defined(__18F4520)
   #pragma config OSC = HS
   #pragma config PWRT = ON, WDT = OFF
   #pragma config LVP = OFF, DEBUG = OFF
   #pragma config CP0 = ON, CP1 = ON, CP2 = ON, CP3 = ON, CPB = ON, CPD = ON
   #pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = ON
#else
   #error unsupported chip
#endif

#ifdef DB038_PIC14

   // wait the indicated number of milliseconds
   void wait_ms( unsigned int x ){
      while( x > 0){

         // wait one millisecond
         WAIT_US( 1000 );

         x--;
      }
   }

   // create the shadow regsiters
   unsigned char PORTA_SHADOW;
   unsigned char PORTB_SHADOW;
   unsigned char PORTC_SHADOW;
   unsigned char PORTD_SHADOW;
   unsigned char PORTE_SHADOW;

   void disable_analog_functions( void ){
      ANSEL &= ( 1 << 1 ) ^ 0xFF;
   }

#endif


#ifdef DB038_PIC16

   #include <delays.h>

   #define STEP 10U
   #define CYCLES ( STEP * ( XTAL_FREQ / ( 4 MHZ )))

   // wait (at least!) the indicated number of microseconds
   void WAIT_US( unsigned int x ){
      Delay10TCYx( CYCLES );
      for( ; x > STEP; x -= STEP ){
         Delay10TCYx( CYCLES );  
      }
   }

   // wait the indicated number of milliseconds
   void wait_ms( unsigned int x ){
      while( x-- > 0 ){
         Delay1KTCYx( XTAL_FREQ / ( 4 MHZ ) );
      }
   }

   void disable_analog_functions( void ){
      ADCON1 = 0x0F;
   }

#endif

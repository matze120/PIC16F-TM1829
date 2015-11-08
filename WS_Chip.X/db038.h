//
// Hi-Tech Lite include file for DB038 board with 16F887:
// basic functions
//
// $Id: db038.h,v 1.4 2012/04/24 17:25:32 Wouter Exp $
//
// (c) Wouter van Ooijen - wouter@voti.nl
//
// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.
// 

#ifndef _DB038_H_
#define _DB038_H_

#if defined(_16F887)
   #define DB038_PIC14
#elif defined(__18F4520)
   #define DB038_PIC16
#else
   #error unsupported chip
#endif

#define MHZ *1000L            // number of kHz in a MHz
#define KHZ *1                // number of kHz in a kHz
#define XTAL_FREQ ( 20 MHZ )  // we run at 20 MHz

#ifdef DB038_PIC14

   #define rom 

   #include <pic.h>              // include target-specific stuff
   #define WAIT_US( x ) _delay( x * ( XTAL_FREQ / ( 4 MHZ )))
   void wait_ms( unsigned int x );

   extern unsigned char PORTA_SHADOW;
   extern unsigned char PORTB_SHADOW;
   extern unsigned char PORTC_SHADOW;
   extern unsigned char PORTD_SHADOW;
   extern unsigned char PORTE_SHADOW;

   #define PORTA_FLUSH { PORTA = PORTA_SHADOW; }
   #define PORTB_FLUSH { PORTB = PORTB_SHADOW; }
   #define PORTC_FLUSH { PORTC = PORTC_SHADOW; }
   #define PORTD_FLUSH { PORTD = PORTD_SHADOW; }
   #define PORTE_FLUSH { PORTE = PORTE_SHADOW; }

   #define PIN_SET( port, b ) do { \
      port##_SHADOW |= ( 1 << (b) ); \
      port = port##_SHADOW; \
   } while(0)

   #define PIN_CLEAR( port, b ) do { \
      port##_SHADOW &= ( 0xFF ^ ( 1 << (b) )); \
      port = port##_SHADOW; \
   } while(0)

   #define PIN_COPY( port, b, v ) do { \
      if( v ){  \
   	     PIN_SET( port, (b) ); \
      } else { \
        PIN_CLEAR( port, (b) ); } \
   } while(0)
   	
   #define PORT_SET( port, v ) do { \
      port##_SHADOW = ( (v) ); \
      port = port##_SHADOW; \
   } while(0)   

#endif

#ifdef DB038_PIC16

   #define rom rom

   #include <p18cxxx.h>       // include target-specific stuff
   void WAIT_US( unsigned int x );
   void wait_ms( unsigned int x );

   #define  PORTA_LAT LATA
   #define  PORTB_LAT LATB
   #define  PORTC_LAT LATC
   #define  PORTD_LAT LATD
   #define  PORTE_LAT LATE

   #define PIN_SET( port, b ) do { \
      port##_LAT |= ( 1 << (b) ); \
   } while(0)

   #define PIN_CLEAR( port, b ) do { \
      port##_LAT &= ( 0xFF ^ ( 1 << (b) )); \
   } while(0)

   #define PIN_COPY( port, b, v ) do { \
      if( v ){  \
   	     PIN_SET( port, (b) ); \
      } else { \
        PIN_CLEAR( port, (b) ); } \
   } while(0)
   	
   #define PORT_SET( port, v ) do { \
      port##_LAT = ( (v) ); \
   } while(0)  

#endif

#define INPUT 1
#define OUTPUT 0

#define  PORTA_DIRECTION TRISA
#define  PORTB_DIRECTION TRISB
#define  PORTC_DIRECTION TRISC
#define  PORTD_DIRECTION TRISD
#define  PORTE_DIRECTION TRISE

#define PIN_DIRECTION( port, pin, d ) do { \
  if( (d) == INPUT ){  \
      port##_DIRECTION |= ( 1 << (pin) ); \
   } else { \
      port##_DIRECTION &= ( 0xFF ^ ( 1 << (pin) )); \
   } \
} while(0)

#define PORT_DIRECTION( port, d ) do { \
    if( (d) == INPUT ){  \
      port##_DIRECTION = 0xFF; \
   } else { \
      port##_DIRECTION = 0x00; } \
} while(0)

void disable_analog_functions( void );

#endif

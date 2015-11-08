/* 
 * File:   WS_Chip.c
 * Author: marcelfornacon
 *
 * Created on 1. März 2014, 15:50
 */

#include <stdio.h>
#include <stdlib.h>
#include "pic16f887.h"
/*
 *
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#define _XTAL_FREQ 20000000
/*
 * 
 */

unsigned char i = 0;

int LEDData[6][3] = {
                        {0xff, 0x00, 0x00},
                        {0x00, 0xff, 0x00},
                        {0x00, 0x00, 0xff},
                        {0xff, 0x00, 0x00},
                        {0x00, 0xff, 0x00},
                        {0x00, 0x00, 0xff},
                    };

unsigned char index1 = 0;
unsigned char index2 = 1;
unsigned char index3 = 2;
unsigned char index4 = 0;
unsigned char index5 = 1;
unsigned char index6 = 2;
unsigned char indexHelp = 0;



/*
 *
 */


void wait_ms(unsigned int time)
{
    unsigned int Ti;
    while (time > Ti)
    {
        Ti++;
    __delay_us(1000);
    }
    
    Ti = 0;
}

void _0(void)
{
    RD0 = 0;
    RD0 = 0;
    RD0 = 1;
    __delay_us(1);
}

void _1(void)
{
    RD0 = 0;
    RD0 = 0;
    RD0 = 0;
    RD0 = 0;
    RD0 = 0;
    RD0 = 0;
    RD0 = 0;
    RD0 = 0;

    RD0 = 1;
    __delay_us(1);
}

void initLED(void)
{
        _1();           //MSB Blue
        _1();
        _1();
        _1();
        _1();  
        _1();
        _1();
        _1();
        
        _1();           //MSB Red
        _1();
        _1();
        _1();
        _1();
        
        _1();
        _1();
        _1();
        _1();           //MSB Green
        _1();
        
        _1();      
        _1();
        _1();
        _1();
        _1();
        
        _0();
}

void sendBit(unsigned char HL)
{
    if(HL == 1)
    {
        RD0 = 0;
        RD0 = 0;
        RD0 = 0;
        RD0 = 0;
        RD0 = 0;
        RD0 = 0;
        RD0 = 0;
        RD0 = 0;
        
        RD0 = 1;
        __delay_us(1);
    }
    else
    {
        RD0 = 0;
        RD0 = 0;
        RD0 = 1;
        __delay_us(1);
    }
}

void sendRGB(unsigned char red, unsigned char green, unsigned char blue)
{
        sendBit(red && 0b10000000);
        sendBit(red && 0b01000000);
        sendBit(red && 0b00100000);
        sendBit(red && 0b00010000);
        sendBit(red && 0b00001000);
        sendBit(red && 0b00000100);
        sendBit(red && 0b00000010);
        sendBit(0);
        
        sendBit(green && 0b10000000);
        sendBit(green && 0b01000000);
        sendBit(green && 0b00100000);
        sendBit(green && 0b00010000);
        sendBit(green && 0b00001000);
        sendBit(green && 0b00000100);
        sendBit(green && 0b00000010);
        sendBit(0);
        
        sendBit(blue && 0b10000000);
        sendBit(blue && 0b01000000);
        sendBit(blue && 0b00100000);
        sendBit(blue && 0b00010000);
        sendBit(blue && 0b00001000);
        sendBit(blue && 0b00000100);
        sendBit(blue && 0b00000010);
        sendBit(0);

        __delay_us(50);
}

void sendLEDData(unsigned char LED, unsigned char LEDNumber)
{
    unsigned char i = 0;
    while(LEDNumber > i)
    {
    sendRGB(LEDData[i][0], LEDData[i][1], LEDData[i][2]);
    i++;
    }
}

void resetLED()
{
    __delay_us(500);
}

void main(void)
{
    GIE = 0;
    
    TRISD0 = 0;
    RD0 = 1;
    
    initLED();
    
    __delay_us(500);
    /*
    while(i < 10)
    {
        _0();           //MSB Blue
        _1();
        _1();
        _1();
        _1();  
        _1();
        _0();
        _0();           //Always 0
        
        _0();           //MSB Red
        _0();
        _0();
        _0();
        _0(); 
        _0();
        _0();
        _0();           //Always 0
        
        _0();           //MSB Green
        _0();
        _0();      
        _0();
        _0();
        _0();
        _0();
        _0();           //Always 0 
        
        //wait_ms(50);
        __delay_us(50);
        i++;
    }
    i=0;
    
    
    while(i < 10)
    {
        _0();           //MSB Blue
        _0();
        _0();
        _0();
        _0();  
        _0();
        _0();
        _0();           //Always 0
        
        _1();           //MSB Red
        _1();
        _1();
        _1();
        _1(); 
        _1();
        _1();
        _0();           //Always 0
        
        _0();           //MSB Green
        _0();
        _0();      
        _0();
        _0();
        _0();
        _0();
        _0();           //Always 0 
        
        //wait_ms(50);
        __delay_us(50);
        i++;
    }
    i=0;
    
    
    while(i < 10)
    {
        _0();           //MSB Blue
        _0();
        _0();
        _0();
        _0();  
        _0();
        _0();
        _0();           //Always 0
        
        _0();           //MSB Red
        _0();
        _0();
        _0();
        _0(); 
        _0();
        _0();
        _0();           //Always 0
        
        _1();           //MSB Green
        _1();
        _1();      
        _1();
        _1();
        _1();
        _1();
        _0();           //Always 0 
        
        //wait_ms(50);
        __delay_us(50);
        i++;
    }
    i=0;
    
    
    while(i < 20)
    {
        _0();           //MSB Blue
        _0();
        _0();
        _0();
        _0();  
        _0();
        _0();
        _0();           //Always 0
        
        _0();           //MSB Red
        _0();
        _0();
        _0();
        _0(); 
        _0();
        _0();
        _0();           //Always 0
        
        _0();           //MSB Green
        _0();
        _0();      
        _0();
        _0();
        _0();
        _0();
        _0();           //Always 0 
        
        //wait_ms(50);
        __delay_us(50);
        i++;
    }
    i=0;
     * 
     */
    
    /*
    while(i < 3)
    {
        sendRGB(0xFF,0xFF,0xFF);
        i++;
    }
    i=0;
    */
    
    sendLEDData(LEDData,3);
    
    resetLED();
    __delay_ms(1000);

    
    
    //initLED();
    
    LEDData[0][0] = 0x00;
    LEDData[0][1] = 0xff;
    LEDData[0][2] = 0x00;
    
    LEDData[1][0] = 0x00;
    LEDData[1][1] = 0x00;
    LEDData[1][2] = 0xff;
    
    LEDData[2][0] = 0xff;
    LEDData[2][1] = 0x00;
    LEDData[2][2] = 0x00;
    
                        //{0x00, 0x00, 0xff},
                        //{0xff, 0x00, 0x00},
                        //{0x00, 0xff, 0x00},
                        //{0x00, 0x00, 0xff},
                        //{0xff, 0x00, 0x00},
                    //};
    
    while(1)
    {
    LEDData[index1][0] = 0xff;
    LEDData[index1][1] = 0x00;
    LEDData[index1][2] = 0x00;   
    
    LEDData[index2][0] = 0x00;
    LEDData[index2][1] = 0xff;
    LEDData[index2][2] = 0x00;
    
    LEDData[index3][0] = 0x00;
    LEDData[index3][1] = 0x00;
    LEDData[index3][2] = 0xff;
    
    
    
    indexHelp = index1;
    index1 = index2;
    index2 = index3;
    index3 = indexHelp;
    
    
    sendLEDData(LEDData,3);
    resetLED();
    __delay_ms(100);
    
    }

    
}


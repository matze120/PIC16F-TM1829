/* 2012-09-12 - Patrick Cantwell

Code to work with WS2811 LEDs (pixels, strips, etc). Updated 2012-10-05 to fix the ugly for() loop syntax..

Note: in the current code 24 bit color is defined as 0xRRGGBB, however for strips with different color order you'll need to change that up (ex: 0xGGRRBB). This is easier than messing with the routine that writes the data out to the strips (for now...)

*/

#include <18f46k22.h>
#Fuses INTRC_IO,PLLEN,PRIMARY_ON,NOFCMEN,NOIESO,PUT,
#Fuses BROWNOUT,BORV29,NOWDT,
#Fuses CCP2C1,NOPBADEN,CCP3B5,
#Fuses NOHFOFST,TIMER3B5,NOMCLR,
#Fuses NOSTVREN,NOLVP,NOXINST,NODEBUG
#Fuses NOPROTECT,NOCPB,NOCPD,NOWRT,NOWRTC
#Fuses NOWRTB,NOWRTD,NOEBTR,NOEBTRB

#use delay( clock=64000000,INTERNAL )
#USE SPI (MASTER, SPI1, MODE=0, BITS=8, STREAM=SPI_1, MSB_FIRST)

#define LED_STRIP_LEN 50
unsigned int32 led_strip_colors[LED_STRIP_LEN];

#define ws2811_zero 0b10000000
#define ws2811_one 0b11110000

void single_color(unsigned int32 color1) {
  unsigned long i;
  for(i=0; i<LED_STRIP_LEN; i++) {
    led_strip_colors[i] = color1;
  }
}

void dual_color(unsigned int32 color1, unsigned int32 color2) {
  unsigned long i;
  for(i=0; i<LED_STRIP_LEN; i++) {
    if((i%2) == 0) led_strip_colors[i] = color1;
    if((i%2) == 1) led_strip_colors[i] = color2;
  }
}

void tri_color(unsigned int32 color1, unsigned int32 color2, unsigned int32 color3) {
  unsigned long i;
  for(i=0; i<LED_STRIP_LEN; i++) {
    if((i%3) == 0) led_strip_colors[i] = color1;
    if((i%3) == 1) led_strip_colors[i] = color2;
    if((i%3) == 2) led_strip_colors[i] = color3;
  }
}

void send_frame() {  //clever, cleaner way of doing this. Thanks to the help on the CCS message boards. Test a singular bit, and then march the bits to the left..
  unsigned int16 i;
  unsigned int32 this_led;
  unsigned int bit;
  
  for(i=0;i<LED_STRIP_LEN;i++) {
    this_led = led_strip_colors[i];         // assign this LED's color to a throwaway variable
    for(bit=0;bit<24;bit++) {
      if(bit_test(this_led, 23)) {          // test fixed bit 23
        spi_write(ws2811_one);
      }
      else {
        spi_write(ws2811_zero);
      }
      this_led*=2;                          // march all the bits one position to the left so the 22nd bit is now in the 23rd position, etc..
    }
  }
  delay_us(50);                             // wait 50us to latch the string
}

void main(void) {

  unsigned int16 i;
  unsigned int j;
  setup_spi( SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_16 );

  delay_ms(250);

  single_color(0xFFC58F);
  send_frame();
  delay_ms(5000);
  single_color(0xFF9329);
  send_frame();
  delay_ms(5000);
  single_color(0xFF0000);
  send_frame();
  delay_ms(1000);
  single_color(0x00FF00);
  send_frame();
  delay_ms(1000);
  single_color(0x0000FF);
  send_frame();
  delay_ms(1000);
  tri_color(0xFF0000,0xFFC58F,0x0000FF);
  send_frame();
  sleep();


/* // this is some quick and dirty example code to clear a string of 50 LEDs, and then light them all red, blue, green  
  for(i=0;i<1200;i++) {
    spi_write(ws2811_zero);
  }
  delay_us(50);

  for(i=0;i<15;i++) {
    for(j=0;j<8;j++) {
      spi_write(ws2811_one);
    }
    for(j=0;j<8;j++) {
      spi_write(ws2811_zero);
    }
    for(j=0;j<8;j++) {
      spi_write(ws2811_zero);
    }    
  }
  for(i=0;i<15;i++) {
    for(j=0;j<8;j++) {
      spi_write(ws2811_zero);
    }
    for(j=0;j<8;j++) {
      spi_write(ws2811_one);
    }
    for(j=0;j<8;j++) {
      spi_write(ws2811_zero);
    }
  }
  for(i=0;i<20;i++) {
    for(j=0;j<8;j++) {
      spi_write(ws2811_zero);
    }
    for(j=0;j<8;j++) {
      spi_write(ws2811_zero);
    }
    for(j=0;j<8;j++) {
      spi_write(ws2811_one);
    }
  }
  delay_us(50);
*/
}

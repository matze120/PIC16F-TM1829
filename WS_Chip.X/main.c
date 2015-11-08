#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include "delay_x.h"

#define BIT(B)           (0x01 << (uint8_t)(B))
#define SET_BIT_HI(V, B) (V) |= (uint8_t)BIT(B)
#define SET_BIT_LO(V, B) (V) &= (uint8_t)~BIT(B)

#define PORT  PORTB
#define DDR    DDRB
#define PIN       0

#define RESET    50	// usec
#define ON_HI   600	// nsec
#define ON_LO   650	// nsec
#define OFF_HI  250	// nsec
#define OFF_LO 1000	// nsec

#define PAUSE  1000     // msec
#define DELAY    25	// msec
 
static void rgb(uint8_t r, uint8_t g, uint8_t b)
{
	// Reset.
	SET_BIT_LO(PORTB, PIN);
	_delay_us(RESET);

	// Green
	for (uint8_t bit = 0; bit < 8; bit++) {
		if (g & 0x80) {
			SET_BIT_HI(PORT, PIN);
			_delay_ns(ON_HI);
			SET_BIT_LO(PORT, PIN);
			_delay_ns(ON_LO);
		} else {
			SET_BIT_HI(PORT, PIN);
			_delay_ns(OFF_HI);
			SET_BIT_LO(PORT, PIN);
			_delay_ns(OFF_LO);
		}
		g <<= 1;
	}

	// Red
	for (uint8_t bit = 0; bit < 8; bit++) {
		if (r & 0x80) {
			SET_BIT_HI(PORT, PIN);
			_delay_ns(ON_HI);
			SET_BIT_LO(PORT, PIN);
			_delay_ns(ON_LO);
		} else {
			SET_BIT_HI(PORT, PIN);
			_delay_ns(OFF_HI);
			SET_BIT_LO(PORT, PIN);
			_delay_ns(OFF_LO);
		}
		r <<= 1;
	}

	// Blue
	for (uint8_t bit = 0; bit < 8; bit++) {
		if (b & 0x80) {
			SET_BIT_HI(PORT, PIN);
			_delay_ns(ON_HI);
			SET_BIT_LO(PORT, PIN);
			_delay_ns(ON_LO);
		} else {
			SET_BIT_HI(PORT, PIN);
			_delay_ns(OFF_HI);
			SET_BIT_LO(PORT, PIN);
			_delay_ns(OFF_LO);
		}
		b <<= 1;
	}

}

int main(int argc, const char *argv[])
{

	// Init system clock, disable WDT...
	clock_prescale_set(clock_div_1);
	MCUSR &= ~(1 << WDRF);
	wdt_disable();
	
	// Configure pin
	SET_BIT_HI(DDR, PIN);
	// Off
	rgb(0, 0, 0);

	for (;;) {
		// Red
		rgb(255, 0, 0);
		_delay_ms(PAUSE);
		// Yellow
		rgb(255, 255, 0);
		_delay_ms(PAUSE);
		// Green
		rgb(0, 255, 0);
		_delay_ms(PAUSE);
		// Cyan
		rgb(0, 255, 255);
		_delay_ms(PAUSE);
		// Blue
		rgb(0, 0, 255);
		_delay_ms(PAUSE);
		// Magenta
		rgb(255, 0, 255);
		_delay_ms(PAUSE);
		// White
		rgb(255, 255, 255);
		_delay_ms(PAUSE);

		// Off
		rgb(0, 0, 0);
		_delay_ms(PAUSE);

		// Red up
		for (int i = 0; i <= 255; i++) {
			rgb(i, 0, 0);
			_delay_ms(DELAY);
		}

		// Red -> yellow	
		for (int i = 0; i <= 255; i++) {
			rgb(255, i, 0);
			_delay_ms(DELAY);
		}
		// Yellow -> green
		for (int i = 0; i <= 255; i++) {
			rgb(255 - i, 255, 0);
			_delay_ms(DELAY);
		}
		// Green -> cyan
		for (int i = 0; i <= 255; i++) {
			rgb(0, 255, i);
			_delay_ms(DELAY);
		}
		// Cyan -> blue
		for (int i = 0; i <= 255; i++) {
			rgb(0, 255 - i, 255);
			_delay_ms(DELAY);
		}
		// Blue -> magenta
		for (int i = 0; i <= 255; i++) {
			rgb(i, 0, 255);
			_delay_ms(DELAY);
		}
		// Magenta -> white
		for (int i = 0; i <= 255; i++) {
			rgb(255, i, 255);
			_delay_ms(DELAY);
		}

		// White -> Off
		for (int i = 0; i <= 255; i++) {
			rgb(255 - i, 255 - i, 255 - i);
			_delay_ms(DELAY);
		}

		_delay_ms(PAUSE);
	}
}

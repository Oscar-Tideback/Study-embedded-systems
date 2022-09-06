#include <avr/io.h>

void led_init(){
	DDRB &= ~(1<<PB3); 																	// Jumper from PB3 (Green led) to PD6, PB3 set as IN so it's not doing damages (Pin-10 Arduino)
	DDRD |= (1<<PD6);																		// New OUT
}
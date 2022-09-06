#include <avr/io.h>
#include <stdbool.h>

void led_init(){
	DDRB &= ~(1<<PB3); 																// Jumper from PB3 (Green LED) to PD4, PB3 set as IN so it's not doing damages (Pin-10 Arduino)
	DDRD |= (1<<PD4);  																// New OUT (Pin-4 Arduino)
	PORTD |= (1<<PD4);  															// Turn LED off from start
}

void led_green(bool on){
	if(on)
		PORTD &= ~(1<<PD4);  														// Turn LED on
	else
		PORTD |= (1<<PD4);   														// Turn LED off
}

void led_green_on(){
	PORTD |= (1<<PD4);  															// Turn LED off
	PORTD ^= (1<<PD4);																// Toggle off to on
}

void toggle_led(){
	PORTD ^= (1<<PD4); 																// Toggle LED
}
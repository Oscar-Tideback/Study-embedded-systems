#include <avr/io.h>
#include "led.h"
#include "timer.h"

#define clear_flag(reg, bit) (reg = reg | (1 << bit))

int main (void) {
	int i = 0;
	led_init();
	timer0_init();

	while (1) {
		loop_until_bit_is_set(TIFR0, OCF0A);									// Wait for OCF0A flag to be set
		i++;
		if(i > 10){ 																					// Flag has to be set 10 times before toggle LED
			toggle_led();
			i = 0;
		}
		clear_flag(TIFR0, OCF0A);															// Clear OCF0A flag for next turn
	  reg = | (1 << bit))
	}
	return 0;
}
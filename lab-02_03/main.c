#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "timer.h"

#define clear_flag(reg, bit) (reg = reg | (1 << bit))
#define check_bit(reg, bit) (reg = reg & (1 << bit))

uint8_t fade_value = 0;
bool increase = true;

uint8_t simple_ramp(void){
	if(fade_value == 255){
     increase = false;
  }
	else if(fade_value == 0){
    increase = true;
  }

	if(increase){
    return fade_value++;
  }
  else{
    return fade_value--;
  }
}

int main (void){
	timer_init();
	led_init();
  while (1) {
    loop_until_bit_is_set(TIFR2, OCF2A);                    // Wait to OCF2A flag to be set "timer2"
    OCR0A = simple_ramp();                                  // Set new duty cycle for OCR0A "timer0"
    clear_flag(TIFR2, OCF2A);                               // Clear OCF2A flag for next turn "timer2"
  }
  return 0;
}
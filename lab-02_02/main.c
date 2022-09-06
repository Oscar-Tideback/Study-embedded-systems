#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "timer.h"

void main (void) {
	timer0_init();
	led_init();

  while (1) {
    OCR0A = 225;
    _delay_ms(500);
    OCR0A = 205;
    _delay_ms(500);
    OCR0A = 155;
    _delay_ms(500);
    OCR0A = 105;
    _delay_ms(500);
    OCR0A = 55;
    _delay_ms(500);
  }
  return;
}

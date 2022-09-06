#include <avr/io.h>
#include "timer.h"
#define set_bit(reg, bit) (reg = reg | (1 << bit))
#define clear_bit(reg, bit) (reg = reg & ~(1 << bit))
/*
Settings: Prescale 64 and Fast PWM mode on timer0
          Prescale = 16 000 000 Clock / 64 = 250 000 Hz
          PWM-cycle bottom=0, TOP = 255.
          PWM-frequency = 250 000 / 256 = 976.5625 Hz, "~1000/sec"
--------------------------------------------------------------------------
Clock Select Bit Description:
         |CS02   |CS01   |CS00   | Description
         |   0   |   0   |   0   | No clock source (Timer/Counter stopped)
         |   0   |   0   |   1   | clk(No prescaling)
         |   0   |   1   |   0   | clk/8 (From prescaler)
         |   0   |   1   |   1   | clk/64 (From prescaler)
         |   1   |   0   |   0   | clk/256 (From prescaler)
         |   1   |   0   |   1   | clk/1024 (From prescaler)

Waveform Generation Mode (WGM):
         |WGM02  |WGM01  |WGM00  | Timer/Counter Mode of operation | TOP
         |   0   |   0   |   0   | Normal                          | 0xFF
         |   0   |   1   |   0   | CTC                             | OCRA
         |   0   |   1   |   1   | Fast PWM	                       | 0xFF
--------------------------------------------------------------------------
TCCR0A – Timer/Counter Control Register A
TCCR0A = |COM0A1 |COM0A0 |COM0B1 |COM0B0 |   -   |   -   |WGM01  |WGM00  |
         |       |       |       |       |       |       |   1   |   1   |
TCCR0B – Timer/Counter Control Register B
TCCR0B = |FOC0A  |FOC0B  |   -   |   -   |WGM02  |CS02   |CS01   |CS00   |
         |       |       |       |       |   0   |   0   |   1   |   1   |
Compare Output Mode, Fast PWM Mode
         |COM0A1 |COM0A0 | Description
         |   0   |   0   | Normal port operation, OC0A disconnected
         |   1   |   0   | Clear OC0A on Compare Match, set OC0A at BOTTOM,(non-inverting mode).
OCR0A – Output Compare Register A
*/

void timer0_init() {
	set_bit(TCCR0B, CS00);
	set_bit(TCCR0B, CS01);
	clear_bit(TCCR0B, CS02);

	set_bit(TCCR0A, WGM00);
	set_bit(TCCR0A, WGM01);
	clear_bit(TCCR0B, WGM20);
	
	set_bit(TCCR0A, COM0A1);
	clear_bit(TCCR0A, COM0A0);
	
	// Start PWM-cycle att top 256-1 [0]
	OCR0A = 255;
}

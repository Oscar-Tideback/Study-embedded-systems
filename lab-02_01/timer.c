#include <avr/io.h>
#include "timer.h"

#define set_bit(reg, bit) (reg = reg | (1 << bit))
#define clear_bit(reg, bit) (reg = reg & ~(1 << bit))
/*
Settings: Prescale 1024 and CTC mode on timer0
          Prescale = 16 000 000 Clock / 1024 = 15625 Hz
          TimerPeriod = 10 ms = 0.010 s
          OCR0A = 15625 x 0.010 = 156

OCR0A – Output Compare Register A
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
--------------------------------------------------------------------------
TCCR0A – Timer/Counter Control Register A
TCCR0A = |COM0A1 |COM0A0 |COM0B1 |COM0B0 |   -   |   -   |WGM01  |WGM00  |
         |       |       |       |       |       |       |   1   |   0   |
TCCR0B – Timer/Counter Control Register B
TCCR0B = |FOC0A  |FOC0B  |   -   |   -   |WGM02  |CS02   |CS01   |CS00   |
         |       |       |       |       |   0   |   1   |       |   1   |
*/

void timer0_init() {
	set_bit(TCCR0B, CS00);
	set_bit(TCCR0B, CS02);

	clear_bit(TCCR0A, WGM00);
	set_bit(TCCR0A, WGM01);
	clear_bit(TCCR0B, WGM02);

	// 16000000/1024 = 15625/156 = 100.16Hz = 10ms(p)
	OCR0A = 156;
	}
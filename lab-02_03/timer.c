#include <avr/io.h>
#include "timer.h"
#define set_bit(reg, bit) (reg = reg | (1 << bit))
#define clear_bit(reg, bit) (reg = reg & ~(1 << bit))

/* 	Settings: timer0, prescale 64 and Fast PWM Mode:
         Prescal = 16 000 000 Clock / 64 = 250 000 Hz
         PWM-cycle bottom=0, TOP = 255.
         PWM-frequency = 250 000 / 256 = 976.5625 Hz, "~1000/sec"

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
         |   0   |   1   |   1   | Fast PWM                        | 0xFF
--------------------------------------------------------------------------
TCCR0A   Timer/Counter Control Register A
TCCR0A = |COM0A1 |COM0A0 |COM0B1 |COM0B0 |   -   |   -   |WGM01  |WGM00  |
         |       |       |       |       |       |       |  1        1   |
TCCR0B   Timer/Counter Control Register B
TCCR0B = |FOC0A  |FOC0B  |   -   |   -   |WGM02  |CS02   |CS01   |CS00   |
         |       |       |       |       |   0   |   0...|   1...|   1   |
Compare Output Mode, Fast PWM Mode
         |COM0A1 |COM0A0 | Description
         |   0   |   0   | Normal port operation, OC0A disconnected
         |   1   |   0   | Clear OC0A on Compare Match, set OC0A at BOTTOM,(non-inverting mode).
--------------------------------------------------------------------------
--------------------------------------------------------------------------
         Settings: timer2, prescale 1024 and CTC mode:
         Prescal = 16 000 000 Clock / 1024 = 15625 Hz
         TimerPeriod = 16 ms = 0.016 s
         OCR2A = 15625 x 0.016 = 250 - 1 (249)

OCR0A   Output Compare Register A

Clock Select Bit Description:
         |CS22   |CS21   |CS20   | Description
         |   0   |   0   |   0   | No clock source (Timer/Counter stopped)
         |   0   |   0   |   1   | clk(No prescaling)
         |   0   |   1   |   0   | clk/8 (From prescaler)
         |   0   |   1   |   1   | clk/32 (From prescaler)
	       |   1   |   0   |   0   | clk/64 (From prescaler)
         |   1   |   0   |   1   | clk/128 (From prescaler)
         |   1   |   1   |   0   | clk/256 (From prescaler)
         |   1   |   1   |   1   | clk/1024 (From prescaler)

Waveform Generation Mode (WGM):
         |WGM22  |WGM21  |WGM20  | Timer/Counter Mode of operation | TOP
         |   0   |   0   |   0   | Normal                          | 0xFF
         |   0   |   1   |   0   | CTC                             | OCRA
--------------------------------------------------------------------------
TCCR2A   Timer/Counter Control Register A
TCCR2A = |COM2A1 |COM2A0 |COM2B1 |COM2B0 |   -   |   -   |WGM21  |WGM20  |
         |       |       |       |       |       |       |   1   |   0   |
TCCR2B   Timer/Counter Control Register B
TCCR2B = |FOC2A  |FOC2B  |   -   |   -   |WGM02  |CS22   |CS21   |CS20   |
         |       |       |       |       |   0   |   1   |   1   |   1   |
*/
void timer_init() {
	// Timer0	
	set_bit(TCCR0A, WGM00);
	set_bit(TCCR0A, WGM01);
	//clear_bit(TCCR0B, WGM02);
	
	//clear_bit(TCCR0A, COM0A0);
	set_bit(TCCR0A, COM0A1);

	set_bit(TCCR0B, CS00);
	set_bit(TCCR0B, CS01);
	//clear_bit(TCCR0B, CS02);

	// Timer2
	// Match flag OCF2A is set when timer matches OCR2A.
	// 16000000/1024 x 0.016 = 250-1, [0]
	OCR2A = 249; 
	
	//clear_bit(TCCR2A, WGM20);
	set_bit(TCCR2A, WGM21);
	//clear_bit(TCCR2B, WGM22);

	set_bit(TCCR2B, CS20);
	set_bit(TCCR2B, CS21);
	set_bit(TCCR2B, CS22);
}



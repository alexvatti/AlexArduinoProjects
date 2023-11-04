/*
 * QUTy-timer-pwm.c
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*
   f1  = 2150 Hz @3.3MHz
   f2  = 4070 Hz @3.3MHz

   t1  = 330 ms
   t2  = 660 ms
*/
volatile uint8_t state = 0;

void my_delay_ms(int ms)
{
	while (ms > 0)
	{
		_delay_ms(1);
		--ms;
	}
}

// Function to update timer parameters and delay
void update_timer_duration_delay(uint16_t duration, uint16_t dutycycle, uint16_t delay_ms)
{
	TCA0.SINGLE.PERBUF = duration;   // update duration period of PWM
	TCA0.SINGLE.CMP0BUF = dutycycle; // update duty cycle of PWM
	my_delay_ms(delay_ms); // set delay in ms
}

ISR(TCA0_OVF_vect)
{
	// Toggle state and update timer parameters and delay accordingly
	if (state == 0) {
		update_timer_duration_delay(818, 410, 660);
		state = 1;
		} else {
		update_timer_duration_delay(1550, 775, 330);
		state = 0;
	}
	// Clear the overflow interrupt flag
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

void timer_pwm_init() {
	
	cli(); // Disable global interrupts during initialization
	
	PORTB.DIR |= PIN0_bm; // Configure PB0 as output
	
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc; // set single slope PWM mode
	TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP0EN_bm; // Configure timer: enable compare channel 0,
	
	TCA0.SINGLE.CMP0 = 775; // Set initial dutycycle and
	TCA0.SINGLE.PER = 1550; // Set initial time duration values
	
	TCA0.SINGLE.INTCTRL |= TCA_SINGLE_OVF_bm; // Enable overflow interrupt
	
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm; // Enable timer: no prescaler, enable timer
	
	sei(); // Enable global interrupts
}

int main(void)
{
	timer_pwm_init();
    /* Replace with your application code */
    while (1) 
    {
    }
}

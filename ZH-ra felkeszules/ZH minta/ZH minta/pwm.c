#include <avr/io.h>
#include "pwm.h"
void PWM_init(void)
{
	// kitostesi tenyezo [0;100]
	//Fast PWM mode ||WGM01:0 = 3
	//f(PWM)=f_clk/N.256
	//Phase Correct PWM mode ||WGM01:0 = 1)
	//f(PWM)=f_clk/N.510
	//N: eloosztas
	//256: 8 bites regiszter
	
	DDRB=0xF0;
	TCCR0=((1<<WGM00)|(0<<WGM01)|(0<<COM00)|(1<<COM01)|(0<<CS00)|(1<<CS01)|(1<<CS02));
	
	PORTB|=(1<<PB5);
	
	// 	PB7 	OC2/OC1C(1) (Output Compare and PWM Output for Timer/Counter2 or Output
	// 			Compare and PWM Output C for Timer/Counter1)
	// 	PB6		OC1B (Output Compare and PWM Output B for Timer/Counter1)
	// 	PB5		OC1A (Output Compare and PWM Output A for Timer/Counter1)
	// 	PB4		OC0 (Output Compare and PWM Output for Timer/Counter0)
}


void PWM_set_kitoltes(uint8_t kitoltes100)
{
	uint8_t kitoltes255=kitoltes100*(255/100);
	OCR0=kitoltes255;//kis tau
}
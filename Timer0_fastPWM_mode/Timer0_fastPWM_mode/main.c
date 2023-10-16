// Timer0_fastPWM_mode
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

void Timer0_init();
void led_init();
void led_put(uint8_t led);



int main(void)
{
	led_init();
	Timer0_init();
	/* Replace with your application code */
	uint8_t tau=0;
	while (1)
	{
		_delay_ms(200);
		tau++;
		OCR0=tau;
	}
}


void Timer0_init()
{
	const uint8_t mode_nor=(0<<WGM00)|(0<<WGM01);
	const uint8_t mode_pwm=(0<<WGM00)|(1<<WGM01);
	const uint8_t mode_ctc=(1<<WGM00)|(0<<WGM01);
	const uint8_t mode_fpwm=(1<<WGM00)|(1<<WGM01);
	
	const uint8_t pres_0=(0<<CS02)|(0<<CS01)|(0<<CS00);
	const uint8_t pres_1=(0<<CS02)|(0<<CS01)|(1<<CS00);
	const uint8_t pres_8=(0<<CS02)|(1<<CS01)|(0<<CS00);
	const uint8_t pres_32=(0<<CS02)|(1<<CS01)|(1<<CS00);
	const uint8_t pres_64=(1<<CS02)|(0<<CS01)|(0<<CS00);
	const uint8_t pres_128=(1<<CS02)|(0<<CS01)|(1<<CS00);
	const uint8_t pres_256=(1<<CS02)|(1<<CS01)|(0<<CS00);
	const uint8_t pres_1024=(1<<CS02)|(1<<CS01)|(1<<CS00);
	//set mode for timer 0
	
	TCCR0|=(0<<FOC0)|(1<<COM01)|(0<<COM00)|pres_64|mode_fpwm;
	
	OCR0=254;
	
	
}


void led_init(){
	DDRB=0xF0;
	DDRD=0xF0;
}

void led_put(uint8_t led){
	PORTB=led << 4;
	PORTD=led;
}

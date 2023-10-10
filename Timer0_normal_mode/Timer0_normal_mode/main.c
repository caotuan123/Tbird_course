#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void Timer0_init();
void init_interrupt_timer0_nor();
void init_interrupt_timer0_ctc();
void led_init();
void led_put(uint8_t led);

uint8_t current_led_state=0x00;
unsigned int counter=0;



int main(void)
{
	led_init();
	Timer0_init();
	/* Replace with your application code */
	while (1)
	{
	}
}
ISR(TIMER0_OVF_vect){
	
	TCNT0=131;
	counter+=1;
	if(counter==1000){
		counter=0;
		current_led_state=current_led_state^0x0F;
		//Toggle LED
		led_put(current_led_state);
	}
}


//dem 1 giay
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
	
	
	TCCR0|=(0<<FOC0)|(0<<COM01)|(0<<COM00)|pres_128|mode_nor;
	
	TCNT0=131;
	// set interrupt
	init_interrupt_timer0_nor();
	
}

void init_interrupt_timer0_nor(){
	TIMSK=0x01;
	sei();
}

void led_init(){
	DDRB=0xF0;
	DDRD=0xF0;
}

void led_put(uint8_t led){
	PORTB=led << 4;
	PORTD=led;
}

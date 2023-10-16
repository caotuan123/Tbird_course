#define  F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#define DDR_RGB_RED DDRC
#define PORT_RGB_RED PORTC
#define PIN_RGB_RED PC7

#define DDR_RGB_GREEN DDRE
#define PORT_RGB_GREEN PORTE
#define PIN_RGB_GREEN PE3

#define DDR_RGB_BLUE DDRE
#define PORT_RGB_BLUE PORTE
#define PIN_RGB_BLUE PE2

void Timer0_init();
void init_interrupt_timer0_nor();
void init_interrupt_timer0_ctc();
void led_init();
void rgb_init();
void led_put(uint8_t led);

uint8_t current_led_state=0x00;
uint8_t counter=0;// step number

uint8_t tau=0;

int main(void)
{
	led_init();
	//Timer0_init();
	/* Replace with your application code */
	rgb_init();
	PORT_RGB_BLUE|=(1<<PIN_RGB_BLUE);
	led_put(PINE);
	while (1)
	{
		_delay_ms(10);
		tau++;
		if(tau==100){
			tau=0;
		}
	}
}

//1 ms
ISR(TIMER0_COMP_vect){
	
	counter+=1;
	if(counter==100-1){
		counter=0;
	}
	
	if(counter>tau){
		led_put(0x00);
	}
	else
	{
		led_put(0x80);
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
	
	TCCR0|=(0<<FOC0)|(0<<COM01)|(0<<COM00)|pres_1|mode_ctc;
	
	OCR0=124;
	
	// set interrupt
	init_interrupt_timer0_ctc();
	
}

void init_interrupt_timer0_ctc(){
	TIMSK=0x02;
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

void rgb_init(){
	DDR_RGB_BLUE|=(1<<PIN_RGB_BLUE);
	DDR_RGB_GREEN|=(1<<PIN_RGB_GREEN);
	DDR_RGB_RED|=(1<<PIN_RGB_RED);
}
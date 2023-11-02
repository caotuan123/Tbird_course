#include <avr/io.h>
#include <avr/interrupt.h>
#include "matrix.h"
#include "lcd.h"


void sevseg_out(uint8_t sel, uint8_t data);

uint8_t sevseg_data[4]={0};

void insert_arr_at_tail(uint8_t input){
	for(int i=3;i>0;i--){
		sevseg_data[i]=sevseg_data[i-1];
	}
	sevseg_data[0]=input;
}
ISR(TIMER0_COMP_vect){
	static uint8_t pos=0;
	if(pos==3)
		pos=0;
	else
		pos++;
	sevseg_out(pos,sevseg_data[pos]);
}

void init_interrupt_timer0_ctc(){
	TIMSK=0x02;
	sei();
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
	
	TCCR0|=(0<<FOC0)|(0<<COM01)|(0<<COM00)|pres_8|mode_ctc;
	
	OCR0=200;
	
	// set interrupt
	init_interrupt_timer0_ctc();
	
}



void led_init(){
	DDRB=0xF0;
	DDRD=0xF0;
}

void led_put(uint8_t led){
	PORTB=led << 4;
	PORTD=led;
}
void sevseg_out(uint8_t sel, uint8_t data)
{
	PORTA=1<<7|sel<<4|data;
}
void port_init()
{
	DDRA=0xFF;
	DDRB=0xF0;
	DDRD=0xF0;

}
int main(void)
{
	matrix_init();
	led_init();
	lcd_init();
	port_init();
	Timer0_init();
	uint8_t counter=0;
    /* Replace with your application code */
    while (1) 
    {	
		uint8_t cur_matrix= matrix_get();
		if(cur_matrix!=0xff){
			insert_arr_at_tail(cur_matrix-'0');
			
		}
		
    }
}


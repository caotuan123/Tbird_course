#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "USART.h"
#include "led.h"
#include "RS_485_fifo.h"

#include "timer.h"
uint8_t n_rider[6]={0x18,0x24,0x42,0x81,0x42,0x24};
uint8_t nr_counter=0;
uint8_t timer_counter=0;
uint8_t led_test=0x0f;
ISR(TIMER1_COMPA_vect){
	
	timer_counter=(timer_counter+1)%10;

	if (timer_counter==9)
	{
		nr_counter=(nr_counter+1)%6;
		
		fifo_send(0x3F,0x10,n_rider[nr_counter],n_rider[nr_counter]);
	}
	
		
	
}
ISR(USART1_TX_vect)
{
	led_test^=0xFF;
	led_out(led_test);
}
int main(void)
{
	timer1_CTCmode_init(64,6250);
	sei();
	rs485_init();
	Drive_en();
	USART1_Init(8);
	USART0_Init(8);
	RGB_led_off();
	led_init();
	USART1_txint_on();

    while (1) 
    {
		
	}

}

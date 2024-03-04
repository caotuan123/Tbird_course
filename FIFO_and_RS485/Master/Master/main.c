#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#include "USART.h"
#include "led.h"
#include "RS_485_fifo.h"
#include "timer.h"


struct command
{
	uint8_t id;
	uint8_t cmd;
	uint8_t data1;
	uint8_t data2;
	};

uint8_t n_rider[6]={0x3C,0x66,0xC3,0x66,0x3C,0x66};


uint8_t rs_counter=0; 
uint8_t timer_counter=0;
uint8_t rs_stage;
uint8_t rs_led=0;
ISR(TIMER1_COMPA_vect){
	
	timer_counter=(timer_counter+1)%10;
	if(timer_counter==9)
	{
		
		rs_counter =(rs_counter+1)%31;
		if(rs_counter>=0 && rs_counter<=11)
			rs_stage=1;
		else
		if(rs_counter==12)
			rs_stage=2;
		else
		if (rs_counter>=13 && rs_counter<=20)
			rs_stage=3;
		else
		if(rs_counter>=21 && rs_counter<=28)
			rs_stage=4;
		else
		if(rs_counter==29)
			rs_stage=5;
		else 
		if(rs_counter==30)
			rs_stage=6;
		
		switch(rs_stage)
		{
			case 1:
				fifo_send(0x3F,0x10,n_rider[rs_counter%6],0);
				break;
			case 2:
				fifo_send(EVERYBODY,0x11,0,0);
				break;
			case 3:
				if(rs_counter==13) rs_led=0;
				fifo_send(EVERYBODY,0x12,0,rs_led);
				rs_led++;
				break;
			case 4:
				if(rs_counter==21) rs_led=0;
				fifo_send(0x3F,0x13,rs_led,0);
				rs_led++;
				break;
			case 5:
				fifo_send(EVERYBODY,0x14,56,78);
				break;
			case 6:
				fifo_send(EVERYBODY,0x14,98,12);
				break;
				
		
		}
		

	
		
	}
}
void USART1_txint_on()
{
	UCSR1B|=1<<TXCIE1;
}

int main(void)
{
	timer1_CTCmode_init(64,6250);
	sei();
	USART1_Init(8);
	rs485_init();
	Drive_en();
	//USART1_txint_on;
	
	led_init();
    while (1) 
    {
    }
}


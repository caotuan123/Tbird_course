#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "USART.h"
#include "led.h"
#include "RS_485_fifo.h"
#include "timer.h"
#include "sevseg.h"
#include "button.h"


void SEVENSEG(uint8_t data1);

uint8_t receiving_stage=0;
uint8_t is_start=0;

ISR(USART1_RX_vect)
{
	led_out(0xFF);
	unsigned char k =UDR1;
	if(is_start)
	{
		receiving_stage++;
		switch(receiving_stage)
		{
			case 1:
			fifo_tmp1_id=k;
			case 2:
			fifo_tmp1_cmd=k;
			break;
			case 3:
			fifo_tmp1_data1=k;
			break;
			case 4:
			fifo_tmp1_data2=k;
			break;
			default: break;
		}
	}
	
	if(k==RS_START && is_start==0)
	{
		is_start=1;
	}
	else if (k==RS_STOP&& is_start==1)
	{
		is_start=0;
		receiving_stage=0;
		if(fifo_tmp1_id==EVERYBODY)
		fifo_write(fifo_tmp1_cmd, fifo_tmp1_data1, fifo_tmp1_data2);
	}
}
ISR(TIMER0_COMP_vect)
{
	sevseg_put4digit();
}

int main(void)
{
	sei();
	timer0_CTCmode_init(64,50);
	USART1_Init(8);
	rs485_init();
	sevseg_init();
	led_init();
	//Receive_en();
	USART1_int_on();
	Drive_en();
	
	button_init();
	//led_out(0x0F);
	uint8_t but;
    while (1) 
    {
		but=button_get();
		if(but==1)
		{
			fifo_send(EVERYBODY,RS_TOKEN,0x01,0);
			_delay_ms(100);
			Receive_en();
		}
		//========================================================
		if(!Is_fifo_empty)
		{
			fifo_read(&fifo_tmp2_cmd,&fifo_tmp2_data1,&fifo_tmp2_data2);
			if(fifo_tmp2_cmd==RS_TOKEN)
			{
				Drive_en();
				SEVENSEG(fifo_tmp2_data1);
				_delay_ms(250);
				fifo_send(EVERYBODY,RS_TOKEN,fifo_tmp2_data1+1,0);
				_delay_ms(100);
				Receive_en();
				
			}
		}
    }
}

void SEVENSEG(uint8_t data1)
{
	
	sevseg_num[1]=data1/10;
	sevseg_num[0]=data1%10;
	
}
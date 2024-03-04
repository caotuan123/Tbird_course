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
#include "sevseg.h"
#include "timer.h"


void LED_out(uint8_t led);
void LED_all_off(void);
void LED_on(uint8_t led);
void LED_off(uint8_t led);
void SEVENSEG(uint8_t data1, uint8_t data2);


uint8_t receiving_stage=0;
uint8_t is_start=0;

ISR(USART0_RX_vect)
{
	unsigned char k =UDR1;
	//sevseg_num[0]=5;
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
			if(fifo_tmp1_id==EVERYBODY||fifo_tmp1_id==SLAVE10_ID)
			fifo_write(fifo_tmp1_cmd, fifo_tmp1_data1, fifo_tmp1_data2);
		}
}

ISR(TIMER1_COMPA_vect){
	sevseg_put4digit();	
}
int main(void)
{
	timer1_CTCmode_init(64,255);
	sei();
	sevseg_init();
	led_init();
	
	rs485_init();
	Receive_en();

	USART0_Init(8);
	USART1_Init(8);
	
	USART1_int_on();//USART RX interrupt on
	//sevseg_num[3]=1;


	

    while (1) 
    {
			if(!Is_fifo_empty) 
			{
				fifo_read(&fifo_tmp2_cmd,&fifo_tmp2_data1,&fifo_tmp2_data2);
				switch(fifo_tmp2_cmd)
				{
					case 0x10:
						LED_out(fifo_tmp2_data1);
						break;
					case 0x11:
						LED_all_off();
						break;
					case 0x12:
						LED_on(fifo_tmp2_data1);
						break;
					case 0x13:
						LED_off(fifo_tmp2_data2);
						break;
					case 0x14:
						SEVENSEG(fifo_tmp2_data1, fifo_tmp2_data2);					
						break;
				}
			}
		
		
	}

}
void LED_out(uint8_t led)
{
	PORTB=led<<4; //led also 4 bit--> 8 port felso 4bit
	PORTD=led;
}

void LED_all_off(void)
{
	LED_out(0);
}
void LED_on(uint8_t led)
{
	uint8_t led_n=0x01<<led;
	PORTB|=led_n<<4; //led also 4 bit--> 8 port felso 4bit
	PORTD|=led_n;
}

void LED_off(uint8_t led)
{
	uint8_t led_f=0x01<<led;
	led_f= ~led_f;
	PORTB &=led_f<<4; //led also 4 bit--> 8 port felso 4bit
	PORTD &=led_f;
	
}

void SEVENSEG(uint8_t data1, uint8_t data2)
{
	sevseg_num[3]=data1/10;
	sevseg_num[2]=data1%10;
	sevseg_num[1]=data2/10;
	sevseg_num[0]=data2%10;
	
}
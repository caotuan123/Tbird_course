#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "led.h"
int main(void)
{
	USART0_Init(103);
	USART0_Transmit('a');
	USART1_Init(103);
	USART1_textsend("XIn chao moi nguoi");
	led_init();
	RGBled_init();
	
	
    /* Replace with your application code */
    while (1) 
    {
		char get=USART0_Receive();
		RGBled_out(get);
    }
}


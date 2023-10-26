#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "button.h"

#define BUT_1 1<<PING0
#define BUT_2 1<<PING1
#define BUT_3 1<<PING2
#define BUT_4 1<<PING3
#define BUT_5 1<<PING4
#define BUT_PIN PING
void led_init(){
	DDRB=0xF0;
	DDRD=0xF0;
}

void led_put(uint8_t led){
	PORTB=led << 4;
	PORTD=led;
}



int main(void)
{
	uint8_t button_state;
	uint8_t counter=0;
	
    led_init();
	button_init();
	
	
	

    while (1) 
    {
		
		button_state=button_get();
		_delay_ms(10);
		switch (button_state)
		{
			case 1:
				counter+=1;
				break;
			case 2:
				counter+=2;
				break;
			
			case 3:
				counter+=3;
				break;
			
			case 4:
				counter+=4;
				break;
			
			case 5:
				counter+=5;
				break;
			
			default:
				break;
		}
		led_put(counter);
		
    }
}

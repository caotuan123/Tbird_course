# include <avr/io.h>
# include "led.h"
# include "common.h"
void led_init()
{
	DDRB=0xF0;
	DDRD=0xF0;
}

void led_out(uint8_t led)
{

	PORTB=led<<4; //led also 4 bit--> 8 port felso 4bit
	PORTD=led;

}
void RGBled_init(void)
{
	DDRE|=0x0C;
	DDRC|=0x80;
}

void RGBled_out(char RGB)
{
	if(RGB=='R')	PORTC|=0x80;//R
	else if(RGB=='G')PORTE|=0x08;//G
	else if(RGB=='B')PORTE|=0x04;//B
}
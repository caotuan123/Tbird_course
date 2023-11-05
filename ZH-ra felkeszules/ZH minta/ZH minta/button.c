#define F_CPU 8000000
#include <avr/io.h>
#include "button.h"
#include <util/delay.h>
 uint8_t old_but;
void button_init(void)
{
	DDRG&=~(0x1F);
}

uint8_t button_get(void)
{
	// returns 0 if is not pressed
	// returns 1 if 1st button pressed
	uint8_t but=0;
	uint8_t val=PING&0x1F;
	
	if(val)
	{
		switch (val)
		{
		case 0x01 : 
			but=1;
			break;
		case 0x02 :
			but=2;
			break;
		case 0x04 :
			but=3;
			break;
		case 0x08 :
			but=4;
			break;
		case 0x10 :
			but=5;
			break;
		default: break;
		
		}
	}
	
	if(but!=old_but)
	{
		old_but=but;
		return but;
	}
	else
	
	return 0;	
}
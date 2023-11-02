#define F_CPU 8000000
#include "matrix.h"
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

uint8_t matrix_old_key=0xFF;
void  matrix_init(void)
{
	DDRC |= 0x78;//0b 0111 1000
}

uint8_t  matrix_get(void)
{
	uint8_t key=0;
	uint8_t olvas;

	char  matrix_map[]={'*','0','#',
						'1','2','3',
						'4','5','6',
						'7','8','9',0xFF};
						
	for(uint8_t matrix_row=0x08;matrix_row<=0x40;matrix_row<<=1)
	{

		PORTC=matrix_row;
		olvas=PINC&0x07;
		_delay_ms(5);
		if(olvas==0b110)
			break;
			key++;

		if(olvas==0b101)
		break;
			key++;
			
		if(olvas==0b011)
		break;
			key++;
	}
	
	if(key!=matrix_old_key)
	{
		matrix_old_key=key;
		return matrix_map[key];
	}
	else
	return matrix_map[12];
}
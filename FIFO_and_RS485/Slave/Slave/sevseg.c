#include <avr/io.h>
#include <inttypes.h>
#include "sevseg.h"


uint8_t sevseg_num[4]={0};
uint8_t sevseg_j=0;
void sevseg_init()
{
	DDRA = 0xFF;
}
void sevseg_put1digit(uint8_t num,uint8_t digit_pos)
{
	PORTA=0x80 | digit_pos<<4 | num;
}
void sevseg_put4digit()
{
	sevseg_j=(sevseg_j+1)%4;
	sevseg_put1digit(sevseg_num[sevseg_j],sevseg_j);
}


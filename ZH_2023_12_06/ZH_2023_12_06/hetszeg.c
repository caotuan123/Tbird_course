/*
 * hetszeg.c
 *
 * Created: 08/12/2023 7:01:32 SA
 *  Author: CaoAnhTuan
 */
#include "hetszeg.h"
#include <avr/io.h>
uint8_t sevseg_data[4] = {0};

void sevseg_init()
{
	DDRA = 0xFF;
}
void sevseg_out(uint8_t sel, uint8_t data)
{
	PORTA = 1 << 7 | sel << 4 | data;
}
void sevseg_put_buff(unsigned num, unsigned int posi)
{
	if (posi > 3)
		posi = 3;
	if (num > 9)
		num = 9;
	sevseg_data[posi] = num;
}
void sevseg_run()
{
	static uint8_t pos = 0;
	if (pos == 3)
		pos = 0;
	else
		pos++;
	sevseg_out(pos, sevseg_data[pos]);
}

void sevseg_print_num_uint(unsigned int num)
{
	if (num > 9999)
		num = 9999;
	sevseg_data[3] = (num / 1000) % 10;
	sevseg_data[2] = (num / 100) % 10;
	sevseg_data[1] = (num / 10) % 10;
	sevseg_data[0] = (num / 1) % 10;
}
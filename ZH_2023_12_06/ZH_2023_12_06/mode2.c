#include <stdlib.h>

#include "mode2.h"
#include "timer.h"
#include "lcd.h"
#include "matrix.h"
#include "hetszeg.h"

int mode2_num_start;
int mode2_num_stop;
uint8_t mode_2_is_first_run = 0;

uint8_t mode2_get_number(int *result)
{
	static int counter;
	static char tmp[5] = {0};
	char c = matrix_get();
	if (c != 0xff && c != '#')
	{
		lcd_data(c);
		tmp[counter] = c;
		if (counter == 5 - 1 || c == '*')
		{
			tmp[counter] = 0;
			*result = atoi(tmp);
			counter = 0;
			return 1;
		}
		else
		{
			counter++;
		}
	}
	return 0;
}

void mode2_run()
{
	static unsigned int counter;

	if (mode_2_is_first_run == 1)
	{
		mode_2_is_first_run = 0;
		counter = mode2_num_start;
	}

	sevseg_print_num_uint(counter);

	if (counter == mode2_num_stop)
	{
		counter = mode2_num_start;
	}
	else
		counter++;
}

void mode2_start_num_count()
{
	timer1_CTCmode_init(128, 25000);
}
void mode2_start()
{

	uint8_t result;
getnumer:
	lcd_cur_posi(LCD_ROW_1, 1);
	lcd_write_string("           "); // delete row
	lcd_cur_posi(LCD_ROW_1, 1);
	lcd_write_string("Start:");
	while (1)
	{
		result = mode2_get_number(&mode2_num_start);
		if (result == 1)
			break;
	}
	lcd_cur_posi(LCD_ROW_1, 1);
	lcd_write_string("           "); // delete row
	lcd_cur_posi(LCD_ROW_1, 1);
	lcd_write_string("Stop:");

	while (1)
	{
		result = mode2_get_number(&mode2_num_stop);
		if (result == 1)
			break;
	}

	if (mode2_num_start >= mode2_num_stop)
	{
		goto getnumer;
	}
	// start_timer
	lcd_cur_posi(LCD_ROW_1, 1);
	lcd_write_string("             ");
	mode_2_is_first_run = 1;
	timer3_CTCmode_init(256, 30000);
}

void mode2_stop()
{
	timer3_CTCmode_init(0, 0);
	lcd_cur_posi(LCD_ROW_1, 1);
	lcd_write_string("STOP      ");
}
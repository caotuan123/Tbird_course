/*
 * ZH_2023_11_06.c
 *
 * Created: 07/11/2023 7:30:38 CH
 * Author : CaoAnhTuan
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "USART.h"
#include "led.h"
#include "lcd.h"
#include "common.h"
#include "matrix.h"
#include "timer.h"
#include "button.h"
#include "hetszeg.h"
#include "adc.h"
#include "mode1.h"
#include "mode2.h"
#include "mode3.h"
#define ARROW_DIRECT_UP -1
#define ARROW_DIRECT_DOWN 1

void start_handle();
void stop_handle();
void move_arrow(uint8_t direct);
void sevsg_start_display();
uint8_t arrow_pos_current = 0;

// timer0 for sevseg
// timer1 for adc
// timer3 for number counter

int main(void)
{

	led_init();
	matrix_init();
	lcd_init();
	button_init();
	sevseg_init();
	sevsg_start_display();
	lcd_cur_posi(LCD_ROW_0, 0);
	lcd_data('>');
	
	while (1)
	{
		uint8_t but_var = button_get();
		_delay_ms(2);
		switch (but_var)
		{
		case 1:
			move_arrow(ARROW_DIRECT_DOWN);
			break;
		case 2:
			move_arrow(ARROW_DIRECT_UP);
			break;
		case 3: // start mode
			start_handle();
			break;
		case 4: // stop mode
			stop_handle();
			break;
		default:
			break;
		}
	}
}

ISR(TIMER0_COMP_vect)
{
	sevseg_run();
}

ISR(TIMER1_COMPA_vect)
{
	mode1_run();
}

ISR(TIMER3_COMPA_vect)
{
	mode2_run();
}

ISR(USART0_RX_vect)
{
	mode3_run();
}
void sevsg_start_display()
{
	timer0_CTCmode_init(128, 125);
}

void move_arrow(uint8_t direct)
{

	uint8_t arrow_pos_next = (arrow_pos_current + direct) % 4;
	lcd_cur_posi(arrow_pos_current, 0);
	lcd_data(' ');
	lcd_cur_posi(arrow_pos_next, 0);
	lcd_data('>');
	arrow_pos_current = arrow_pos_next;
}

void start_handle()
{
	switch (arrow_pos_current)
	{
	case 0:
		mode1_start();
		break;
	case 1:
		mode2_start();
		break;

	case 2:
		mode3_start();
		break;
	case 3:

		break;

	default:
		break;
	}
}

void stop_handle()
{
	switch (arrow_pos_current)
	{
	case 0:
		mode1_stop();
		break;
	case 1:
		mode2_stop();
		break;
	case 2:
		mode3_stop();
		break;
	case 3:

		break;

	default:
		break;
	}
}

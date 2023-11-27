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
#include "led.h"
#include "lcd.h"
#include "common.h"
#include "matrix.h"
#include "timer.h"
#include "button.h"

# define ARROW_DIRECT_UP -1
# define ARROW_DIRECT_DOWN 1

void start_handle();
void stop_handle();
void move_arrow(uint8_t direct);

void mode1_start();
void mode1_stop();
void mode1_led_run(const uint8_t* states,const int states_len);

void mode2_start();
void mode2_num_count();
uint8_t mode2_get_number(int *result);
void mode2_stop();

 
const int led_states_len= LED_STATES_LEN;
uint8_t led_states[LED_STATES_LEN]=
{
	0b00000001,
	0b00000011,
	0b00000111,
	0b00001111,
	0b00011110,
	0b00111100,
	0b01111000,
	0b11110000,
	0b01111000,
	0b00111100,
	0b00011110,
	0b00001111,
	0b00000111,
	0b00000011,
	0b00000001
};

uint8_t arrow_pos_current=0;
int mode2_num_start;
int mode2_num_stop;
uint8_t mode_2_is_first_run=0;


int main(void)
{
    led_init();
	matrix_init();
	lcd_init();
	button_init();

    while (1) 
    {
		uint8_t but_var = button_get();
		_delay_ms(2);
		switch(but_var){
			case 1:
				move_arrow(ARROW_DIRECT_DOWN);
				break;
			case 2:
				move_arrow(ARROW_DIRECT_UP);
				break;
			case 3://start mode
				start_handle();
				break;
			case 4://stop mode
				stop_handle();
				break;
			default:
				break;
		}
		
	}
	
}


ISR(TIMER0_COMP_vect)
{
	mode2_num_count();
	
}

ISR(TIMER1_COMPA_vect)
{
	mode1_led_run(led_states,led_states_len);
}
void move_arrow(uint8_t direct){
	
	uint8_t arrow_pos_next=(arrow_pos_current+direct)%4;
	lcd_cur_posi(arrow_pos_current,0);
	lcd_data(' ');
	lcd_cur_posi(arrow_pos_next,0);
	lcd_data('>');
	arrow_pos_current=arrow_pos_next;
}

void mode1_start()
{	
	lcd_cur_posi(LCD_ROW_0,1);
	lcd_write_string("Led running");
	timer1_CTCmode_init(256,31249);
	
}

void mode1_stop()
{
	timer1_CTCmode_init(0,0);	
	led_out(0x00);
	lcd_cur_posi(LCD_ROW_0,1);
	lcd_write_string("Led stopped");
}


void mode1_led_run(const uint8_t* states,const int states_len){
	static int counter;
	led_out(states[counter]);
	if(counter==states_len-1)
	{
		counter=0;
	}
	else
	{
		counter++;
	}
}


uint8_t mode2_get_number(int *result){
	static int counter;
	static char tmp[5]={0};
	char c=matrix_get();
	if(c!=0xff && c!='#')
	{
		lcd_data(c);
		tmp[counter]=c;
		if(counter==5-1||c=='*')
		{
			tmp[counter]=0;
			*result = atoi(tmp);
			counter=0;
			return 1;
		}
		else
		{
			counter++;
		}
	}
	return 0;
}
	
void mode2_num_count(){
	static int timer_counter;
	static int counter;
	
	if(mode_2_is_first_run==1)
	{
		mode_2_is_first_run=0;
		counter=mode2_num_stop;
	}
	
	if(timer_counter==200)
	{
		timer_counter=0;
		lcd_cur_posi(LCD_ROW_1,1);
		char buffer[6];
		itoa(counter,buffer,10);
		lcd_write_string(buffer);
			
		if(counter==mode2_num_start)
		{
			counter=mode2_num_stop;
		}
		else
		counter--;
	}
	else
	timer_counter++;
}
void mode2_start_num_count(){
	timer1_CTCmode_init(128, 25000);
}
void mode2_start()
{
	
	uint8_t result;
	getnumer:
		lcd_cur_posi(LCD_ROW_1,1);
		lcd_write_string("           ");//delete row
		lcd_cur_posi(LCD_ROW_1,1);
		lcd_write_string("Start:");		
		while(1)
		{
			result=mode2_get_number(&mode2_num_start);
			if (result==1)
				break;
		}
		lcd_cur_posi(LCD_ROW_1,1);
		lcd_write_string("           ");//delete row
		lcd_cur_posi(LCD_ROW_1,1);
		lcd_write_string("Stop:");

		while(1)
		{
			result=mode2_get_number(&mode2_num_stop);
			if (result==1)
				break;
		}
		
	
	if(mode2_num_start>=mode2_num_stop)
	{
		goto getnumer;
	}
	//start_timer
	lcd_cur_posi(LCD_ROW_1,1);
	lcd_write_string("             ");
	mode_2_is_first_run=1;
	timer0_CTCmode_init(128,125);//2ms

}

void mode2_stop()
{
	timer0_CTCmode_init(0,0);
	lcd_cur_posi(LCD_ROW_1,1);
	lcd_write_string("STOP      ");
	
}
		
void start_handle()
{
	switch(arrow_pos_current){
		case 0:
			mode1_start();
			break;
		case 1:
			mode2_start();
			break;
		case 2:
			//mode3_start();
			break;
		case 3:
			//mode4_start();
			break;
			
		default:
			break;
	}
}

void stop_handle()
{
	switch(arrow_pos_current){
		case 0:
			mode1_stop();
			break;
		case 1:
			mode2_stop();	
			break;
		case 2:
			//mode3_stop();
			break;
		case 3:
			//mode4_stop();
			break;
		
		default:
			break;
	}
}

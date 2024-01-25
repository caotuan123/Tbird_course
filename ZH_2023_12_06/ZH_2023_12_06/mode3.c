/*
 * mode3.c
 *
 * Created: 09/12/2023 9:32:48 CH
 *  Author: CaoAnhTuan
 */ 
#include "USART.h"
#include "lcd.h"

#include "mode3.h"
#include <stdlib.h>
#define USART0_BUFF_LEN 256

unsigned char USART0_buff[USART0_BUFF_LEN];
unsigned int USART0_buff_ptr=0;
int state=0;//0: first num, 1: operator, 2: second num, 4: caculator
int first_num;
int second_num;
char operator;

int caculator(int num1, int num2, const char ope){
	switch (ope)
	{
		case '+':
		return (num1+num2);
		case '-':
		return (num1-num2);
		case 'x':
		return (num1*num2);
		case '/':
		return (num1/num2);
		default:
		return 0;
	}
}

void cmd_handle(){
	int result;
	char buff[10];
	switch(state){
		case 0:
			first_num = atoi((char*)USART0_buff);
			state=1;
			lcd_cur_posi(LCD_ROW_0,5);
			lcd_write_string((char*)USART0_buff);
			break;
		case 1:
			operator = USART0_buff[0];
			lcd_cur_posi(LCD_ROW_1,9);
			lcd_data(operator);
			state=2;
			break;
		case 2:
			second_num = atoi((char*)USART0_buff);
			lcd_cur_posi(LCD_ROW_2,5);
			lcd_write_string((char*)USART0_buff);
			state=3;
			break;
		case 3:
			result=caculator(first_num,second_num,operator);
			itoa(result,buff,10);
			state=0;
			lcd_cur_posi(LCD_ROW_3,2);
			lcd_write_string(buff);
			break;
	}
}

void mode3_run(){
	unsigned char received_data=USART0_Receive();
	USART0_Transmit(received_data);
	if(received_data=='\n' || received_data=='\r'){
		USART0_buff[USART0_buff_ptr]='\0';
		USART0_buff_ptr=0;
		cmd_handle();
	}
	else{
		USART0_buff[USART0_buff_ptr]=received_data;
		USART0_buff_ptr++;
	}
}
void mode3_start(){
	lcd_cur_posi(LCD_ROW_0,1);
	lcd_write_string("op1:");
	lcd_cur_posi(LCD_ROW_1,1);
	lcd_write_string("muvelet:");
	lcd_cur_posi(LCD_ROW_2,1);
	lcd_write_string("op2:");
	lcd_cur_posi(LCD_ROW_3,1);
	lcd_write_string("=");
	USART0_Init(103);
}
void mode3_stop(){
	USART0_textsend("stop\r\n");
	USART0_stop();
}
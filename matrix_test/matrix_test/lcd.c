
#include <inttypes.h>
#include "lcd.h"
#include <avr/io.h>

#define F_CPU 16000000
#include <util/delay.h>


void lcd_clk(void)
{
	//LCD E 0
	//(1<<3)=0b00001000 ~(1<<3)=0b11110111
	LCD_E_PORT &= ~(1<<LCD_E_PIN);		//ne irjak felul semmit
	_delay_ms(2);
	//LCD E 1
	LCD_E_PORT |= (1<<LCD_E_PIN);
	_delay_ms(2);
	//LCD E 0
	LCD_E_PORT &= ~(1<<LCD_E_PIN);
	_delay_ms(2);
}
void lcd_send_cmd(uint8_t cmd)
{
	//R/W: 0(iras)
	LCD_RW_PORT &= ~(1<<LCD_RW_PIN);
	//RS: 0(IR)
	LCD_RS_PORT &= ~(1<<LCD_RS_PIN);
	//Felso 4-bit
	uint8_t data_temp;
	data_temp=PINE;
	LCD_DATA_PORT = (cmd&0xF0);
	//E CLK
	lcd_clk();
	//Also 4-bit
	LCD_DATA_PORT = (cmd&0x0F)<<LCD_DATA_SHIFT;
	//E CLK
	lcd_clk();
	LCD_DATA_PORT=data_temp;
}

void lcd_init(void)
{
	LCD_DATA_DDR|=0xF0;
	LCD_E_DDR|=(1<<LCD_E_PIN);
	LCD_RS_DDR|=(1<<LCD_RS_PIN);
	LCD_RW_DDR|=(1<<LCD_RW_PIN);
	//4 adat vezetekre 2-est kikuldeni
	LCD_DATA_PORT |= 0x20;
	//3x clk
	lcd_clk();
	lcd_clk();
	lcd_clk();
	//3x 0x28 cmd
	lcd_send_cmd(0x28);
	lcd_send_cmd(0x28);
	lcd_send_cmd(0x28);
	//Display ON - Kurzor cuccok
	lcd_send_cmd(0x0C);		//LCD ON, CUR ON, BL ON //sima LCD ON 0x0C
	//LCD CRL
	lcd_send_cmd(LCD_CL_DISPLAY);
	
}

//Data iras
void lcd_data(uint8_t data)
{
	//R/W: 0(iras)
	LCD_RW_PORT &= ~(1<<LCD_RW_PIN);
	//RS: 1(adat)
	LCD_RS_PORT |= (1<<LCD_RS_PIN);
	//Felso 4-bit
	uint8_t data_temp;
	data_temp=PINE;
	LCD_DATA_PORT = (data&0xF0);
	//E CLK
	lcd_clk();
	//Also 4-bit
	LCD_DATA_PORT = (data&0x0F)<<LCD_DATA_SHIFT;
	//E CLK
	lcd_clk();
	LCD_DATA_PORT=data_temp;
}

//LCD CLK - LCD_E 0-1-0 _||_

void lcd_write_string(char *s)
{
	while (*s)
	{
		lcd_data(*s);
		s++;
	}
}
void lcd_cur_posi(uint8_t row, uint8_t colum)
{
	colum>LCD_COL_LAST?colum=LCD_COL_LAST:0;
	uint8_t position[4]={LCD_LINE_0,LCD_LINE_1,LCD_LINE_2,LCD_LINE_3};
	lcd_send_cmd((position[row])+colum);
}

void lcd_cur_blink(){
	lcd_send_cmd(LCD_DISON_CURBLK);
}

void lcd_cur_unblink(){
	lcd_send_cmd(LCD_DIS0N_CUROFF);
}







#include <inttypes.h>
#include "lcd.h"
#include <avr/io.h>

#define F_CPU 8000000
#include <util/delay.h>

//LCD Init - PORT init + config
clocks_digit ora_digit[6]={
	{"H0",0,0},
	{"H1",1,0},
	{"M0",3,0},
	{"M1",4,0},
	{"S0",6,0},
	{"S1",7,0}
};

clocks_num ora_szam[3]={
	{"H",11,11},
	{"M",59,11},
	{"S",59,11}
};

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
	lcd_cmd(0x28);
	lcd_cmd(0x28);
	lcd_cmd(0x28);
	//Display ON - Kurzor cuccok
	lcd_cmd(0x0C);		//LCD ON, CUR ON, BL ON //sima LCD ON 0x0C
	//LCD CRL
	
}
//CMD iras
void lcd_cmd(uint8_t cmd)
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
void lcd_string(char *s)
{
	while (*s)
	{
		lcd_data(*s);
		s++;
	}
}
void lcd_cur_posi(uint8_t row, uint8_t colum)
{
	
	uint8_t position[4]={LCD_LINE_0,LCD_LINE_1,LCD_LINE_2,LCD_LINE_3};
	
	lcd_cmd((position[row])+colum);
}


// Oraval kapcsolatban


void Change_clk_digit_to_num(void)
{
	ora_szam[0].current_val=ora_digit[0].current_val*10+ora_digit[1].current_val;
	ora_szam[1].current_val=ora_digit[2].current_val*10+ora_digit[3].current_val;
	ora_szam[2].current_val=ora_digit[4].current_val*10+ora_digit[5].current_val;
}

void Change_clk_num_to_digit(void)
{
	ora_digit[0].current_val=ora_szam[0].current_val/10;
	ora_digit[1].current_val=ora_szam[0].current_val%10;
	ora_digit[2].current_val=ora_szam[1].current_val/10;
	ora_digit[3].current_val=ora_szam[1].current_val%10;
	ora_digit[4].current_val=ora_szam[2].current_val/10;
	ora_digit[5].current_val=ora_szam[2].current_val%10;
}

uint8_t compare_clk_num_w_max(void)
{
	//return 1 if num< max
	//return 0 if num> max
	int i=0;
	while (i<3)
	{
		if(ora_szam[i].current_val>ora_szam[i].max_val)return 0;
		i++;
	}
	return 1;
}

void lcd_print_time(void)
{
	for(int i=0;i<6;i++)
	{
		lcd_cur_posi(0,ora_digit[i].digit_poz);
		lcd_data(ora_digit[i].current_val+'0');
	}
}

void ora_szamlalo(void)
{
	ora_szam[2].current_val++;
	if(ora_szam[2].current_val==60)
	{
		ora_szam[2].current_val=0;
		ora_szam[1].current_val++;
		if(ora_szam[1].current_val==60)
		{
			ora_szam[1].current_val=0;
			ora_szam[0].current_val++;
			if(ora_szam[0].current_val==12)
			ora_szam[0].current_val=0;
		}
	}
	
}


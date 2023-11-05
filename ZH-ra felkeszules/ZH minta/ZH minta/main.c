
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "timer.h"
#include "button.h"
#include "matrix.h"
#include "led.h"
#include "adc.h"
#include <stdlib.h>
#include <stdio.h>
int timer0_counter=0;

void hetszeg_init(void);
void SEVSEG_put1digit(uint8_t szam,uint8_t digit_pozicio);
void change_szamlalo_digit_to_num();
void change_szamlalo_num_to_digit();
void SEVSEG_put4digit();
uint8_t regi_csilag=0;
uint8_t ujcsilag=0;
uint8_t hetszeg_szam[4]={0};
uint16_t szamlalo=0;
char tmp[100];
uint8_t hetszeg_szam_input[4]={0};
uint16_t szamlalo_input=0;
uint8_t IsStart=0;
uint8_t Is_red_on=0;
uint8_t Is2feladat=0;
uint8_t Is3feladat=0;

int j=0;

int adc_sum=0;

// ISR(TIMER1_COMPA_vect)
// {
// 	adc_counter++;
// 	
// 		adc_sum +=adc_C();
// 	
// 	if(adc_counter==5)
// 	{
// 		adc_sum=0;
// 		adc_sum/=5;
// 		lcd_cur_posi(3,5);
// 		itoa(adc_sum,tmp,10);
// 		lcd_string(tmp);
// 		adc_counter=0;
// 	}
// }
ISR(TIMER0_COMP_vect)
{
	SEVSEG_put4digit();
	timer0_counter++;
	if(timer0_counter%100==0)
		adc_sum+=adc_C();
	
	if(timer0_counter==500)
	{
		if(Is_red_on) PORTC^=0x80;//R
		if(IsStart)	 szamlalo++;
		if(szamlalo==1000)szamlalo=0;
		change_szamlalo_num_to_digit();
		
		timer0_counter=0;
		
		
		adc_sum/=5;
		lcd_cur_posi(3,5);
		itoa(adc_sum,tmp,10);
		lcd_string(tmp);
		adc_sum=0;
	}	
	
}

	int main(void)
{
	RGBled_init();
	adc_init();
    lcd_init();
	matrix_init();
	hetszeg_init();
	lcd_cmd(LCD_CL_DISPLAY);
	lcd_cur_posi(0,0);
	lcd_string("num:");
	lcd_cur_posi(3,0);
	lcd_string("Temp:  C");
	timer0_CTCmode_init(64,250);
	//timer1_CTCmode_init(256,6250);
	uint8_t but,but1;
	char matrix_tmp;
	while (1) 
    {
		
		but=button_get();
		matrix_tmp=matrix_get();
		
		if(but)
		{
			if(but==3)
			{
				IsStart=1;
				lcd_cur_posi(1,0);
				lcd_string("     ");
				lcd_cur_posi(1,0);
				lcd_string("START");
			}
			if(but==4)
			{
				IsStart=0;
				lcd_cur_posi(1,0);
				lcd_string("     ");
				lcd_cur_posi(1,0);
				lcd_string("STOP");
				lcd_cur_posi(1,11);
				lcd_string("   ");
				lcd_cur_posi(1,11);
				itoa(szamlalo,tmp,10);
				lcd_string(tmp);
				
				
			}
			if(but==5)
			{
				szamlalo=0;
				lcd_cur_posi(1,0);
				lcd_string("     ");
				lcd_cur_posi(1,0);
				lcd_string("NULL");
			}
			if(but==1){
				
				lcd_cur_posi(0,4);
				for(int i=4;i>0;i--)
				{
					if(i==1)
					{
						
						while(1)
						{
							but1=button_get();
							if(but1==2)
							{
								szamlalo_input=hetszeg_szam_input[0]+hetszeg_szam_input[1]*10+hetszeg_szam_input[2]*100;
								if(szamlalo_input>=0&&szamlalo_input<=999)
								{
									if(Is2feladat)
									{
										
										if(szamlalo_input==543)
										{
											PORTC&=~0x80;//R
											PORTE&=~0x08;//G
											PORTE&=~0x04;//B
											RGBled_out('G');
										}
										else
										{
											PORTC&=~0x80;//R
											PORTE&=~0x08;//G
											PORTE&=~0x04;//B
											PORTE&=~(0x08);//G
											Is_red_on=1;
											
										}
									}
									lcd_cur_posi(1,0);
									lcd_string("     ");
									lcd_cur_posi(1,0);
									lcd_string("OK");
									szamlalo=szamlalo_input;
									break;
								}
								else
								{
									lcd_cur_posi(1,0);
									lcd_string("     ");
									lcd_cur_posi(1,0);
									lcd_string("ERROR");
									break;
								}
							}
							
						}
					}
					while(i>1)
					{
						matrix_tmp=matrix_get();
						if(matrix_tmp!=0xff)
						{
							hetszeg_szam_input[i-2]=matrix_tmp-'0';
							lcd_data(matrix_tmp);
							break;
						}
					}
					
				}
				

				
				}
		
		
		}
	  if(regi_csilag!=ujcsilag)
	  {
		  lcd_cur_posi(2,0);
		  lcd_string("    ");
		  lcd_cur_posi(2,0);
		  for (int i=0;i<ujcsilag;i++)
		  {
			  lcd_data('*');
		  }
	  }
	  
	  if(szamlalo>=0&&szamlalo<=100)
	  {
		  regi_csilag=ujcsilag;
		  ujcsilag=1;
		  
	  }
	  if(szamlalo>=101&&szamlalo<=250)
	  {
		  regi_csilag=ujcsilag;
		  ujcsilag=2;
	  }
	  if(szamlalo>=251&&szamlalo<=500)
	  {
		 regi_csilag=ujcsilag;
		 ujcsilag=3;
	  }
	  if(szamlalo>=501&&szamlalo<=999)
	  {
		  regi_csilag=ujcsilag;
		  ujcsilag=4;
	  }
	}
	
}

void change_szamlalo_digit_to_num()
{
	szamlalo=hetszeg_szam[0]+hetszeg_szam[1]*10+hetszeg_szam[2]*100;
}

void change_szamlalo_num_to_digit()
{
	hetszeg_szam[0]=szamlalo%10;
	hetszeg_szam[1]=(szamlalo/10)%10;
	hetszeg_szam[2]=(szamlalo/100);
}
void hetszeg_init()
	{
		DDRA = 0xFF;
	}
void SEVSEG_put1digit(uint8_t szam,uint8_t digit_pozicio)
	{
		PORTA=0x80 | digit_pozicio<<4 | szam;
	}
void SEVSEG_put4digit()
	{
		j=(j+1)%4;
		SEVSEG_put1digit(hetszeg_szam[j],j);
	}


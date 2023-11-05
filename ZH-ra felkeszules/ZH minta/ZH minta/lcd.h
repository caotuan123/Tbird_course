
#ifndef LCD_H_
#define LCD_H_

#define LCD_E_DDR		DDRF
#define LCD_E_PORT		PORTF
#define LCD_E_PIN		3
#define LCD_RS_DDR		DDRF
#define LCD_RS_PORT		PORTF
#define LCD_RS_PIN		1
#define LCD_RW_DDR		DDRF
#define LCD_RW_PORT		PORTF
#define LCD_RW_PIN		2
#define LCD_DATA_DDR	DDRE
#define LCD_DATA_PORT	PORTE	//felo 4 bit
#define LCD_DATA_SHIFT		4
//----command
#define LCD_CL_DISPLAY 0x01
#define LCD_4_BIT_1LINE_5X7  0x20
#define LCD_4_BIT_2LINE_5X7  0x28
#define LCD_DISOFF_CUROFF	 0x80
#define LCD_DIS0N_CUROFF  0x0C
#define LCD_DISON_CURBLK	 0x0F//display on cursor blink
#define LCD_LINE_0  0x80
#define LCD_LINE_1  0xC0
#define LCD_LINE_2  0x90
#define LCD_LINE_3  0xD0
//-----------
typedef struct clocks_digits
{
	char name[3];
	uint8_t digit_poz;
	uint8_t current_val;
	
}clocks_digit;

typedef struct clocks_nums
{
	char name[3];
	uint8_t max_val;
	uint8_t current_val;
	
}clocks_num;

extern clocks_num ora_szam[3];
extern clocks_digit ora_digit[6];

//LCD Init - PORT init + config
void lcd_init(void);
//CMD iras
void lcd_cmd(uint8_t cmd);
//Data iras
void lcd_data(uint8_t data);
//LCD CLK - LCD_E 0-1-0 _||_
void lcd_clk(void);
void lcd_string(char *s);
void lcd_cur_posi(uint8_t row, uint8_t colum);//put cursor on position
void lcd_s_stime(uint8_t row,uint8_t colum, char*);//put string in short time
//---oraval kapcsolatos-------------------------------

void Change_clk_digit_to_num(void);
void Change_clk_num_to_digit();
uint8_t compare_clk_num_w_max(void);
void lcd_print_time(void);
void ora_szamlalo(void);


//String
//Pozicionalas
//Egyedi karakter
//Futo szogeg
//Fenyujsag
//LCD MENU

#endif /* LCD_H_ */
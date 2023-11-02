
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
#define LCD_ROW_0  0
#define LCD_ROW_1  1
#define LCD_ROW_2  2
#define LCD_ROW_3  3
#define LCD_COL_FIRST 0
#define LCD_COL_LAST 15
//LCD Init - PORT init + config
void lcd_init(void);
//Data iras

void lcd_data(uint8_t data);
void lcd_write_string(char *s);
void lcd_cur_posi(uint8_t row, uint8_t colum);//put cursor on position
void lcd_cur_blink();
void lcd_cur_unblink();
void lcd_send_cmd(uint8_t);

#endif /* LCD_H_ */
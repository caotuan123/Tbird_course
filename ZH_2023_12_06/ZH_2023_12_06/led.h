#ifndef LED_H_
#define LED_H_
#include <avr/io.h>

void led_init(void);
void led_out(uint8_t led);
void RGBled_init(void);
void RGBled_out(char RGB);
#endif
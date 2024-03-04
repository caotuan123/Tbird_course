#ifndef SEVSEG_H_
#define SEVSEG_H_

extern uint8_t sevseg_num[4];
extern uint8_t sevseg_j;

void sevseg_init();
void sevseg_put1digit(uint8_t num,uint8_t digit_pos);
void sevseg_put4digit();

#endif
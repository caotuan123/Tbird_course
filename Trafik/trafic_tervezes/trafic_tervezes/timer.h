#ifndef TIMER_H_
#define TIMER_H_


typedef struct prescalers
{
	int prescaler_num;
	uint8_t CSn2_val;
	uint8_t CSn1_val;
	uint8_t CSn0_val;
}prescaler;

extern prescaler pres_timer0[8];
extern prescaler pres_timer1_2_3[8];
void timer0_nomalmode_init(int prescaler_num_input, int top_val);
void timer0_CTCmode_init(int prescaler_num_input, int top_val);
void timer1_CTCmode_init(int prescaler_num_input, int top_val);

#endif
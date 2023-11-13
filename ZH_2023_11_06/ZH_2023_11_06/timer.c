#include <inttypes.h>
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

prescaler pres_timer0[8]={
	{0	 ,0	,0	,0},
	{1	 ,0	,0	,1},
	{8	 ,0	,1	,0},
	{32	 ,0	,1	,1},
	{64	 ,1	,0	,0},
	{128 ,1	,0	,1},
	{256 ,1	,1	,0},
	{1024,1	,1	,1}
};

// 	1 1 0 External clock source on Tn pin. Clock on falling edge
// 	1 1 1 External clock source on Tn pin. Clock on rising edge

prescaler pres_timer1_2_3[8]={
	{0	  ,0	,0	,0},
	{1	  ,0	,0	,1},
	{8	  ,0	,1	,0},
	{64	  ,0	,1	,1},
	{256  ,1	,0	,0},
	{1024 ,1	,0	,1},
	{-1   ,1	,1	,0},
	{-2   ,1	,1	,1}
};
void timer0_nomalmode_init(int prescaler_num_input, int top_val)
{
	//if prescaler_num_input == -1 --> STOP timer
	
	int i=0;
	while(i<8)
	{
		if(prescaler_num_input==pres_timer0[i].prescaler_num)break;
		i++;
	}
	
	TCCR0=(pres_timer0[i].CSn2_val<<CS02)|
	(pres_timer0[i].CSn1_val<<CS01)|
	(pres_timer0[i].CSn0_val<<CS00);
	
	TCNT0=top_val;
	TIMSK=(1<<TOIE0); //• Bit 1 – OCIE0 TimerCounter0 Output Compare Match Interrupt Enable
	sei();
}

void timer0_CTCmode_init(int prescaler_num_input, int top_val)
{
	//2 ms /8 MHz/ prescaler 128/ top 125
	//2 ms /8 MHz/ prescaler 64/ top 250
	//if prescaler_num_input == -1 --> STOP timer
	
	int i=0;
	while(i<8)
	{
		if(prescaler_num_input==pres_timer0[i].prescaler_num)break;
		i++;
	}
	
	TCCR0=(pres_timer0[i].CSn2_val<<CS02)|
	(pres_timer0[i].CSn1_val<<CS01)|
	(pres_timer0[i].CSn0_val<<CS00)|
	(1<<WGM01);
	
	TCNT0=0;
	TIMSK=(1<<OCIE0); //• Bit 1 – OCIE0 TimerCounter0 Output Compare Match Interrupt Enable
	OCR0=top_val;
	sei();
}


void timer1_CTCmode_init(int prescaler_num_input, int top_val)
{

	//if prescaler_num_input == -1 --> STOP timer
	
	int i=0;
	while(i<8)
	{
		if(prescaler_num_input==pres_timer1_2_3[i].prescaler_num)break;
		i++;
	}
	TCCR1B= (pres_timer1_2_3[i].CSn2_val<<CS12)|
	(pres_timer1_2_3[i].CSn1_val<<CS11)|
	(pres_timer1_2_3[i].CSn0_val<<CS10)|
	(1<<WGM12);
	
	TCNT1=0;
	TIMSK=(1<<OCIE1A); //• Bit 1 – OCIE0 TimerCounter0 Output Compare Match Interrupt Enable
	OCR1A=top_val;
	sei();
}
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void Timer1_init();
void init_interrupt_timer1_nor();
void led_init();
void led_put(uint8_t led);
uint8_t led_read();
int counter=0;





int main(void)
{
	led_init();
	Timer1_init();
	/* Replace with your application code */
	while (1)
	{
	}
}

ISR(TIMER1_OVF_vect){
	counter+=1;
	if(counter==1000){
		counter=0;
		//Toggle LED
		led_put(led_read()^0x0F);
	}
}


//dem 1 giay
void Timer1_init()
{
	
	const uint8_t pres_0=(0<<CS12)|(0<<CS11)|(0<<CS10);
	const uint8_t pres_1=(0<<CS12)|(0<<CS11)|(1<<CS10);
	const uint8_t pres_8=(0<<CS12)|(1<<CS11)|(0<<CS10);
	const uint8_t pres_64=(0<<CS12)|(1<<CS11)|(1<<CS10);
	const uint8_t pres_256=(1<<CS12)|(0<<CS11)|(0<<CS10);
	const uint8_t pres_1024=(1<<CS12)|(0<<CS11)|(1<<CS10);

	//=================================
	const uint8_t mode_a_nor=(0<<WGM10)|(0<<WGM11);
	const uint8_t mode_a_ctc=(0<<WGM10)|(0<<WGM11);
	
	const uint8_t mode_b_nor=(0<<WGM12)|(0<<WGM13);
	const uint8_t mode_b_ctc=(1<<WGM12)|(0<<WGM13);
	
	//TCCR1A|= (0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<COM1C1)|(0<<COM1C0)|mode_a_nor;
	//TCCR1B|= (0<<ICNC1)|(0<<ICES1)|(0<<0)|mode_a_nor|pres_1;
	TCCR1A=0x00;
	TCCR1B=pres_1;
	init_interrupt_timer1_nor();
}

void init_interrupt_timer1_nor(){
	TIMSK|=1<<TOIE1;
	sei();
}


void led_init(){
	DDRB=0xF0;
	DDRD=0xF0;
}
uint8_t led_read(){
	uint8_t result=0;
	result=PIND;
	result=PINB >> 4;
	
	return result;
}

void led_put(uint8_t led){
	PORTB=led << 4;
	PORTD=led;
}

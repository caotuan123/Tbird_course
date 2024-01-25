#include <avr/io.h>
#include <avr/interrupt.h>
unsigned char count = 0;
unsigned char pwm = 1;
void LED_init(void);
void Timer0_init(void);
void LED_out(char count);
int main()
{
	LED_init();
	Timer0_init();
	while(1)
	{
	}
}
ISR(TIMER0_OVF_vect) //megszakítást kiszolgáló rutin
{
	count++; //számláló
	if (count>pwm)
	{
		PORTC = 0; //kikapcsoljuk az összes LED-et
		if (count>100)
		{
			count=0;
			pwm++;
		}
	}
	else
	{
		PORTC |= 0x80;
		 //bekapcsoljuk az összes LED-et
	}
}
void LED_init()
{
	DDRB = 0xF0;
	DDRD = 0xF0;
	DDRC = 0x80;
	DDRE |= 0x4|0x8;
}

void LED_out (char count)
{
	PORTD=count&0xF0;
	PORTB=(count<<4)&0xF0;
}
void Timer0_init()
{
	TCCR0 = (0<<CS02) | (1<<CS01)| (0<<CS00); //8 el?osztás
	TIMSK = (1<<TOIE0); //megszakítás engedélyezés
	sei(); //globális IT EN
}
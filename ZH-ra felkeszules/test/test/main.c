#include <avr/io.h>
#include <avr/interrupt.h>
void Timer1Init();
void PORT_init();
void Timer0Init();
void SEVSEG_put1number(uint8_t szam, uint8_t digit);
void SEVSEG_put4number();
uint8_t digit[4]={0};
uint16_t szamlalo=0;
int j=0;
int main()
{
	PORT_init();
	Timer1Init(); //Timer beállítása
	Timer0Init();
	sei();
	while(1)
	{
	}
}
ISR(TIMER1_COMPA_vect)
{
	szamlalo++; //Számlálás
	if (szamlalo==1001)
	{
		szamlalo=0;
	}
	digit[0]=szamlalo%10;
	digit[1]=(szamlalo/10)%10;
	digit[2]=(szamlalo/100)%10;
	digit[3]=szamlalo/1000;
}
ISR(TIMER0_OVF_vect)
{
	SEVSEG_put4number();
}

void Timer1Init() {
	TCCR1B = (1<<WGM12) | (1<<CS12) ; //ctc //256
	TCCR1C = 0;
	OCR1A = 31249; //max 65535 (16bit-es) 1s (8MHz)
	
	TIMSK |= (1<<OCIE1A); //engedélyezés
}
void Timer0Init()
{
	TCCR0=(0<<CS02)|(1<<CS01)|(1<<CS00);//011: eloosztas 32---~1 ms
	TIMSK|=(1<<TOIE0);
}
void PORT_init()
{
	DDRA = 0xFF;
}
void SEVSEG_put1number(uint8_t szam, uint8_t digit)
{
	PORTA=0x80 | (digit)<<4 | szam; //kiíratás 0x80=enable;
}
void SEVSEG_put4number()
{
	j = (j+1)%4; //folyamatos kiírás
	SEVSEG_put1number(digit[j], j);
}
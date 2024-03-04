#include "USART.h"
#include <avr/io.h>

void USART0_Init( uint16_t baud )
{
	// set baud 51 if 8Hz and 9600 bps
	/* Set baud rate */
	/*
	2400	207		0.2% 
	4800	103		0.2% 
	9600	51		0.2% 
	14.4k	34	   -0.8%
	19.2k	25		0.2% 
	28.8k	16		2.1%
	38.4k	12		0.2%
	57.6k	8	   -3.5%
	76.8k	6	   -7.0%
	115.2k  3		8.5%
	*/
	UBRR0H = (unsigned char)(baud >>8);
	UBRR0L = (unsigned char)baud ;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);//RXEN0: RX Complete Interrupt Enable
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}
void USART1_Init( uint16_t baud )
{
	/* Set baud rate */
	UBRR1H = (unsigned char)(baud >>8);
	UBRR1L = (unsigned char)baud ;
	/* Enable receiver and transmitter */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	/* Set frame format: 8data, 1stop bit */
	UCSR1C = (0<<USBS1)|(3<<UCSZ10);
}
void USART0_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Copy ninth bit to TXB8 */
	UCSR0B &= ~(1<<TXB80);
	if ( data & 0x0100 )
	UCSR0B |= (1<<TXB80);
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
void USART1_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) )
	;
	/* Copy ninth bit to TXB8 */
	UCSR1B &= ~(1<<TXB81);
	if ( data & 0x0100 )
	UCSR1B |= (1<<TXB81);
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

unsigned char USART0_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}
unsigned char USART1_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) )
	;
	/* Get and return received data from buffer */
	return UDR1;
}

void USART0_textsend(char*s)
{
	{ while (*s)
		{
			USART0_Transmit(*s);
			s++;
		}
	}
}

void USART1_textsend(char*s)
{
	{ while (*s)
		{
			USART1_Transmit(*s);
			s++;
		}
	}
}
void USART0_rxint_on()
{
	UCSR0B|=1<<RXCIE0;
}

void USART0_rxint_off()
{
	UCSR0B&=~(1<<RXCIE0);
}
void USART1_rxint_on()
{
	UCSR1B|=1<<RXCIE1;
}
void USART1_rxint_off()
{
	UCSR1B&=~(1<<RXCIE1);
}
void USART1_txint_on()
{
	UCSR1B|=1<<TXCIE1;
}
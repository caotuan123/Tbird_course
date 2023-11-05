#include "USART.h"
#include <avr/io.h>

void USART0_Init( uint16_t baud )
{
	// set baud 51 if 8Hz and 9600 bps
	/* Set baud rate */
	UBRR0H = (unsigned char)(baud >>8);
	UBRR0L = (unsigned char)baud ;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);//RXEN0: RX Complete Interrupt Enable
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
void USART1_Init( uint16_t baud )
{
	/* Set baud rate */
	UBRR1H = (unsigned char)(baud >>8);
	UBRR1L = (unsigned char)baud ;
	/* Enable receiver and transmitter */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	/* Set frame format: 8data, 2stop bit */
	UCSR1C = (1<<USBS1)|(3<<UCSZ10);
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
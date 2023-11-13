#ifndef USART_H_
#define USART_H_
#include <avr/io.h>
void USART0_Init( uint16_t baud );
void USART1_Init( uint16_t baud );
void USART0_Transmit( unsigned char data );
void USART1_Transmit( unsigned char data );
unsigned char USART0_Receive( void );
unsigned char USART1_Receive( void );
void USART0_textsend(char*s);
#endif
/*
 * mode3.h
 *
 * Created: 09/12/2023 9:33:05 CH
 *  Author: CaoAnhTuan
 */ 


#ifndef MODE3_H_
#define MODE3_H_

#include <avr/io.h>
//put this in to USART RX ISR
void mode3_run();
void mode3_start();
void mode3_stop();
#endif /* MODE3_H_ */
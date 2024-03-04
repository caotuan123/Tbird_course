#include <avr/io.h>
#include <inttypes.h>
#include "RS_485_fifo.h"
#include "USART.h"

 uint8_t fifo_p_read=0;
 uint8_t fifo_p_write=0;
 uint8_t Is_fifo_empty=1;
 uint8_t Is_fifo_full=0;
 struct fifo_frame fifo[30];

 uint8_t fifo_tmp1_id	;
 uint8_t fifo_tmp1_cmd;
 uint8_t fifo_tmp1_data1;
 uint8_t fifo_tmp1_data2;
 
 uint8_t fifo_tmp2_cmd;
 uint8_t fifo_tmp2_data1;
 uint8_t fifo_tmp2_data2;

void rs485_init()
{
	DDRC|=1<<RE;
	DDRE|=1<<DE;
}

void Drive_en(void)
{
	PORTC|=1<<RE;
	PORTE|=1<<DE;
}

void Receive_en(void)
{
	PORTC&=~(1<<RE);
	PORTE&=~(1<<DE);
}


uint8_t fifo_write(uint8_t cmd, uint8_t data1, uint8_t data2){
	if(Is_fifo_full) return 0;
	
	fifo[fifo_p_write].CMD= cmd;
	fifo[fifo_p_write].DATA1= data1;
	fifo[fifo_p_write].DATA2= data2;
	
	fifo_p_write=(fifo_p_write+1)%N_FIFO;
	
	if(fifo_p_read==fifo_p_write) Is_fifo_full=1;
	if(Is_fifo_empty) Is_fifo_empty=0;
	return 1;
}

uint8_t fifo_read(uint8_t * cmd, uint8_t * data1, uint8_t *data2){
	if (Is_fifo_empty) return 0;
	
	
	*cmd = fifo[fifo_p_read].CMD;
	*data1=fifo[fifo_p_read].DATA1;
	*data2=fifo[fifo_p_read].DATA2;
	
	fifo_p_read=(fifo_p_read+1)%N_FIFO;
	
	if(Is_fifo_full) Is_fifo_full=0;
	if(fifo_p_read==fifo_p_write) Is_fifo_empty=1;
	
	return 1;
}

void fifo_send(uint8_t id, uint8_t cmd, uint8_t data1, uint8_t data2 ){
	
	USART1_Transmit(0xAA);// start
	USART1_Transmit(id);// ID:mindenki
	USART1_Transmit(cmd);
	USART1_Transmit(data1);
	USART1_Transmit(data2);
	USART1_Transmit(0xbb);// stop
}

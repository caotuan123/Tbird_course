#ifndef RS_485_FIFO_
#define RS_485_FIFO_

#define RE PC7
#define DE PE2

#define N_FIFO 30
#define RS_START 0xAA
#define RS_STOP 0xEE
#define SLAVE10_ID 0X39
#define MASTER1_ID 0x30
#define EVERYBODY 0x50 //Command for everyone in the net
#define RS_TOKEN 0x77

#define CM_1 0x10;
#define CM_2 0x11;
#define CM_3 0x12;
#define CM_4 0x13;
#define CM_5 0x14;


struct fifo_frame
{
	uint8_t CMD;
	uint8_t DATA1;
	uint8_t DATA2;
};
extern struct fifo_frame fifo[30];//used to receive commands and data

extern uint8_t fifo_p_read;
extern uint8_t fifo_p_write;
extern uint8_t Is_fifo_empty;
extern uint8_t Is_fifo_full;

extern uint8_t fifo_tmp1_id;
extern uint8_t fifo_tmp1_cmd;
extern uint8_t fifo_tmp1_data1;
extern uint8_t fifo_tmp1_data2;

extern uint8_t fifo_tmp2_cmd;
extern uint8_t fifo_tmp2_data1;
extern uint8_t fifo_tmp2_data2;

void rs485_init(void);
void Drive_en(void);
void Receive_en(void);
uint8_t fifo_write(uint8_t cmd, uint8_t data1, uint8_t data2);
uint8_t fifo_read(uint8_t * cmd, uint8_t * data1, uint8_t *data2);
void fifo_send(uint8_t id, uint8_t cmd, uint8_t data1, uint8_t data2 );
#endif

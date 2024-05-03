#ifndef DATA_TRANSFER_LEVEL_H
#define DATA_TRANSFER_LEVEL_H

#include "stdint.h"
#include "string.h"

typedef union data
{
	char data[4];
	float send_data;
	
}Send_data_t;

#define S_OF  									0x55
#define E_OF  									0xAA
#define ESC  										0x7D
#define FAILURE_FRAME 					-1
#define TRUE_FRAME							0

#define MAX_RAW_DATA_TX 				(4 + 1)	  /*raw data is consist of 4 bytes data for velocity or position and 1 byte mode, 1 byte lenght of raw data */
#define MAX_RAW_DATA_RX					(4*3 + 1)	/*receive PID 4*3 of data and 1 byte for mode of raw data*/
#define MAX_FRAME_DATA_RX				(MAX_RAW_DATA_RX * 2 + 4)
#define MAX_FRAME_DATA_TX       (MAX_RAW_DATA_TX * 2 + 4)

void create_raw_frame_data(uint8_t *mode, float *data_to_send, uint8_t *frame_data);
uint8_t create_frame_uart_tx_data(uint8_t *data_src, uint8_t length_raw_data, uint8_t *data_des);
int8_t decode_received_frame_data(uint8_t *data_src,uint8_t *length_received_data, uint8_t *data_des, uint16_t *length_raw_data);

#endif

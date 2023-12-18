#include "data_transfer_level.h"
#include "crc16.h"

Send_data_t data; 

void create_raw_frame_data(uint8_t *mode, float *data_to_send, uint8_t *frame_data)
{
	uint8_t index = 0;
	Send_data_t tx_data;
	tx_data.send_data = *data_to_send; 
	memcpy(frame_data + index, mode, 1);
	++index;
	memcpy(frame_data + index,tx_data.data,sizeof(float));
}

uint8_t create_frame_uart_tx_data(uint8_t *data_src, uint8_t *length_raw_data, uint8_t *data_des)
{
	uint16_t count_ESC = 0;
	uint16_t crc = 0;
	*(data_des ++) = S_OF;
	for (int i = 0; i < *length_raw_data; i++)
	{
		if ((*(data_src+i)) == S_OF || (*(data_src+i) == ESC) || (*(data_src + i) == E_OF))
		{
			*(data_des++) = ESC;
			crc = crc16_floating(*(data_des - 1),crc);
			*(data_des++) = *(data_src + i) ^ 0x20;
			crc = crc16_floating(*(data_des - 1),crc);
			count_ESC ++;
		}
		else 
		{
			crc = crc16_floating(*(data_src + i),crc);
			*(data_des++) = *(data_src+i);
		}
	}
	*(data_des++) = (uint8_t) (crc);
	*(data_des++) = (uint8_t) (crc >> 8);
	*(data_des) = E_OF;
	return ((*length_raw_data) + count_ESC + 4);
}

int8_t decode_received_frame_data(uint8_t *data_src,uint8_t *length_received_data, uint8_t *data_des, uint16_t *length_raw_data)
{
	uint8_t start_check_frame = 0;
	uint8_t index = 0;
	uint8_t find_end_frame = 0;
	uint8_t *p_start_check = data_src;
	uint16_t crc_check = 0;
	int count_raw_data = 0;
	for (volatile int i = 0; i < *length_received_data; i++)
	{
		if (*(data_src + i) == S_OF)
		{
			start_check_frame = 1;
			index = i + 1;
			break;
		}
	}
	p_start_check += index;
	if (start_check_frame == 1)
	{
		for (volatile int i = 0; i < *length_received_data; i++)
		{
			if ((*(p_start_check + i) == E_OF) && (*(p_start_check + i - 1) != ESC))
			{
				index = i;
				find_end_frame = 1;
				break;
			}
		}
		if (find_end_frame == 1)
		{
			uint8_t test_1 = *(p_start_check + index - 2);
			while (*(p_start_check) != test_1)
			{
				if ((*(p_start_check)) == ESC)
				{
					crc_check = crc16_floating(*(p_start_check), crc_check);
					*(data_des++) = *(++p_start_check) ^ (0x20);
					crc_check = crc16_floating(*(p_start_check), crc_check);
				}
				else
				{
					crc_check = crc16_floating(*(p_start_check), crc_check);
					*(data_des++) = *(p_start_check);
				}
				p_start_check++;
				count_raw_data++;
			}
			uint8_t crc_1 = (uint8_t)crc_check;
			uint8_t crc_2 = (uint8_t)(crc_check >> 8);
			if (!(crc_1 == *(p_start_check) && crc_2 == *(p_start_check + 1)))
			{
				return -1;
			}else 
			{
				*length_raw_data = count_raw_data;
				return 0;
			}
		}else 
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

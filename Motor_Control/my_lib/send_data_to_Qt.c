#include "send_data_to_Qt.h"

Send_data_t send_Qt;
extern UART_HandleTypeDef huart1;
void send_data_to_Qt(MOTOR *foo_motor, MODE_t *foo_mode,CONTROL_MOTOR_t *foo_control, uint8_t *foo_frame_tx, uint8_t *length_foo_frame_tx)
{
		if ((*(foo_mode) == VELO_CONTROL_MODE) && (*(foo_control) == START_MOTOR))
		{
			/*Now runiing in velocity mode*/
				uint8_t mode = SEND_REAL_VELOCITY_CMD;
				uint8_t index = 0;
				send_Qt.send_data = foo_motor->velocity_of_motor;
				uint8_t *motor_data;
				motor_data = (uint8_t *)malloc(5);
				memcpy(motor_data + index,&mode,1);
				++index;
				memcpy(motor_data + index, send_Qt.data,sizeof(float));
				*(length_foo_frame_tx) = create_frame_uart_tx_data(motor_data,MAX_RAW_DATA_TX,foo_frame_tx);
				HAL_UART_Transmit_DMA(&huart1,foo_frame_tx,*(length_foo_frame_tx));
				free(motor_data);
		}
		
		if ((*(foo_mode) == POSI_CONTROL_MODE) && (*(foo_control) == START_MOTOR))
		{
			/*Now runiing in position mode*/
				uint8_t mode = SEND_REAL_POSITION_CMD;
				uint8_t index = 0;
				send_Qt.send_data = foo_motor->position_of_motor;
				uint8_t *motor_data;
				motor_data = (uint8_t *)malloc(5);
				memcpy(motor_data + index,&mode,1);
				++index;
				memcpy(motor_data + index, send_Qt.data,sizeof(float));
				*(length_foo_frame_tx) = create_frame_uart_tx_data(motor_data,MAX_RAW_DATA_TX,foo_frame_tx);
				HAL_UART_Transmit_DMA(&huart1,foo_frame_tx,*(length_foo_frame_tx));
				free(motor_data);
		}
}

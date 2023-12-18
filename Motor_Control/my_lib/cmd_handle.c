#include "cmd_handle.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3; 
void send_error_signal_t()
{
	uint16_t i = 0;
	i++;
}

void test_cmd_handler(uint8_t *processed_frame, MOTOR *foo_motor,PID_t *velocity_pid, PID_t *position_pid,ENCODER *foo_encoder, MODE_t *foo_mode, CONTROL_MOTOR_t *foo_control, int8_t *check_frame, TIM_HandleTypeDef *htim)
{
	if (*(check_frame) == FAILURE_FRAME)
	{
		send_error_signal_t();
	}else 
	{
		uint8_t command = *(processed_frame);
		switch(command)
		{
			case SEND_PID_CMD:
				if(*(foo_mode) == VELO_CONTROL_MODE)
				{
					/*pid for controling velocity*/
					velocity_pid->Kp = *((float *)(processed_frame + 1));
					velocity_pid->Ki = *((float *)(processed_frame + 5));
					velocity_pid->Kd = *((float *)(processed_frame + 9));
				}else 
				{
					/*pid for controlling position*/
					position_pid->Kp = *((float *)(processed_frame + 1));
					position_pid->Ki = *((float *)(processed_frame + 5));
					position_pid->Kd = *((float *)(processed_frame + 9));
				}
				break;
			case MODE_CONTROL_POSITION_CMD:
				/*choose mode control for motor. This is position control mode*/
				*(foo_mode) = POSI_CONTROL_MODE;
				foo_motor->set_point_position = *((float *)(processed_frame + 1));
				break;
			case MODE_CONTROL_VELOCITY_CMD:
				/*choose mode control for motor. This is velocity control mode*/
				*(foo_mode) = VELO_CONTROL_MODE;
				foo_motor->set_point_velocity = *((float *)(processed_frame + 1));
				break;
			case START_CMD:
				*(foo_control) = START_MOTOR;
				HAL_TIM_Base_Start_IT(&htim3);
				break;
			case STOP_CMD:
				*(foo_control) = STOP_MOTOR;
				motor_set_PWM(0,&htim1);
				HAL_TIM_Base_Stop_IT(&htim3);
				break;
			case RESET_CMD:
				/*reset pid*/
				pid_init(position_pid,0,0,0);
				pid_init(velocity_pid,0,0,0);
			/*lack of htim2 CNT = 0*/
				htim->Instance->CNT = 0;
				/*reset encoder*/
				foo_encoder->position_value_pulse = 0;
				foo_encoder->previous_value_pulse = 0;
				foo_encoder->turned_value_pulse = 0;
			/*reset motor*/
				foo_motor->position_of_motor = 0;
				foo_motor->velocity_of_motor = 0;
				foo_motor->set_point_position = 0;
				foo_motor->set_point_velocity = 0;
			/*resrt mode of motor*/
				*(foo_mode) = MODE_IDLE;
				break;
			default:
			break;
			}
	}
}

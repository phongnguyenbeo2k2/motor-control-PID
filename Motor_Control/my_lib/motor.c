#include "motor.h"

void motor_init(MOTOR *foo_motor, TIM_HandleTypeDef *htim)
{
	foo_motor->position_of_motor = 0;
	foo_motor->velocity_of_motor = 0;
	foo_motor->set_point_position = 0;
	foo_motor->set_point_velocity = 0;
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
}

void motor_setpoint_velocity(MOTOR *foo_motor, float setpoint)
{
	foo_motor->set_point_velocity = setpoint;
}
void motor_setpoint_position(MOTOR *foo_motor, float setpoint)
{
	foo_motor->set_point_position = setpoint;
}
void calculate_motor(ENCODER *foo_encoder, MOTOR *foo_motor, uint8_t calculate_velocity)
{
	if(calculate_velocity == CALCULATE_VELOCITY)
	{
		/*calculate velocity of motor*/
		foo_motor->velocity_of_motor = (((float)foo_encoder->turned_value_pulse) * 60)/ (PPR * Ts); 
	}else 
	{
		/*calculate position of motor*/
		foo_motor->position_of_motor = (((float)foo_encoder->position_value_pulse) * 360) / PPR;
	}
}
void motor_set_PWM(int motor_duty,TIM_HandleTypeDef *htim)
{
	if (motor_duty > 0)
	{
//		htim->Instance->CCR2 = (motor_duty)*((htim->Instance->ARR) / 100) ;
//		htim->Instance->CCR3 = 0;
		htim->Instance->CCR2 = 0;
		htim->Instance->CCR3 = (motor_duty)*((htim->Instance->ARR) / 100);
	}else if (motor_duty < 0)
	{
		htim->Instance->CCR2 = (-motor_duty)*((htim->Instance->ARR) / 100);
		htim->Instance->CCR3 = 0;
//		htim->Instance->CCR2 = 0;
//		htim->Instance->CCR3 = (-motor_duty)*((htim->Instance->ARR) / 100);
	}else if (motor_duty == 0)
	{
		htim->Instance->CCR2 = 0;
		htim->Instance->CCR3 = 0;
	}
}

#include "pid.h"

void pid_init(PID_t *foo_pid, float de_Kp, float de_Ki, float de_Kd)
{
	foo_pid->Kp = de_Kp;
	foo_pid->Kd = de_Kd;
	foo_pid->Ki = de_Ki;
	foo_pid->I_part = 0;
	foo_pid->pre_error_value = 0;
}

float pid_compute_velocity(PID_t *foo_pid, MOTOR *foo_motor, EMA_FILTER_t *foo_ema)
{
	/*velocity*/
	/*Step 1: filtered by ema filter uint*/
	float velocity_filtered, output_pid_velo_unit;
//	velocity_filtered = ema_filter_update(foo_ema,foo_motor->velocity_of_motor); 
	float error_velo = foo_motor->set_point_velocity  - foo_motor->velocity_of_motor;
//	foo_motor->velocity_of_motor = velocity_filtered;
	foo_pid->I_part += Ts * error_velo;
//	if (error_velo < 0.005f*(foo_motor->set_point_velocity))
//	{
//		foo_pid->I_part = 0;
//	}
	output_pid_velo_unit = (foo_pid->Kp * error_velo) + (foo_pid->Ki)*(foo_pid->I_part) + (foo_pid->Kd) * ((error_velo - foo_pid->pre_error_value) / Ts);
	foo_pid->pre_error_value = error_velo;
	if (output_pid_velo_unit > 95)
	{
		output_pid_velo_unit = 95;
	}else if (output_pid_velo_unit < -95)
	{
		output_pid_velo_unit = -95;
	}
	return output_pid_velo_unit;
}

float pid_compute_position(PID_t *foo_pid, MOTOR *foo_motor, EMA_FILTER_t *foo_ema)
{
	/*position*/
	float error_position, output_pid_position_uinit;
	error_position  = foo_motor->set_point_position - foo_motor->position_of_motor;
	foo_pid->I_part += error_position*Ts;
	if (error_position < 0.001*foo_motor->set_point_position)
	{
		foo_pid->I_part = 0;
	}
	output_pid_position_uinit = foo_pid->Kp * error_position + (foo_pid->Ki)*(foo_pid->I_part) + (foo_pid->Kd)* ((error_position - foo_pid->pre_error_value) / Ts);
	foo_pid->pre_error_value = error_position;
	if (output_pid_position_uinit > 95)
	{
		output_pid_position_uinit = 95;
	}else if (output_pid_position_uinit < -95)
	{
		output_pid_position_uinit = -95;
	}
	return output_pid_position_uinit;
}


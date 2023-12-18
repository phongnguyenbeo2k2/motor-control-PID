#ifndef MOTOR_H
#define MOTOR_H

#include "encoder.h"
/*pulse per resolution is 11 (pulse/round) * 168 *4*/
#define PPR 7932.0f
/*Sample time is 10ms*/
#define Ts 	0.01 

#define CALCULATE_VELOCITY  1
#define CALCULATE_POSITION		0

/*Note that: my motor use timer 1 for provide pulse and use chanel 2, 3 at pin A9 and A10 sequence*/
/*Timer 3 is used to sample time*/
/*Timer 2 is used to read pulse that feedback from encoder*/

typedef struct 
{
	float velocity_of_motor; /*uint round per minute that isn't filtered*/
	float	position_of_motor; /*unit degree*/
	float set_point_velocity;
	float set_point_position;
	
}MOTOR;

typedef enum
{
	MODE_IDLE,
	VELO_CONTROL_MODE,
	POSI_CONTROL_MODE
}MODE_t;

typedef enum
{
	START_MOTOR,
	STOP_MOTOR
}CONTROL_MOTOR_t;

void motor_init(MOTOR *foo_motor, TIM_HandleTypeDef *htim);
void motor_setpoint_velocity(MOTOR *foo_motor, float setpoint);
void motor_setpoint_position(MOTOR *foo_motor, float setpoint);
void calculate_motor(ENCODER *foo_encoder, MOTOR *foo_motor, uint8_t calculate_velocity);
void motor_set_PWM(int motor_duty,TIM_HandleTypeDef *htim);
#endif

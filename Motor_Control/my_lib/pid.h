#ifndef PID_H
#define PID_H

#include "motor.h"
#include "ema_filter.h"

typedef struct
{
	float Kp;
	float Ki;
	float Kd;
	float I_part;
	float pre_error_value;
}PID_t;

void pid_init(PID_t *foo_pid, float de_Kp, float de_Ki, float de_Kd);
float pid_compute_velocity(PID_t *foo_pid, MOTOR *foo_motor, EMA_FILTER_t *foo_ema);
float pid_compute_position(PID_t *foo_pid, MOTOR *foo_motor, EMA_FILTER_t *foo_ema);
#endif

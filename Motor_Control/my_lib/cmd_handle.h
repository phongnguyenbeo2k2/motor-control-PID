#ifndef CMD_HANDLE_H
#define CMD_HANDLE_H

#include "stdint.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "data_transfer_level.h"

#define SEND_PID_CMD 										0x01
#define MODE_CONTROL_VELOCITY_CMD				0X03
#define MODE_CONTROL_POSITION_CMD 			0x05
#define START_CMD												0x07
#define STOP_CMD												0x09
#define SEND_REAL_VELOCITY_CMD					0x0F
#define SEND_REAL_POSITION_CMD					0x11
#define ERROR_FRAME_CMD									0x13
#define RESET_CMD 											0x15

void send_error_signal_t(void);
void test_cmd_handler(uint8_t *processed_frame, MOTOR *foo_motor, PID_t *velocity_pid, PID_t *position_pid, ENCODER *foo_encoder, MODE_t *foo_mode, CONTROL_MOTOR_t *foo_control, int8_t *check_frame, TIM_HandleTypeDef *htim);
#endif

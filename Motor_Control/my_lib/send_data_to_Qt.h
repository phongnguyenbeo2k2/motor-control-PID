#ifndef SEND_DATA_TO_QT_H
#define SEND_DATA_TO_QT_H

#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "motor.h"
#include "pid.h"
#include "data_transfer_level.h"
#include "string.h"
#include "cmd_handle.h"
#include "stdlib.h"

void send_data_to_Qt(MOTOR *foo_motor, MODE_t *foo_mode,CONTROL_MOTOR_t *foo_control, uint8_t *foo_frame_tx, uint8_t *length_foo_frame_tx);

#endif

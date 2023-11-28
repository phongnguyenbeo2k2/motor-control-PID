#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

typedef struct
{
	/*current value pulse is pluse received from begin of sample time to end of sameple time*/
	int16_t turned_value_pulse;
	/*store CNT value from previous mutsty*/
	int16_t previous_value_pulse;
	int32_t position_value_pulse;
}ENCODER;

void encoder_init(ENCODER *foo_encoder, TIM_HandleTypeDef *htim);
void read_from_encoder(ENCODER *foo_encoder,TIM_HandleTypeDef *htim);


#endif

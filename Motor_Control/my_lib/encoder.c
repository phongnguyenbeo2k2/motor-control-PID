#include "encoder.h"

void encoder_init(ENCODER *foo_encoder, TIM_HandleTypeDef *htim)
{
	foo_encoder->position_value_pulse = 0;
	foo_encoder->previous_value_pulse = 0;
	foo_encoder->turned_value_pulse = 0;
	HAL_TIM_Encoder_Start(htim,TIM_CHANNEL_ALL);
	htim->Instance->CNT = 0;
}
void read_from_encoder(ENCODER *foo_encoder,TIM_HandleTypeDef *htim)
{
	foo_encoder->turned_value_pulse = htim->Instance->CNT - foo_encoder->previous_value_pulse;
	foo_encoder->previous_value_pulse = htim->Instance->CNT;
	foo_encoder->position_value_pulse	+= foo_encoder->turned_value_pulse;
}

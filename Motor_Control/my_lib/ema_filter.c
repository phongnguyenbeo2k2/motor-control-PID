#include "ema_filter.h"

void ema_filter_init(EMA_FILTER_t *foo_ema)
{
	foo_ema->alpla = 0;
	foo_ema->current_out = 0;
	foo_ema->previous_out = 0;
}

void ema_filter_setalpha(EMA_FILTER_t *foo_ema, float foo_alpha)
{
	if (foo_alpha > 1)
	{
		foo_alpha = 1;
	}else if (foo_alpha < 0)
	{
		foo_alpha = 0;
	}
	foo_ema->alpla = foo_alpha;
}

float ema_filter_update(EMA_FILTER_t *foo_ema, float input)
{
	foo_ema->current_out = foo_ema->alpla* input + (1 - foo_ema->alpla) * foo_ema->previous_out;
	foo_ema->previous_out = foo_ema->current_out;
	return foo_ema->current_out;
}

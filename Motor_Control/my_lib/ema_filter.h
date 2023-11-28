#ifndef EMA_FILTER_H
#define EMA_FILTER_H

typedef struct
{
	float alpla;
	float previous_out;
	float current_out;
}EMA_FILTER_t;

void ema_filter_init(EMA_FILTER_t *foo_ema);
void ema_filter_setalpha(EMA_FILTER_t *foo_ema, float foo_alpha);
float ema_filter_update(EMA_FILTER_t *foo_ema, float input);
#endif

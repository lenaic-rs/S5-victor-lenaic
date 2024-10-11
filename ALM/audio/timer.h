#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void set_MCLK_TIM3_12MHz();
void set_tim2(uint32_t period);
void tim2_change_period (uint32_t period);


#endif

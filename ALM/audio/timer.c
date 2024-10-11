#include "timer.h"
#include "discoveryf4_wiring.h"

#include <libopencm3/stm32/timer.h>

uint32_t period = 6 ;   // 84MHz / 6 ~= 12 MHz

void set_MCLK_TIM3_12MHz() {

   // Output square signal on PC7

   // Configure Mclk/PC7 as tim3 output    
   configure_I2S_MCLK_TIM3 ();

   // Mode no input freq divider, edge counting up
   // CR1  CKD = 00  CMS=00 DIR=0
   timer_set_mode(TIM3,TIM_CR1_CKD_CK_INT,TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

   // No Prescaler division : clock = apb1 frq = 42 Mhz)
   timer_set_prescaler(TIM3, 0);

   // Repeat counting  CR1 OPM = 0
   timer_continuous_mode(TIM3);

   timer_set_period(TIM3,period)  ;

   // enable_irq : output compare
//   timer_enable_irq(TIM3, TIM_DIER_CC1IE);

   // enable output compare, active high
   timer_set_oc_polarity_high(TIM3,TIM_OC2);
   timer_enable_oc_output(TIM3,TIM_OC2);

   // pwm mode
   timer_enable_oc_preload(TIM3,TIM_OC2);     // OcxPE=1
   timer_set_oc_mode(TIM3,TIM_OC2 ,TIM_OCM_PWM2);
   timer_set_oc_value(TIM3,TIM_OC2,period/2);
   timer_generate_event(TIM3,1);              // force UG bit

   // start timer
   timer_enable_counter(TIM3);
}

void set_tim2(uint32_t period) {

   // Output square signal on PC7

   // Configure Mclk/PC7 as tim3 output    
   configure_pin(PB11_TIM2_CH4);

   // Mode no input freq divider, edge counting up
   // CR1  CKD = 00  CMS=00 DIR=0
   timer_set_mode(TIM2,TIM_CR1_CKD_CK_INT,TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

   // No Prescaler division : clock = apb1 frq = 42 Mhz)
   timer_set_prescaler(TIM2, 0);

   // Repeat counting  CR1 OPM = 0
   timer_continuous_mode(TIM2);

   timer_set_period(TIM2,period)  ;

   // enable_irq 
   timer_enable_irq(TIM2, TIM_IC4);

   // enable output compare, active high
   timer_set_oc_polarity_high(TIM2,TIM_OC4);
   timer_enable_oc_output(TIM2,TIM_OC4);

   // pwm mode
   timer_enable_oc_preload(TIM2,TIM_OC4);     // OcxPE=1
   timer_set_oc_mode(TIM2,TIM_OC4 ,TIM_OCM_PWM2);
   timer_set_oc_value(TIM2,TIM_OC4,period/2);
//   timer_generate_event(TIM2,1);              // force UG bit

   // start timer
   timer_enable_counter(TIM2);
}

void tim2_change_period (uint32_t period) {
   timer_set_period(TIM2,period)  ;
}


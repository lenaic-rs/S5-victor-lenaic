/*
 *
 *  Copyright (C) 2017 Philippe Waille <Philippe.Waille@univ-grenoble-alpes.fr>
 *
 *  This discovery examples code is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this code.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#include "discoveryf4_wiring.h"
#include "cold_startup.h"
#include "timer.h"
#include "i2c_audio.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/dac.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>

#define RELOAD_VAL_500MS 0xA02BE8
#define RELOAD_VAL_100MS 0x2008C8

#define MELODIE_LENGTH 12 

uint8_t v;

typedef struct {
   uint32_t tim2_period;
   int duree;
   int actif;
} melodie_t;

melodie_t  melodie [MELODIE_LENGTH] = {
   { 60000, 10,1}, // note de 1000ms
   { 60000, 2,0},  // silence  de 200ms
   { 65000, 8,1},
   { 65000, 2,0},
   { 70000, 6,1},
   { 70000, 2,0},
   { 75000, 5,1},
   { 75000, 1,0},
   { 80000, 4,1},
   { 80000, 1,0},
   { 85000, 3,1},
   { 85000, 1,0},
};

int note_courante = 0;
uint32_t tim2_period=85000;
int duree = 1;
int actif = 0;

uint16_t valdac=0;

void do_cycle_dac() {
  if (actif) {
     valdac+=200;
     if (valdac >=2500) valdac=0;
     dac_load_data_buffer_single(DAC1,0x500+valdac,DAC_ALIGN_RIGHT12,DAC_CHANNEL1);
  }
}

void tim2_isr () {
   timer_clear_flag(TIM2, 0xff);
   do_cycle_dac();
   tim2_change_period(tim2_period);
}
                   
#define MSCK_TIM3  ((portpin_t) {GPIOC, GPIO7, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_AF_DUMMY})    

void systick_config(uint32_t reload_val) {
   systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
   systick_set_reload(reload_val);
   systick_interrupt_enable();
   systick_counter_enable();
}

void sys_tick_handler () {
   if (duree >0) { 
     duree --;
   } else {
     note_courante = (note_courante+1)%MELODIE_LENGTH;
     duree = melodie[note_courante].duree;
     tim2_period = melodie[note_courante].tim2_period;
     actif = melodie[note_courante].actif;
   }
} 
   
int main (void) {
   coldstart();

   configure_pin(MSCK_TIM3);   
  
   configure_pin(AUDIO_DAC1_OUT);
   dac_buffer_enable (DAC1,DAC_CHANNEL1);
   dac_enable (DAC1,DAC_CHANNEL1);

   configure_i2c_audio();

   set_MCLK_TIM3_12MHz();
   timer_enable_irq(TIM2, TIM_DIER_CC2IE);
   nvic_enable_irq(NVIC_TIM2_IRQ);
   set_tim2(50000);
   tim2_change_period(80000);   
   systick_config(RELOAD_VAL_100MS);      
   // write_cs(0x02, 0x22);
   // v = read_cs(0x02);
   // write_cs(0x02, 0x01);

   while (1) {
   }
   return 0;
}


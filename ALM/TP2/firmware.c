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

#include "cold_startup.h"
#include "bp_leds.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>

uint16_t n=0;

uint32_t val, bpval;

uint16_t leds_seq [12]={1,2,4,8,3,6,0xC,9,7,0xE,0xD,0xB};
int delta=1;

void plusplus () {
  n= n+delta;
}

#define RELOAD_VAl_700MS 0xffffff
#define RELOAD_VAl_350MS 0x8fffff

void systick_config(uint32_t reload_val) {
   systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
   systick_set_reload(reload_val);
   // sera a completer au prochain TP
   
   systick_counter_enable();
}

void sortie_int (uint16_t v) {
   GPIOD_ODR=0x2345;
   write_leds_int(v);
   val= GPIOD_ODR;
}

void sortie_int_bsrr (uint16_t v) {
   //GPIOD_ODR=0x2345;
   write_leds_int_bsrr(v);
   //val= GPIOD_ODR;
}

#define DELTA 1000000
void delay(uint32_t d) {
  int i;
  for (i=0; i<d*DELTA; i++) {}
}

void chenillard (uint16_t v) {
   delay(5);
   write_leds_int(leds_seq[v]);
}
    
int main (void) {
   coldstart();
   config_leds_pins();   
   //systick_config(RELOAD_VAl_350MS);
   while (1) {
      // write_leds_int_variante(0, 0, 0, 1);
      // write_leds_int_variante(0, 0, 1, 0);
      // write_leds_int_variante(0, 1, 0, 0);
      // write_leds_int_variante(1, 0, 0, 0);
      // write_leds_int_variante(1, 0, 1, 0);
      // write_leds_int_variante(1, 1, 1, 1);
      // sortie_int(0);
      // sortie_int(17);
      //sortie_int(n);
      sortie_int_bsrr(n);
      //chenillard(n%12);
      //write_leds_int(n%12);
      plusplus ();
   }
   return 0;
}


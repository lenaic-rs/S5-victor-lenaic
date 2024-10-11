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
#include "spi_mems.h"
#include "lis3dsh.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/cortex.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>

uint8_t v;

int main (void) {
   coldstart();
   config_leds_pins();
   init_spi1();
   // 1. on verifie s'il y a bien 0x3f dans WHO_AM_I (test lecture)

   // 2. on ecrit 0x22 dans OFF_X et on relit (test ecriture)
   
   
   // 3. si tout s'est bien passe, on pourra remettre 0x00 dans
   // OFF_X et puis continuer...
   
   mems_init ();
   while (1) {
      mems_wait_sample();
      mems_read_sample();
      mems_display_sample();
   }
   return 0;
}

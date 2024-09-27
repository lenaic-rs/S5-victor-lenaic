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


#ifndef CLOCKS_SETUP_H
#define CLOCKS_SETUP_H

#include <libopencm3/stm32/rcc.h>
/********************* Clocks *************************************************/

#define AHB_FREQUENCY 168000000  // 168Mhz

#define GPIO_CLOCKS \
           RCC_AHB1ENR_IOPAEN |\
           RCC_AHB1ENR_IOPBEN |\
           RCC_AHB1ENR_IOPCEN |\
           RCC_AHB1ENR_IOPDEN |\
           RCC_AHB1ENR_IOPEEN

#define APB1_CLOCKS \
           RCC_APB1ENR_TIM4EN     |\
           RCC_APB1ENR_TIM3EN     |\
           RCC_APB1ENR_TIM2EN     |\
           RCC_APB1ENR_I2C1EN     |\
           RCC_APB1ENR_SPI2EN     |\
 	   RCC_APB1ENR_SPI3EN     |\
           RCC_APB1ENR_DACEN


#define APB2_CLOCKS \
           RCC_APB2ENR_SYSCFGEN |\
           RCC_APB2ENR_SPI1EN


#define AHB2_CLOCKS \
           RCC_AHB2ENR_RNGEN

/*******************************************************************************/

static inline void setup_clocks () {
   //  ahb = 168Mhz, apb1 = 42 MHz apb2 = 84 MHz
   rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

   // enable GPIO CLOCKS
   rcc_peripheral_enable_clock(&RCC_AHB1ENR, GPIO_CLOCKS);

   // APB1 peripherals clocks : tim2 to 4
   rcc_peripheral_enable_clock(&RCC_APB1ENR, APB1_CLOCKS);

   // APB2 peripherals clocks : syscfg (for exti irq lines) + spi1
   rcc_peripheral_enable_clock(&RCC_APB2ENR, APB2_CLOCKS);

   // AHB2 : random number generator
   rcc_peripheral_enable_clock(&RCC_AHB2ENR, AHB2_CLOCKS);
}

#endif //  CLOCKS_SETUP_H

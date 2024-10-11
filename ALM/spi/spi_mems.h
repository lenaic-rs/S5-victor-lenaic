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


#ifndef SPI_MEMS
#define SPI_MEMS

#include <stdint.h>
#include <libopencm3/stm32/gpio.h>

// Acceleration theshold for display
#define DELTA 7 

// Systick count shared with firmware
extern uint32_t syscount;

extern int8_t x;
extern int8_t y;

void mems_init();
void mems_wait_sample ();
void mems_read_sample ();
void mems_display_sample ();

// debugging purpose
void init_spi1();              
uint8_t spi_read_command (uint8_t add);
void spi_write_command (uint8_t add,  uint8_t data);

#endif

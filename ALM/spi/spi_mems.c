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

#include <stdbool.h>

#include "spi_mems.h"
#include "lis3dsh.h"
#include "bp_leds.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/exti.h>

// Mems x and y values
int8_t x=0;
int8_t y=0;

void spi_mems_configure_pins () {
  // SPI1 signals
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO5 | GPIO6 | GPIO7);            
  gpio_set_af(GPIOA, GPIO_AF5, GPIO5 | GPIO6 | GPIO7);                           
      
  // LIS chip select       
  gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);    
   
  // LIS interrupt       
  gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);     
  gpio_set_af(GPIOE, GPIO_AF15, GPIO0);
}

void spi_lis_mems_select () {
  gpio_clear(GPIOE, GPIO3);
}

void spi_lis_mems_deselect () {
  gpio_set(GPIOE, GPIO3);
}

void init_spi1 () {
   // baud rate : APB2 freq/16 : 82Mhz/16 = 5,125MHz  (< 10MHz required by mems)
   // Clock idle high, sample on rising edge : CPOl,CPHA = (1,1)
   // 8 bits frame, MSB bit first, no crc

   spi_mems_configure_pins ();

   spi_lis_mems_deselect();
 
   spi_disable_crc(SPI1);
   spi_init_master(SPI1,SPI_CR1_BAUDRATE_FPCLK_DIV_16,
                   SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2,
                   SPI_CR1_DFF_8BIT,SPI_CR1_MSBFIRST);
   spi_set_full_duplex_mode(SPI1);
   spi_enable(SPI1);  
}

uint8_t spi_read_command (uint8_t add) {
   uint8_t result;
   spi_lis_mems_select();
   spi_send(SPI1, (add | 1 << 7));
   spi_read(SPI1);
   spi_send(SPI1, 0);
   result = spi_read(SPI1);
   spi_lis_mems_deselect();   
   return result;
}

void spi_write_command (uint8_t add,  uint8_t data) {
   spi_lis_mems_select();
   spi_send(SPI1, (add & (~(1 << 7))));
   spi_read(SPI1);
   spi_send(SPI1, data);
   spi_read(SPI1);
   spi_lis_mems_deselect();  
}

void mems_init () {
   // Lis3dsh appplication note, operating modes, page 10 :
   // On power up, lis3dsh download calibration from its internal rom
   // It enters power down mode after a boot sequence of ~ 10ms
   // We should not emit the following spi write until powerup time + 10ms
   // But rcc_clock_setup_pll seems long enough so
   // no extra delay is provided here

   spi_write_command(0x24, LIS3_CTRL5_INIT);
   spi_write_command(0x25, LIS3_CTRL6_INIT);
   spi_write_command(0x2E, LIS3_FIFO_CTRL_INIT);

   spi_write_command(0x20, LIS3_CTRL4_INIT);
   spi_write_command(0x23, LIS3_CTRL3_INIT);

}

void mems_wait_sample () {
  while ((spi_read_command(0x27) & (1 << 3)) == 0) {}
}

void mems_read_sample () {
   x = spi_read_command(0x29);
   y = spi_read_command(0x2B);
}

void mems_display_sample () {

  if (x > DELTA) {
     write_pin(EAST_BIT,1);
     write_pin(WEST_BIT,0);
  } else if (x < -DELTA) {
     write_pin(EAST_BIT,0);
     write_pin(WEST_BIT,1);
  } else {
     write_pin(EAST_BIT,0);
     write_pin(WEST_BIT,0);
  }
   
  if (y > DELTA) {
     write_pin(NORTH_BIT,1);
     write_pin(SOUTH_BIT,0);
  } else if (y < -DELTA) {
     write_pin(NORTH_BIT,0);
     write_pin(SOUTH_BIT,1);
  } else {
     write_pin(NORTH_BIT,0);
     write_pin(SOUTH_BIT,0);
  }
}


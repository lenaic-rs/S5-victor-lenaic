#include "bp_leds.h"

#include <libopencm3/stm32/gpio.h>

void config_leds_pins () {
   gpio_mode_setup(GPIOD,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,
                   NORTH_MASK | SOUTH_MASK | EAST_MASK | WEST_MASK);
}

void write_pin(uint16_t pin, bool value) {
  GPIOD_BSRR = 1 << (value ? pin : (pin+16));
}


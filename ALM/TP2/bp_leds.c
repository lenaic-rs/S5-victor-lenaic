#include "bp_leds.h"
#include <libopencm3/stm32/gpio.h>

void config_leds_pins () {
   gpio_mode_setup(GPIOD,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,LEDS_MASK);
}

void write_leds_int  (uint16_t intval) {
  // a completer

}

void write_leds_int_bsrr (uint16_t intval) {
   uint32_t v = intval;
   // a completer
   
}

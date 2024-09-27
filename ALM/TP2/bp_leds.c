#include "bp_leds.h"
#include <libopencm3/stm32/gpio.h>

void config_leds_pins () {
   gpio_mode_setup(GPIOD,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,LEDS_MASK);
}

void write_leds_int  (uint16_t intval) {
   uint32_t t = GPIOD_ODR & (~(15 << 12));
   uint32_t m = intval % 16;
   // GPIOD_ODR = t | (intval << 12);
   GPIOD_ODR = t | (((uint32_t) intval) << 12);
}

void write_leds_int_variante (char green, char orange, char red, char blue) {
   uint32_t masque = (green << 12) | (orange << 13) | (red << 14) | (blue << 15);
   uint32_t t = GPIOD_ODR & (~(15 << 12));
   GPIOD_ODR = t | masque;
   //GPIOD_ODR = (intval << 12);
}

void write_leds_int_bsrr (uint16_t intval) {
   uint32_t v = intval;
   // a completer
   
}

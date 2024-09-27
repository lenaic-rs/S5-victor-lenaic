#include "bp_leds.h"
#include <libopencm3/stm32/gpio.h>

void config_leds_pins()
{
   gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDS_MASK);
}

void write_leds_int(uint16_t intval)
{
   uint32_t val = intval;
   uint32_t t = GPIOD_ODR & (~(0xf << 12));
   uint32_t m = val & 0xf;
   GPIOD_ODR = t | (m << 12);
}

void write_leds_int_variante(char green, char orange, char red, char blue)
{
   uint32_t masque = (green << 12) | (orange << 13) | (red << 14) | (blue << 15);
   uint32_t t = GPIOD_ODR & (~(15 << 12));
   GPIOD_ODR = t | masque;
}

void write_leds_int_bsrr(uint16_t intval)
{
   uint32_t v = (intval & 1) == 0;
   uint32_t o = ((intval & 2) >> 1) == 0;
   uint32_t r = ((intval & 4) >> 2) == 0;
   uint32_t b = ((intval & 8) >> 3) == 0;

   GPIOD_BSRR = (1 << (12 + (16 * v))) | (1 << (13 + (16 * o))) | (1 << (14 + (16 * r))) | (1 << (15 + (16 * b)));
}

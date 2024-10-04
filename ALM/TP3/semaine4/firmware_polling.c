#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rng.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>

#include "bp_leds.h"
#include "cold_startup.h"

#define RELOAD_VAl_350MS 0x8fffff

uint32_t rnd = 0;

void init_rng_polling() {
  RNG_CR |= RNG_CR_RNGEN;
}
 
void systick_config(uint32_t reload_val) {
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(reload_val);
  systick_interrupt_enable();
  systick_counter_enable();
}

void sys_tick_handler(){
  write_leds_int((uint16_t) rnd);
}

int check_seed_error() {
  return ((RNG_SR & RNG_SR_SECS) != 0);
}

int check_clock_error() {
  return ((RNG_SR & RNG_SR_CECS) != 0);
}

int check_data_ready() {
  return ((RNG_SR & RNG_SR_DRDY) != 0);
}

void wait_for_new_rnd() {
  while (!check_data_ready()) {  
    if (check_seed_error() || check_clock_error()) {
      init_rng_polling();
    }
  }
}

int main (void) {	
  coldstart(); 
  config_leds_pins();
  gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDS_MASK);
  systick_config(RELOAD_VAl_350MS);
  init_rng_polling(); 
  
  while(1) {
    wait_for_new_rnd();      //  <-- ?
    rnd = RNG_DR;            //  <-- ? 
  }
  return 0;
}

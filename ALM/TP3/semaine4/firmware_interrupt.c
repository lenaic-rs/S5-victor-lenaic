#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rng.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>

#include "bp_leds.h"
#include "cold_startup.h"

#define RELOAD_VAl_350MS 0x8fffff

uint32_t rnd = 0;

void init_rng() {

}
 
void systick_config(uint32_t reload_val) {
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(reload_val);

  systick_counter_enable();
}

void sys_tick_handler(){

}

int check_no_seed_error() {
  
}

int check_no_clock_error() {
 
}

int check_data_ready() {
 
}

int main (void) {	
  coldstart(); 
  config_leds_pins();
  gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDS_MASK);
  systick_config(RELOAD_VAl_350MS);
  
  init_rng();
  while(1);
  return 0;
}


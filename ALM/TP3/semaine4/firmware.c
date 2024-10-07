#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rng.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>

#include "bp_leds.h"
#include "cold_startup.h"
#include <stdio.h>
#define RELOAD_VAl_350MS 0x8fffff

uint32_t rnd = 0;
long count_rng_interrupts = 0;

void init_rng() {
  nvic_enable_irq(NVIC_HASH_RNG_IRQ);
  RNG_CR |= RNG_CR_IE;
  RNG_CR |= RNG_CR_RNGEN;
}
 
void systick_config(uint32_t reload_val) {
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(reload_val);
  systick_interrupt_enable();
  systick_counter_enable();
}

void sys_tick_handler(){
  printf("%ld\n", count_rng_interrupts);
  count_rng_interrupts = 0;
  write_leds_int((uint16_t) rnd);
}

int check_no_seed_error() {
  return ((RNG_SR & RNG_SR_SEIS) == 0);
}

int check_no_clock_error() {
  return ((RNG_SR & RNG_SR_CEIS) == 0);
}

int check_data_ready() {
  return ((RNG_SR & RNG_SR_DRDY) != 0);
}

void hash_rng_isr() {
  count_rng_interrupts++;
  if (check_no_seed_error() && check_no_clock_error() && check_data_ready()) {
      rnd = RNG_DR;
  } else {
    printf("Erreur interruption\n");
    RNG_SR &= (~RNG_SR_CEIS);
    RNG_SR &= (~RNG_SR_SEIS);
    RNG_CR |= RNG_CR_RNGEN;
  }
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


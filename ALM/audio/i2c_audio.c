#include "i2c_audio.h"
#include "cs_audio_config.h"
#include "discoveryf4_wiring.h"

#include <libopencm3/stm32/i2c.h>
#include <stdbool.h>

// I2C audio peripheral address
// 100101a  avec a=AD0=0
// On I2C bus sda : 0x94 write 0x95 read

#define CS42L22_I2C_ADDRESS 0x4a

// I2C apb1 bus clock input = 42 MHz
#define FREQ_FROM_APB1 42

#define SETUP_FOR_WRITE false
#define SETUP_FOR_ACCESS false
#define SETUP_FOR_READ true

void configure_i2c_audio (void) {
  // configure pins and reset chip
  configure_I2C_AUDIO_PINS ();
  
  i2c_reset(I2C1);
  i2c_peripheral_disable(I2C1);

  // Speed configuration -> standard mode@100KHz
  i2c_set_clock_frequency(I2C1,FREQ_FROM_APB1);
  i2c_set_standard_mode(I2C1);
  i2c_set_speed(I2C1,i2c_speed_sm_100k,FREQ_FROM_APB1);
  i2c_set_trise(I2C1,FREQ_FROM_APB1+1);

  i2c_peripheral_enable(I2C1);

  // unreset AUDIO
  write_pin(AUDIO_RESET,true);

  cs_begin_init();
  cs_config(cs_analog_init_seq);
  cs_end_init();
}

void wait_not_busy () {    
   while ((I2C1_SR2 & (1 << 1)) != 0){}
}     

void wait_start_sent () {   
   while ((I2C1_SR1 & 1) == 0){}
}    

void wait_address_sent () { 
   while ((I2C1_SR1 & (1 << 1)) == 0){}   
   
}  

void wait_byte_sent () {     
   while ((I2C1_SR1 & (1 << 2)) == 0){}
   
}   

void wait_byte_received () {    
   while ((I2C1_SR1 & (1 << 6)) == 0){}
  
}   

void clear_addr_bit () { 
   (void)I2C1_SR2;
} 

void send_address (bool read) { 
  i2c_send_7bit_address(I2C1, CS42L22_I2C_ADDRESS, read);
} 

void write_cs (uint8_t regnum, uint8_t regval) {
  wait_not_busy();
  i2c_send_start(I2C1);
  wait_start_sent();
  send_address(I2C_WRITE);
  wait_address_sent();
  clear_addr_bit();
  i2c_send_data(I2C1, regnum);
  wait_byte_sent();
  i2c_send_data(I2C1, regval);
  wait_byte_sent();
  i2c_send_stop(I2C1);
}

int8_t read_cs (uint8_t regnum) {
  uint8_t data;
  wait_not_busy();
  i2c_send_start(I2C1);
  wait_start_sent();
  send_address(I2C_WRITE);
  wait_address_sent();
  clear_addr_bit();
  i2c_send_data(I2C1, regnum);
  wait_byte_sent();
  i2c_send_stop(I2C1);
  wait_not_busy();
  i2c_send_start(I2C1);
  wait_start_sent();
  send_address(I2C_READ);
  wait_address_sent();
  clear_addr_bit();
  i2c_disable_ack(I2C1);
  wait_byte_received();
  data = i2c_get_data(I2C1); 
  i2c_send_stop(I2C1);
  return data;
}


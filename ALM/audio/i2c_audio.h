#ifndef I2S_AUDIO_H
#define I2S_AUDIO_H

#include <stdint.h>
#include <stdbool.h>

void configure_i2c_audio (void);
void write_cs (uint8_t regnum, uint8_t regval);
int8_t read_cs (uint8_t regnum);

#endif

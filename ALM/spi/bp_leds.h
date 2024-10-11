#ifndef BP_LEDS_H
#define BP_LEDS_H

#include <stdint.h>
#include <stdbool.h>

// LEDS on GPIOD

#define GREEN_BIT 12
#define WEST_BIT GREEN_BIT

#define GREEN_MASK (1 << GREEN_BIT)
#define WEST_MASK GREEN_MASK

#define ORANGE_BIT  13
#define NORTH_BIT ORANGE_BIT 

#define ORANGE_MASK (1 << ORANGE_BIT)
#define NORTH_MASK ORANGE_MASK 

#define RED_BIT 14
#define EAST_BIT RED_BIT

#define RED_MASK (1 << RED_BIT)
#define EAST_MASK RED_MASK

#define BLUE_BIT 15
#define SOUTH_BIT BLUE_BIT

#define BLUE_MASK (1 << BLUE_BIT)
#define SOUTH_MASK  BLUE_MASK


#define LEDS_FIRST_BIT GREEN_BIT
#define LEDS_MASK (0xf << LEDS_FIRST_BIT)


// User push button on GPIOA

#define BP_USER_BIT 0
#define BP_BLUE_BIT BP_USER_BIT

#define BP_USER_MASK (1 << BP_USER_BIT)
#define BP_BLUE_MASK BP_USER_MASK 

// Set leds pins mode 
void config_leds_pins ();

// Set led pin value. 
// write_pin (ORANGE_BIT,1) : orange led on
// write_pin (RED_BIT,1)    : red    led off
void write_pin(uint16_t pin, bool value); 

#endif // BP_LEDS_H

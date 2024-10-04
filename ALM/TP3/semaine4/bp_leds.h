#ifndef BP_LEDS_H
#define BP_LEDS_H

#include <stdint.h>

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

#define RED_MASK (1 << RED_BIT 14)
#define EAST_MASK RED_MASK

#define BLUE_BIT 15
#define SOUTH_BIT BLUE_

#define BLUE_MASK (1 << BLUE_BIT)
#define SOUTH_MASK  BLUE_MASK


#define LEDS_FIRST_BIT GREEN_BIT
#define LEDS_MASK (0xf << LEDS_FIRST_BIT)


// Access functions

// intval in [0,15] : 4 bits as BROG or SENW
// Example : North and South on, East and West off
//  write_leds_int(0xa)
//  write_leds_mask(SOUTH_MASK | NORTH_MASK);

void write_leds_int  (uint16_t intval);
void write_leds_int_bsrr (uint16_t intval);

// Set leds pins mode as output
void config_leds_pins ();

#endif // BP_LEDS_H


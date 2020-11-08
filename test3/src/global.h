#ifndef _VVC_GLOBAL_H
#define _VVC_GLOBAL_H

#include <stdint.h>
#include "stm32f031x6.h"

// Define some simple pin mappings macros
// 'BUTTON_PIN' will double as the 'A' pin for using
// an incremental rotary encoder, so they can share
// EXTI initialization logic.
// 'BUTTON_PIN' must be between PB0 or PB1, unless you want
// to use a different NVIC interrupt and/or GPIO port.
#define BUTTON_PIN     (1)
// (This should also be a GPIOB pin, but can be from 0-15)
#define ROTARY_PIN_B   (0)
// (This should also be a GPIOB pin; pin B3 is the
//  onboard LED for 'Nucleo-32' boards.)
#define LED_PIN        (3)
#define LED_DELAY_MS        2000


#endif

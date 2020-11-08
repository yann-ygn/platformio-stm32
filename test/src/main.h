#ifndef _VVC_MAIN_H
#define _VVC_MAIN_H

#define BUTTON_PIN     (1)
// (This should also be a GPIOB pin, but can be from 0-15)
#define ROTARY_PIN_B   (0)
// (This should also be a GPIOB pin; pin B3 is the
//  onboard LED for 'Nucleo-32' boards.)
#define LED_PIN        (3)

#include <stdint.h>
#include "stm32f031x6.h"

extern "C" void EXTI0_1_IRQ_handler(void);

#endif

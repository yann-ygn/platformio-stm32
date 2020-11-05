#ifndef _VVC_MAIN_H
#define _VVC_MAIN_H

#include <stdint.h>
#include "stm32f031x6.h"

// Define GPIOB pin mappings for our LED and button.
#define BUTTON_PIN (1)
#define LED_PIN    (3)


// C++ memory regions for initializing statics.
// ('fini_array' is ignored because static destructors are rarely
//  important in embedded programs, which never really 'exit'.)
extern void (*_spreinit_array []) (void) __attribute__((weak));
extern void (*_epreinit_array [])(void) __attribute__((weak));
extern void (*_sinit_array [])(void) __attribute__((weak));
extern void (*_einit_array [])(void) __attribute__((weak));

#endif

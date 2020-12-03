#include <stdint.h>
#include <stm32f031x6.h>
#include "utils.h"

#ifndef HARDWARE_H
#define HARDWARE_H

extern "C" void SysTick_Handler(void); // millis() type ISR method

extern "C" void DMA1_Channel2_3_IRQHandler(void);

#endif
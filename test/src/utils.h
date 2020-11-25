#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <stm32f031x6.h>
#include "gpio.h"

namespace Utils
{
    namespace
    {
        uint32_t sysTickCounter = 0;
        uint32_t clockFrequency = 0;
    }

    void clockSetup();
    void setSysTickTimer();
    void incrementSysTickCounter();
    uint32_t getSysTickCounter();
    uint32_t getClockFrequency();
}

#endif
#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stm32f031x6.h>

namespace Utils
{
    namespace
    {
        uint32_t sysTickCounter = 0;
        uint32_t clockFrequency = 0;
    }

    void setClock();
    void setSysTickTimer();
    void incrementSysTickCounter();
    uint32_t getSysTickCounter();
}

#endif
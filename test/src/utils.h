#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
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

class CircularBuffer
{
    private:
        size_t m_size = 0;
        size_t m_capacity = 0;
        size_t m_read = 0;
        size_t m_write = 0;

    public:
        CircularBuffer(size_t size) : m_size(size) {} }
};

class Logger
{
    private:


    public:

};
#endif
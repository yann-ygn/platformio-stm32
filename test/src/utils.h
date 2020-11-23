#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdlib.h>
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

template<typename T, uint16_t N>
class CircularBuffer
{
    private:
        static const uint16_t m_size = N + 1;
        T m_buffer[m_size];
        size_t m_read = 0;
        size_t m_write = 0;

    public:
        CircularBuffer(size_t size) {}
        void read(T& item);
        T read();
};

class Logger
{
    private:


    public:

};
#endif
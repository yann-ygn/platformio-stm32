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

class CircularBuffer
{
    private:
        size_t m_size = 5;
        uint8_t m_buffer[5] = { 0 };
        size_t m_read = 0;
        size_t m_write = 0;

        void advance(size_t& value)
        {
            value = (value + 1) % m_size;
        }

    public:
        CircularBuffer() {}

        void write(uint8_t item)
        {
            m_buffer[m_write] = item;
            advance(m_write);
            if (isEmpty())
            {
                advance(m_read);
            }
        }

        uint8_t read()
        {
            if (! isEmpty())
            {
                size_t oldRead = m_read;
                advance(m_read);
                return m_buffer[oldRead];
            }
        }

        bool isEmpty()
        {
            return (m_read == m_write);
        }
};

class Logger
{
    private:
        void startDmaTx();

    public:
        void logByte(uint8_t byte);

};
#endif
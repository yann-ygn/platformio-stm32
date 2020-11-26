#ifndef LOG_H
#define LOG_H

#include <cstdint>
#include <cstring>
#include <stm32f031x6.h>
#include "buffer.h"
#include "serial.h"

class Logger
{
    private:
        Serial* m_serialPort;
        CircularBuffer m_buffer;

    public:
        Logger(Serial* serialport, uint16_t bufferlenght) : m_serialPort(serialport), m_buffer(bufferlenght) { }
        void log(const char* str);
};

#endif
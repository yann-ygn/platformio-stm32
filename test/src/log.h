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
        
        size_t m_readLength = 0;

        bool m_dmaTxInProgress = false;

    public:
        Logger(Serial* serialport, uint16_t bufferlenght) : m_serialPort(serialport), m_buffer(bufferlenght) { }
        void log(const char* str);
        void dmaTransferCompleteISR();
        void tx();
        bool getDmaTxInProgress();
        void setDmaTxInProgress(bool status);
};

#endif
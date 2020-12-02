#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <stm32f031x6.h>

class CircularBuffer
{
    private:
        size_t m_size;
        char* m_buffer;
        size_t m_read = 0;
        size_t m_write = 0;

        size_t getMin(size_t x, size_t y);
        size_t getMax(size_t x, size_t y);

    public:
        CircularBuffer(size_t size) : m_size(size) { m_buffer = new char[m_size]; }

        size_t getFree();
        size_t getAvailable();
        void write(const char* data, size_t len);
        void read(char* data, size_t len);
        char* getReadAddress();
        void setReadAddress(size_t len);
        size_t getReadLength();
};

#endif
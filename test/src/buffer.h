#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <cstdlib>
#include <stm32f031x6.h>

class CircularBuffer
{
    private:
        size_t m_size;
        char* m_buffer;
        size_t m_read = 0;
        size_t m_write = 0;

        void advance(size_t& value);

    public:
        CircularBuffer(size_t size) : m_size(size) { m_buffer = new char[m_size]; }

        void write(char item);
        void writeString(const char* str, size_t len);

        char read();
        void readString(char* data, size_t len);

        bool isEmpty();
};

#endif
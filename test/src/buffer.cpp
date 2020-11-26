#include "buffer.h"

void CircularBuffer::advance(size_t& value)
{
    value = (value + 1) % m_size;
}

void CircularBuffer::write(char item)
{
    m_buffer[m_write] = item;
    advance(m_write);
    if (isEmpty())
    {
        advance(m_read);
    }
}

char CircularBuffer::read()
{
    if (! isEmpty())
    {
        size_t oldRead = m_read;
        advance(m_read);
        return m_buffer[oldRead];
    }
}

bool CircularBuffer::isEmpty()
{
    return (m_read == m_write);
}

void CircularBuffer::writeString(const char* str, size_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        write(str[i]);
    }
}

void CircularBuffer::readString(char* data, size_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        data[i] = read();
    }
}
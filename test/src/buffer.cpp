#include "buffer.h"

size_t CircularBuffer::getMin(size_t x, size_t y)
{
    if (x < y)
    {
        return x;
    }
    else
    {
        return y;
    }    
}

size_t CircularBuffer::getMax(size_t x, size_t y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }   
}

size_t CircularBuffer::getFree()
{
    size_t size = 0;
    size_t r = m_read;
    size_t w = m_write;

    if (w == r) // Buffer empty
    {
        size = m_size;
    }
    else if (r > w)
    {
        size = r - w;
    }
    else
    {
        size = m_size - (w - r);
    }
    
    return size - 1;
}

size_t CircularBuffer::getAvailable()
{
    size_t size = 0;
    size_t r = m_read;
    size_t w = m_write;

    if (r == w) // Buffer empty
    {
        size = 0;
    }
    else if (w > r)
    {
        size = w - r;
    }
    else
    {
        size = m_size - (r - w);
    }
    
    return size;
}

void CircularBuffer::write(const char* data, size_t len)
{
    size_t free = getFree();
    len = getMin(free, len);

    size_t tocopy = getMin(m_size - m_write, len);

    memcpy(&m_buffer[m_write], data, len);
    m_write += tocopy;
    len -= tocopy;

    if (len > 0)
    {
        memcpy(m_buffer, &data[tocopy], len);
        m_write = len;
    }

    if (m_write >= m_size)
    {
        m_write = 0;
    }
}

void CircularBuffer::read(char* data, size_t len)
{
    size_t available = getAvailable();
    len = getMin(available, len);

    size_t tocopy = getMin(m_size - m_read, len);

    memcpy(data, &m_buffer[m_read], len);
    m_read += tocopy;
    len -= tocopy;

    if (len > 0)
    {
        memcpy(&data[tocopy], m_buffer, len);
        m_read = len;
    }

    if (m_read >= m_size)
    {
        m_read = 0;
    }
}

char* CircularBuffer::getReadAddress()
{
    return &m_buffer[m_read];
}

void CircularBuffer::setReadAddress(size_t len)
{
    size_t available = getAvailable();

    len = getMin(len, available);
    m_read += len;

    if (m_read >= m_size)
    {
        m_read -= m_size;
    }
}

size_t CircularBuffer::getReadLength()
{
    size_t len = 0;
    size_t r = m_read;
    size_t w = m_write;

    if (w > r)
    {
        len = w - r;
    }
    else if (r > w)
    {
        len = m_size - r;
    }
    else
    {
        len = 0;
    }

    return len;
}

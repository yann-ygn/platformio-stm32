#include "log.h"

void Logger::log(const char* str)
{
    size_t len = strlen(str);
    m_buffer.write(str, len);
    char* address = m_buffer.getReadAddress();
    size_t len2 = m_buffer.getReadLength();
    m_serialPort->startDmaTx(address, len2);
    m_buffer.setReadAddress(len2);
}
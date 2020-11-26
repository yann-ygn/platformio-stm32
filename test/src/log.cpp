#include "log.h"

void Logger::log(const char* str)
{
    size_t len = strlen(str);
    m_buffer.writeString(str, 4);
    char data[4] = {};
    m_buffer.readString(data, 4);
    m_serialPort->print(data, 4);
}
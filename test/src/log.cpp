#include "log.h"

void Logger::log(const char* str)
{
    size_t len = strlen(str);
    m_buffer.write("zert", 4);
    char dataout[4];
    m_buffer.read(dataout, 4);
    m_serialPort->print(dataout, 4);
}
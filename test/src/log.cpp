#include "log.h"

void Logger::log(const char* str)
{
    size_t len = strlen(str);
    m_buffer.write(str, len);
    tx();
}

void Logger::dmaTransferCompleteISR()
{
    m_serialPort->clearDmaRegisters();
    m_dmaTxInProgress = false;
    m_buffer.setReadAddress(m_readLength);
}

void Logger::tx()
{
    if (! m_dmaTxInProgress)
    {
        m_readLength = m_buffer.getReadLength();

        if (m_readLength > 0)
        {
            char* address = m_buffer.getReadAddress();
            m_serialPort->startDmaTx(address, m_readLength);
            //m_dmaTxInProgress = true;
        }
    }
}

bool Logger::getDmaTxInProgress()
{
    return m_dmaTxInProgress;
}

void Logger::setDmaTxInProgress(bool status)
{
    m_dmaTxInProgress = status;
}
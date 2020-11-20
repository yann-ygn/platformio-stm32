#include "dma.h"

void Dma::dmaSetup()
{
    #ifdef DMA1
        if (m_dmaPeripheral == DMA1)
        {
            if ((RCC->AHBENR & RCC_AHBENR_DMAEN) != 0x00000001)
            {
                RCC->AHBENR |= RCC_AHBENR_DMAEN;
            }
        }
    #endif
}

void DmaChannel::dmaChannelSetup()
{
    m_dmaPeripheral.dmaSetup();
}
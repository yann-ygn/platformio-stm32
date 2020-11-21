#include "dma.h"

void Dma::dmaSetup()
{
    #ifdef DMA1
        if (m_dmaController == DMA1)
        {
            if ((RCC->AHBENR & RCC_AHBENR_DMAEN) != 0x00000001)
            {
                RCC->AHBENR |= RCC_AHBENR_DMAEN;
            }
        }
    #endif
}

uint32_t Dma::getTransferStatusRegisters()
{
    return m_dmaController->ISR;
}

void Dma::clearTransferErrorStatusRegister(uint8_t channel)
{
    m_dmaController-> IFCR |= (1 << (0x00000008 << (channel - 1)));
}

void Dma::clearHalfTransferStatusRegister(uint8_t channel)
{
    m_dmaController->IFCR |= (1 << (0x00000004 << (channel - 1)));
}

void Dma::clearTransfertCompleteStatusRegister(uint8_t channel)
{
    m_dmaController->IFCR |= (1 << (0x00000002 << (channel - 1)));
}

void DmaChannel::dmaChannelSetup()
{
    m_dmaController.dmaSetup();

    if (m_dmaChannel == DMA1_Channel1)
    {
        m_channel = 1;
    }
    else if (m_dmaChannel == DMA1_Channel2)
    {
        m_channel = 2;
    }
    else if (m_dmaChannel == DMA1_Channel3)
    {
        m_channel = 3;
    }
    else if (m_dmaChannel == DMA1_Channel4)
    {
        m_channel = 4;
    }
    else if (m_dmaChannel == DMA1_Channel5)
    {
        m_channel = 5;
    }
}

void DmaChannel::setDmaChannelSettings(dmaChannelDirectionSettings direction = readFromPeripheral,
dmaChannelPrioritysettings priority = lowPriority,
dmaChannelMemorySizeSettings memsize = memSize8bits,
dmaChannelPeripheralSizeSettings periphsize = periphSize8bits,
dmaChannelMemoryIncreaseModeSettings meminc = memIncDisabled,
dmaChannelTransferCompleteInterruptSettings completeinc = transferCompleteIntDisabled,
dmaChannelPeripheralIncreaseModeSettings periphinc = periphIncDisabled,
dmaChannelMem2MemSettings mem2mem = mem2MemDisabled,
dmaChannelCircularModeSettings circmode = circModeDisabled)
{
    switch (mem2mem)
    {
        case mem2MemDisabled:
            m_dmaChannel->CCR &= ~(DMA_CCR_MEM2MEM);
            break;
        
        case mem2MemEnabled:
            m_dmaChannel->CCR |= (DMA_CCR_MEM2MEM);
            break;
        
        default:
            break;
    }

    switch (priority)
    {
        case lowPriority:
            m_dmaChannel->CCR &= ~(DMA_CCR_PL);
            break;

        case mediumPriority:
            m_dmaChannel->CCR &= ~(DMA_CCR_PL);
            m_dmaChannel->CCR |= DMA_CCR_PL_0;
            break;

        case highPriority:
            m_dmaChannel->CCR &= ~(DMA_CCR_PL);
            m_dmaChannel->CCR |= DMA_CCR_PL_1;
            break;

        case veryHighPriority:
            m_dmaChannel->CCR |= DMA_CCR_PL;
            break;
        
        default:
            break;
    }

    switch (memsize)
    {
        case memSize8bits:
            m_dmaChannel->CCR &= ~(DMA_CCR_MSIZE);
            break;

        case memSize16Bits:
            m_dmaChannel->CCR &= ~(DMA_CCR_MSIZE);
            m_dmaChannel->CCR |= DMA_CCR_MSIZE_0;
            break;

        case memSize32Bits:
            m_dmaChannel->CCR &= ~(DMA_CCR_MSIZE);
            m_dmaChannel->CCR |= DMA_CCR_MSIZE_1;
            break;
        
        default:
            break;
    }

    switch (periphsize)
    {
        case periphSize8bits:
            m_dmaChannel->CCR &= ~(DMA_CCR_PSIZE);
            break;

        case periphSize16Bits:
            m_dmaChannel->CCR &= ~(DMA_CCR_PSIZE);
            m_dmaChannel->CCR |= DMA_CCR_PSIZE_0;
            break;

        case periphSize32Bits:
            m_dmaChannel->CCR &= ~(DMA_CCR_PSIZE);
            m_dmaChannel->CCR |= DMA_CCR_PSIZE_1;
            break;
        
        default:
            break;
    }

    switch (meminc)
    {
        case memIncDisabled:
            m_dmaChannel->CCR &= ~(DMA_CCR_MINC);
            break;

        case memIncEnabled:
            m_dmaChannel->CCR |= DMA_CCR_MINC;
            break;
        
        default:
            break;
    }

    switch (periphinc)
    {
        case periphIncDisabled:
            m_dmaChannel->CCR &= ~(DMA_CCR_PINC);
            break;

        case periphIncEnabled:
            m_dmaChannel->CCR |= DMA_CCR_PINC;
            break;
        
        default:
            break;
    }

    switch (circmode)
    {
        case circModeDisabled:
            m_dmaChannel->CCR &= ~(DMA_CCR_CIRC);
            break;

        case circModeEnabled:
            m_dmaChannel->CCR |= DMA_CCR_CIRC;
            break;
        
        default:
            break;
    }

    switch (direction)
    {
        case readFromPeripheral:
            m_dmaChannel->CCR &= ~(DMA_CCR_DIR);
            break;

        case readFromMemory:
            m_dmaChannel->CCR |= DMA_CCR_DIR;
            break;
        
        default:
            break;
    }

    switch (completeinc)
    {
        case transferCompleteIntDisabled:
            m_dmaChannel->CCR &= ~(DMA_CCR_TCIE);
            break;

        case transferCompleteIntEnabled:
            m_dmaChannel->CCR |= DMA_CCR_TCIE;
            break;
        
        default:
            break;
    }
}

bool DmaChannel::transferCompleted()
{
    if (m_dmaController.getTransferStatusRegisters() & (1 << (0x00000002 << (m_channel - 1))))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DmaChannel::clearTransferRegisters()
{
    m_dmaController.clearHalfTransferStatusRegister(m_channel);
    m_dmaController.clearTransferErrorStatusRegister(m_channel);
    m_dmaController.clearTransfertCompleteStatusRegister(m_channel);
    m_dmaChannel->CCR &= ~(DMA_CCR_EN);
}

#ifndef DMA_H
#define DMA_H

#include <stdint.h>
#include <stm32f031x6.h>
#include "utils.h"


class Dma
{
    private:
        DMA_TypeDef* m_dmaPeripheral;

    public:
        Dma(DMA_TypeDef* periph) : m_dmaPeripheral(periph) { }

        void dmaSetup();
};

enum dmaChannelMem2MemSettings
{
    mem2MemEnabled,
    mem2MemDisabled,
};

enum dmaChannelPrioritysettings
{
    lowPriority,
    mediumPriority,
    highPriority,
    veryHighPriority,
};

enum dmaChannelMemorySizeSettings
{
    MemSize8bits,
    MemSize16Bits,
    MemSize32Bits,
};

enum dmaChannelPeripheralSizeSettings
{
    periphSize8bits,
    periphSize16Bits,
    periphSize32Bits,
};

enum dmaChannelMemoryIncreaseModeSettings
{
    memIncEnabled,
    memIncDisabled,
};

enum dmaChannelPeripheralIncreaseModeSettings
{
    periphIncEnabled,
    periphIncDisabled,
};

enum dmaChannelCircularModeSettings
{
    circModeEnabled,
    circModeDisabled,
};

enum dmaChannelDirectionSettings
{
    readFromMemory,
    readFromPeripheral,
};

enum dmaChannelTransferCompleteInterruptSettings
{
    transferCompleteIntEnabled,
    transferCompleteIntDisabled,
};

class DmaChannel
{
    private:
        DMA_Channel_TypeDef* m_dmaChannel;
        Dma m_dmaPeripheral;

    public:
        DmaChannel(DMA_Channel_TypeDef* channel, DMA_TypeDef* periph) : m_dmaChannel(channel), m_dmaPeripheral(periph) { }

        void dmaChannelSetup();
        void setDmaChannelSettings(dmaChannelMem2MemSettings = mem2MemDisabled, 
                                   dmaChannelPrioritysettings = lowPriority,
                                   dmaChannelMemorySizeSettings = MemSize8bits,
                                   dmaChannelPeripheralSizeSettings = periphSize8bits,
                                   dmaChannelMemoryIncreaseModeSettings = memIncDisabled,
                                   dmaChannelPeripheralIncreaseModeSettings = periphIncDisabled,
                                   dmaChannelCircularModeSettings = circModeDisabled,
                                   dmaChannelDirectionSettings = readFromPeripheral,
                                   dmaChannelTransferCompleteInterruptSettings = transferCompleteIntDisabled);
};

#endif
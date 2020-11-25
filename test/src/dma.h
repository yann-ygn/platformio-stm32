#ifndef DMA_H
#define DMA_H

#include <cstdint>
#include <stm32f031x6.h>
#include "utils.h"


class Dma
{
    private:
        DMA_TypeDef* m_dmaController;

    public:
        Dma(DMA_TypeDef* periph) : m_dmaController(periph) { }

        void dmaSetup();
        uint32_t getTransferStatusRegisters();
        void clearTransferErrorStatusRegister(uint8_t channel);
        void clearHalfTransferStatusRegister(uint8_t channel);
        void clearTransfertCompleteStatusRegister(uint8_t channel);
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
    memSize8bits,
    memSize16Bits,
    memSize32Bits,
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
        Dma m_dmaController;
        DMA_Channel_TypeDef* m_dmaChannel;
        uint8_t m_channel = 0;

    public:
        DmaChannel(DMA_TypeDef* periph, DMA_Channel_TypeDef* channel) : m_dmaController(periph), m_dmaChannel(channel) { }

        void dmaChannelSetup();
        void setDmaChannelSettings(dmaChannelDirectionSettings direction,
                                   dmaChannelPrioritysettings priority,
                                   dmaChannelMemorySizeSettings memsize,
                                   dmaChannelPeripheralSizeSettings periphsize,
                                   dmaChannelMemoryIncreaseModeSettings meminc,
                                   dmaChannelTransferCompleteInterruptSettings completeinc,
                                   dmaChannelPeripheralIncreaseModeSettings periphinc,
                                   dmaChannelMem2MemSettings mem2mem, 
                                   dmaChannelCircularModeSettings circmode);
        bool transferCompleted();
        void clearTransferRegisters();
};

#endif
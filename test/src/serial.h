#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stm32f031x6.h>
#include "utils.h"
#include "dma.h"

class Serial
{
    private:
        USART_TypeDef* m_usart;
        Pin m_rxPin;
        Pin m_txPin;
        DmaChannel* m_dmaTxChannel;
        uint32_t m_bauds;

    public:
        Serial(USART_TypeDef* usart, Bank* bank, uint8_t rx, uint8_t tx, gpioPinSetting settings, uint32_t bauds) : m_usart(usart), m_rxPin(bank, rx, settings), m_txPin(bank, tx, settings), m_bauds(bauds) { }

        void serialSetup();
        void enableDmaTx(DMA_TypeDef* periph, DMA_Channel_TypeDef* channel);
        void print(char* str);
};

#endif
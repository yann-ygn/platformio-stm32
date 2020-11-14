#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stm32f031x6.h>
#include "utils.h"

class Serial
{
    private:
        USART_TypeDef* m_usart;
        Pin m_rxPin;
        Pin m_txPin;
        uint32_t m_bauds;

    public:
        Serial(USART_TypeDef* usart, Bank* bank, uint8_t rx, uint8_t tx, gpioPinSetting settings, uint32_t bauds) : m_usart(usart), m_rxPin(bank, rx, settings), m_txPin(bank, tx, settings), m_bauds(bauds) { }

        void serialSetup();
};

#endif
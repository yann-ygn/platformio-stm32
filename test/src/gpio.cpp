#include <stdint.h>
#include "gpio.h"

void Bank::bankSetup()
{
    #ifdef GPIOA
    if (m_bank == GPIOA)
    {
        uint32_t bankStatus = RCC->AHBENR & RCC_AHBENR_GPIOAEN; // Get the clock status

        if (bankStatus != 0x20000) // 0x00020000 == enabled
        {
            RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
        }
    } 
    #endif

    #ifdef GPIOB
    if (m_bank == GPIOB)
    {
        uint32_t bankStatus = RCC->AHBENR & RCC_AHBENR_GPIOBEN; // Get the clock status

        if (bankStatus != 0x40000) // 0x00040000 == enabled
        {
            RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
        }
    } 
    #endif
}

void Bank::setPinMode(uint8_t pin, uint8_t mode)
{
    m_bank->MODER &= ~(0x3 << (pin * 2)); // Reset the register
    m_bank->MODER |= (mode << (pin * 2)); // Set the register
}

void Bank::setPinType(uint8_t pin, uint8_t otype)
{
    m_bank->OTYPER &= ~(0x1 << pin); // Reset the register
    m_bank->OTYPER |= (otype << pin); // Set the register
}

void Bank::setPinPud(uint8_t pin, uint8_t pud)
{
    m_bank->PUPDR &= ~(0x3 << (pin * 2)); // Reset the register
    m_bank->PUPDR |= (pud << (pin * 2)); // Set the register
}

void Bank::setPinSpeed(uint8_t pin, uint8_t ospeed)
{
    m_bank->OSPEEDR &= ~(0x3 << (pin * 2)); // Reset the register
    m_bank->OSPEEDR |= (ospeed << (pin * 2)); // Set the register
}

void Bank::setPinAlternateFunction(uint8_t pin, uint8_t af)
{
    if (pin < 8)
    {
        m_bank->AFR[0] &= ~(0xF << (pin * 4));
        m_bank->AFR[0] |= (af << (pin * 4));
    }

    else
    {
        m_bank->AFR[1] &= ~(0xF << ((pin - 8) * 4));
        m_bank->AFR[1] |= (af << ((pin - 8) * 4));
    }
}

void Bank::pinOn(uint8_t pin)
{
    m_bank->BSRR = (1 << pin);
}

void Bank::pinOff(uint8_t pin)
{
    m_bank->BSRR = (1 << (pin + 16));
}

uint32_t Bank::readPin(uint8_t pin)
{
    return (m_bank->IDR & (1 << pin));
}

void Pin::pinSetup()
{
    switch (m_pinSettings)
    {
        case pinInputFloating:
            m_pinBank->setPinMode(m_pin, GPIO_MODER_INPUT);
            m_pinBank->setPinPud(m_pin, GPIO_PUPDR_NONE);
            break;

        case pinInputPullDown:
            m_pinBank->setPinMode(m_pin, GPIO_MODER_INPUT);
            m_pinBank->setPinPud(m_pin, GPIO_PUPDR_DOWN);
            break;

        case pinInputPullUp:
            m_pinBank->setPinMode(m_pin, GPIO_MODER_INPUT);
            m_pinBank->setPinPud(m_pin, GPIO_PUPDR_UP);
            break;

        case pinOutputOpenDrain:
            m_pinBank->setPinMode(m_pin, GPIO_MODER_OUTPUT);
            m_pinBank->setPinType(m_pin, GPIO_OTYPER_OD);
            m_pinBank->setPinSpeed(m_pin, GPIO_OSPEEDR_LOW);
            m_pinBank->setPinPud(m_pin, GPIO_PUPDR_NONE);
            break;

        case pinOutputPushPull:
            m_pinBank->setPinMode(m_pin, GPIO_MODER_OUTPUT);
            m_pinBank->setPinType(m_pin, GPIO_OTYPER_PP);
            m_pinBank->setPinSpeed(m_pin, GPIO_OSPEEDR_LOW);
            m_pinBank->setPinPud(m_pin, GPIO_PUPDR_NONE);
            break;

        case pinAlternateFunctionPP:
            m_pinBank->setPinMode(m_pin, GPIO_MODER_AF);
            m_pinBank->setPinType(m_pin, GPIO_OTYPER_PP);
            m_pinBank->setPinSpeed(m_pin, GPIO_OSPEEDR_LOW);
            m_pinBank->setPinPud(m_pin, GPIO_PUPDR_NONE);
            break;

        case pinAlternateFunctionOD:
            m_pinBank->setPinMode(m_pin, GPIO_MODER_AF);
            m_pinBank->setPinType(m_pin, GPIO_OTYPER_OD);
            m_pinBank->setPinSpeed(m_pin, GPIO_OSPEEDR_LOW);
            m_pinBank->setPinPud(m_pin, GPIO_PUPDR_NONE);
            break;

        default:
            break;
    }
}

void Pin::setPinState(uint8_t state)
{
    if (state == 1)
    {
        m_pinBank->pinOn(m_pin);
    }
    else
    {
        m_pinBank->pinOff(m_pin);
    }

    m_pinState = state;
}

uint8_t Pin::getPinState()
{
    if (m_pinBank->readPin(m_pin) & (1 << m_pin))
    {
        m_pinState = 1;
    }
    else
    {
        m_pinState = 0;
    }

    return m_pinState;
}

void Pin::togglePinState()
{
    if (m_pinState == 1)
    {
        m_pinBank->pinOff(m_pin);
    }
    else
    {
        m_pinBank->pinOn(m_pin);
    }

    m_pinState = !m_pinState;
}

void Pin::setPinAlternateFunction(uint8_t af)
{
    m_pinBank->setPinAlternateFunction(m_pin, af);
}
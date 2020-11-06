#include <stdint.h>
#include "gpio.h"
void Bank::bankSetup()
{
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
    m_bank->MODER |= (mode << (pin *2)); // Set the register
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

        default:
            break;
    }
}

#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stm32f031x6.h>
#include "gpio.h"

/**
 * @brief Drives an LED, it can be turned on or off or have its state switched.
 */
class Led
{
    protected:
        Pin m_pin;
        uint8_t m_ledState = 0;
        uint32_t m_now = 0;
        uint32_t m_lastBlinkTime = 0;
        uint8_t m_lastBlinkState = 0;

    public:
        /**
         * @brief Construct a new Led object
         * 
         * @param pin LED pin #
         */
        Led(Bank* bank, uint8_t pin, gpioPinSetting settings) : m_pin(bank, pin, settings) { }

        /**
         * @brief Setup the µC's pins and set the LED to its startup state
         */
        void ledSetup();

        /**
         * @brief Turn the LED on
         */
        void ledTurnOn();

        /**
         * @brief Turn the LED off
         */
        void ledTurnOff();

        /**
         * @brief Set the LED to a desired state
         * 
         * @param state 
         */
        void ledSetState(uint8_t state);

        /**
         * @brief Switch the LED state off/on or on/off
         */
        void ledSwitchState();

        /**
         * @brief Blink an LED with a given inrterval
         * 
         * @param interval Interval in ms
         */
        void blinkLed(uint16_t interval);

        /**
         * @brief Get the Led State object
         * 
         * @return uint8_t 
         */
        uint8_t getLedState();

        /**
         * @brief Set the Led State object
         * 
         * @param state 
         */
        void setLedState(uint8_t state);
};

#endif
#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>
#include <stm32f031x6.h>
#include "gpio.h"

class TemporarySwitch
{
    private:
        Pin m_pin;

        uint8_t m_tempSwitchState = 0;
        uint8_t m_rawState = 0;
        uint8_t m_lasttempswithState = 0;
        uint8_t m_deglitchedState = 0;
        uint8_t m_debouncedState = 1;

        uint32_t m_now = 0;
        uint32_t m_deglitchTime = 0;
        uint32_t m_lastSwitchedTime = 0;
        uint32_t m_lastPushedTime = 0;
        const uint8_t m_deglitchPeriod = 30;
        const uint8_t m_debouncePeriod = 50;
        uint16_t m_longPressPeriod;

        uint8_t m_tempSwitchSwitched = 0;
        uint8_t m_tempSwitchLongPress = 0;
        uint8_t m_longPressActive = 0;


    public:
        TemporarySwitch(Bank* bank, uint8_t pin, gpioPinSetting settings, uint16_t lpperiod) : m_pin(bank, pin, settings), m_longPressPeriod(lpperiod)
        {

        };

        void tempSwitchSetup();

        void tempSwitchPoll();

        bool tempSwitchSwitched();

        bool tempSwitchOn();

        bool tempSwitchPushed();

        bool tempSwitchReleased();

        bool tempSwitchLongPress();

        uint32_t getLastPushedTime();

        void setLastPushedTime(uint32_t time);
};

#endif
#ifndef SWITCH_H
#define SWITCH_H

#include <cstdint>

#include "gpio.hpp"
#include "system.hpp"

namespace hal {
  class TemporarySwitch {
    public:
      TemporarySwitch() = default;

      void setupTempSwitch(Pin t_pin, uint16_t t_period);

      void pollTempSwitch();

      bool isSwitched();

      bool isPushed();

      bool isOn();

      bool isReleased();

      bool isLongPressed();

    private:
      Gpio m_gpio;

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
      uint16_t m_longPressPeriod = 0;

      uint8_t m_tempSwitchSwitched = 0;
      uint8_t m_tempSwitchLongPress = 0;
      uint8_t m_longPressActive = 0;
  };
} // namespace hal



#endif
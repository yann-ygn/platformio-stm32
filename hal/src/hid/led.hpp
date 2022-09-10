#ifndef HAL_LED_H_
#define HAL_LED_H_

#include <cstdint>

#include "per/gpio.hpp"
#include "sys/system.hpp"

namespace hal {
  /**
   * @brief Basic LED implementation, on/off/toggle
   */
  class Led {
    public:
      Led(const Pin& t_pin) : m_gpio(t_pin, GpioBase::OutputType::outputTypePp) {}

      /**
       * @brief Initialize the GPIO
       *
       * @param t_pin Pin # object
       */
      virtual void setupLed();

      /**
       * @brief Turn the LED on
       */
      void turnLedOn();

      /**
       * @brief Turn the LED off
       */
      void turnLedOff();

      /**
       * @brief Toggle the LED on/off
       */
      void toggleLedState();

      /**
       * @brief Blink the LED
       *
       * @param t_period Blinking period in ms
       */
      void blinkLed(uint16_t t_period);

    protected:
      GpioOutput m_gpio;
      uint8_t m_ledState = 0;
      uint32_t m_now = 0;
      uint32_t m_lastBlinkTime = 0;
      uint32_t m_lastBlinkState = 0;
  };
} // namespace hal

#endif // HAL_LED_H_
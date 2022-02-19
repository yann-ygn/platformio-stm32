#ifndef HAL_LED_H_
#define HAL_LED_H_

#include <cstdint>

#include "gpio.hpp"
#include "system.hpp"

namespace hal {
  /**
   * @brief Basic LED implementation, on/off/toggle
   */
  class Led {
    public:
      Led() = default;

      /**
       * @brief Initialize the GPIO
       *
       * @param t_pin Pin # object
       */
      virtual void setupLed(Pin t_pin);

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

    protected:
      Gpio m_gpio;
      uint8_t m_ledState = 0;
  };

  /**
   * @brief An LED that can also blink!
   */
  class BlinkingLed : public Led {
    public:
      /**
       * @brief Blink the LED
       *
       * @param t_period Blinking period in ms
       */
      void blinkLed(uint16_t t_period);

    private:
      uint32_t m_now = 0;
      uint32_t m_lastBlinkTime = 0;
      uint32_t m_lastBlinkState = 0;
  };
} // namespace hal

#endif // HAL_LED_H_
#ifndef HAL_LED_H_
#define HAL_LED_H_

#include <cstdint>

#include "gpio.hpp"

namespace hal {
  class Led {
    public:
      Led();

      /**
       * @brief Initialize the GPIO
       *
       * @param t_pin Pin # object
       */
      virtual void setupLed(Pin t_pin);

    protected:
      Gpio m_gpio;
      uint8_t m_ledState = 0;
  };
}

#endif // HAL_LED_H_
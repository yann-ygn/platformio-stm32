#ifndef HAL_UART_H_
#define HAL_UART_H_

#include <cstdint>

#include "stm32f031x6.h"
#include "gpio.hpp"

namespace hal {
  class Usart {
    public:
      /**
       * @brief Holds the configuration of the USART peripheral
       */
      struct Config {
        /**
         * @brief USART Peripheral
         */
        enum class Periph {
          Usart1,
          Usart2,
        };

        /**
         * @brief UART baud rate
         */
        enum class BaudRate {
          BaudRate9600,
        };

        Pin txpin;
        Pin rxpin;
        Periph periph;
        BaudRate baud;

        /**
         * @brief Constructor with no arguments defines an invalid USART object
         */
        Config() : txpin(),
                  rxpin(),
                  periph(Periph::Usart1),
                  baud(BaudRate::BaudRate9600) {}
      };

      Usart() = default;

      virtual void setupUsart(Pin t_txPin,
                              Pin t_rxPin,
                              Config::Periph t_periph = Config::Periph::Usart1,
                              Config::BaudRate t_baud = Config::BaudRate::BaudRate9600);

    private:
      Config m_cfg;

      USART_TypeDef *m_usartPeriph = nullptr;
  };
}

#endif
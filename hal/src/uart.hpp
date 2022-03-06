#ifndef HAL_UART_H_
#define HAL_UART_H_

#include <cstdint>

#include "stm32f031x6.h"
#include "system.hpp"
#include "gpio.hpp"

namespace hal {
  /**
   * @brief Very basic UART implementation using blocking RX/TX lines
   */
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

        enum class Mode {
          RxOnly,
          TxOnly,
          Bidirectionnal,
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
        Mode mode;
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
                              Config::Mode t_mode = Config::Mode::Bidirectionnal,
                              Config::BaudRate t_baud = Config::BaudRate::BaudRate9600);

      void test();

      bool isUsartDataAvailable() const;

      void printUsart(uint8_t t_data) const;

      uint8_t readUsart() const;

    private:
      Config m_cfg;

      USART_TypeDef *m_usartPeriph = nullptr;
      hal::Gpio m_gpioTx;
      hal::Gpio m_gpioRx;

      void getUsartPeriphAddress();

      void enableUsartPeriph() const;

      void enableUsart() const;

      void enableUsartTx() const;

      void enableUsartRx() const;

      void setUsartBrrRegister(uint16_t value) const;

      /**
       * @brief Read the RX Not Empty register
       *
       * @return uint32_t 0x20 if data is available
       */
      uint32_t getUsartRxneRegister() const;

      uint8_t getUsartRdrRegister() const;
  };
}

#endif
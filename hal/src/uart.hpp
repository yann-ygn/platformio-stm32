#ifndef HAL_UART_H_
#define HAL_UART_H_

#include <cstdint>

#include "stm32f031x6.h"
#include "system.hpp"
#include "gpio.hpp"
#include "circbuff.hpp"


namespace hal {
  /**
   * @brief Very basic UART implementation with no functionality
   */
  class Usart {
    public:
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
      enum class BaudRate : uint32_t {
        BaudRate9600 = 9600,
      };

      /**
       * @brief Holds the configuration of the USART peripheral
       */
      struct Config {
        Periph periph;
        Mode mode;
        BaudRate baud;

        /**
         * @brief Constructor with no arguments defines an invalid USART object
         */
        Config() :
          periph(Periph::Usart1),
          mode(Mode::Bidirectionnal),
          baud(BaudRate::BaudRate9600) {}

        Config(Periph t_periph, Mode t_mode, BaudRate t_baud) :
          periph(t_periph),
          mode(t_mode),
          baud(t_baud) {}
      };

      virtual void setupUsart() = 0;

    protected:
      CircBuff<uint8_t, 255> m_buffer;

      USART_TypeDef* m_usartPeriph = nullptr;

      GpioAlternateFunction m_gpioTx;
      GpioAlternateFunction m_gpioRx;

      Config m_cfg;

      //Usart(const Pin& t_txpin, const Pin& t_rxpin) :
      //  m_gpioTx(t_txpin, GpioBase::AlternadeFunction::noAlternateFunction, GpioBase::OutputType::outputTypePp),
      //  m_gpioRx(t_txpin, GpioBase::AlternadeFunction::noAlternateFunction, GpioBase::OutputType::outputTypePp) {}

      Usart(const Pin& t_txpin, const Pin& t_rxpin, Periph t_periph, Mode t_mode, BaudRate t_baud) :
        m_gpioTx(t_txpin, GpioBase::AlternadeFunction::noAlternateFunction, GpioBase::OutputType::outputTypePp),
        m_gpioRx(t_txpin, GpioBase::AlternadeFunction::noAlternateFunction, GpioBase::OutputType::outputTypePp),
        m_cfg(t_periph, t_mode, t_baud) {}

      void getUsartPeriphAddress();

      void enableUsartPeriph() const;

      void enableUsart() const;

      void enableUsartTx() const;

      void enableUsartRx() const;

      void setUsartBrrRegister(uint32_t value) const;

      /**
       * @brief Read the RX Not Empty register
       *
       * @return uint32_t 0x20 if data is available
       */
      uint32_t getUsartRxneRegister() const;

      uint8_t getUsartRdrRegister() const;
  };

  class UsartBlocking : public Usart {
    public:
      UsartBlocking(const Pin& t_txpin, const Pin& t_rxpin, Periph t_periph, Mode t_mode, BaudRate t_baud) :
        Usart(t_txpin, t_rxpin, t_periph, t_mode, t_baud) {}

      void setupUsart();

      bool isDataAvailable() const;

      void printUsart(uint8_t t_data) const;

      uint8_t readUsart() const;
  };
}

#endif
#include "uart.hpp"

using namespace hal;
/**
void Usart::setupUsart(Pin t_txPin,
                       Pin t_rxPin,
                       Config::Periph t_periph,
                       Config::Mode t_mode,
                       Config::BaudRate t_baud) {
  m_cfg.txpin = t_txPin;
  m_cfg.rxpin = t_rxPin;
  m_cfg.periph = t_periph;
  m_cfg.mode = t_mode;
  m_cfg.baud = t_baud;

  getUsartPeriphAddress();
  enableUsartPeriph();

  uint16_t baudRate = 0;
  uint32_t freq = System::getSysClockFrequency();

  switch (m_cfg.baud)
  {
    case Config::BaudRate::BaudRate9600: {
      baudRate = (freq / 9600);
      setUsartBrrRegister(baudRate);
      break;
    }

    default:
      break;
  }

  enableUsart();

  switch (m_cfg.periph)
  {
    case Config::Periph::Usart1: {
      // On the STM32F0x1 all the USART1 functions are on AF1

      if (m_cfg.mode == Config::Mode::RxOnly || m_cfg.mode == Config::Mode::Bidirectionnal) {
        m_gpioRx.setupGpio(m_cfg.rxpin,
                          Gpio::Config::Mode::modeAlternateFunction,
                          Gpio::Config::Pull::pullNoPull,
                          Gpio::Config::Speed::speedLow,
                          Gpio::Config::OutputType::outputTypePp,
                          Gpio::Config::AlternadeFunction::alternateFunction1);
        enableUsartRx();
      }

      if (m_cfg.mode == Config::Mode::TxOnly || m_cfg.mode == Config::Mode::Bidirectionnal) {
        m_gpioTx.setupGpio(m_cfg.txpin,
                          Gpio::Config::Mode::modeAlternateFunction,
                          Gpio::Config::Pull::pullNoPull,
                          Gpio::Config::Speed::speedLow,
                          Gpio::Config::OutputType::outputTypePp,
                          Gpio::Config::AlternadeFunction::alternateFunction1);

        enableUsartTx();
      }

      break;
    }

    default: break;
  }
}
**/

void Usart::getUsartPeriphAddress() {
  switch (m_cfg.periph)
  {
    case Periph::Usart1: m_usartPeriph = USART1; break;

    default: break;
  }
}

void Usart::enableUsartPeriph() const {
  // register APB2ENR
  // value << address
  // value : 0x0 = disable
  //         0x1  = enable
  // address : 1 << 14 (0x4000) = USART1EN = Enable USART1
  switch (m_cfg.periph)
  {
    case Periph::Usart1: RCC->APB2ENR |= RCC_APB2ENR_USART1EN; break;

    default: break;
  }
}

void Usart::enableUsart() const {
  // Register : UE
  // value << address
  // value : 0x1 = enable
  // address : 0
  m_usartPeriph->CR1 |= USART_CR1_UE;
}

void Usart::enableUsartTx() const {
  // Register : TE
  // value << address
  // value : 0x1 = enable
  // address : 3
  m_usartPeriph->CR1 |= USART_CR1_TE;
}

void Usart::enableUsartRx() const {
  // Register : RE
  // value << address
  // value : 0x1 = enable
  // address : 2
  m_usartPeriph->CR1 |= USART_CR1_RE;
}

void Usart::setUsartBrrRegister(uint16_t value) const {
  // Register : BRR
  // value
  m_usartPeriph->BRR = value;
}

uint32_t Usart::getUsartRxneRegister() const {
  // Register : RXNE
  // address : 5
  return m_usartPeriph->ISR & USART_ISR_RXNE;
}

void UsartPolling::setupUsart(Periph t_perih, Mode t_mode, BaudRate t_baud) {
  m_cfg.periph = t_perih;
  m_cfg.mode = t_mode;
  m_cfg.baud = t_baud;

  getUsartPeriphAddress();
  enableUsartPeriph();

  switch (m_cfg.baud)
  {
    case BaudRate::BaudRate9600: {
      uint16_t baudRate = ((System::getSysClockFrequency()) / 9600);
      setUsartBrrRegister(baudRate);
      break;
    }

    default:
      break;
  }
}

uint8_t Usart::getUsartRdrRegister() const {
  return m_usartPeriph->RDR;
}

bool UsartPolling::isDataAvailable() const {
  return (getUsartRxneRegister() & 0x20);
}

void UsartPolling::printUsart(uint8_t t_data) const {
  m_usartPeriph->TDR = t_data;
}

uint8_t UsartPolling::readUsart() const {
  return getUsartRdrRegister();
}
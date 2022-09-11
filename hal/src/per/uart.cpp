#include "uart.hpp"

using namespace hal;

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

void Usart::setUsartBrrRegister(uint32_t value) const {
  // Register : BRR
  // value
  m_usartPeriph->BRR = value;
}

uint32_t Usart::getUsartRxneRegister() const {
  // Register : RXNE
  // address : 5
  return m_usartPeriph->ISR & USART_ISR_RXNE;
}

void UsartBlocking::setupUsart() {
  getUsartPeriphAddress();
  enableUsartPeriph();
  setUsartBrrRegister(System::getSysClockFrequency() / uint32_t(m_cfg.baud));
  enableUsart();

  if (m_cfg.mode == Mode::RxOnly || m_cfg.mode == Mode::Bidirectionnal) {
    m_gpioRx.setAlternateFunction(GpioAlternateFunction::AlternadeFunction::alternateFunction1);
    m_gpioRx.setupGpio();
    enableUsartRx();
  }

  if (m_cfg.mode == Mode::TxOnly || m_cfg.mode == Mode::Bidirectionnal) {
    m_gpioTx.setAlternateFunction(GpioAlternateFunction::AlternadeFunction::alternateFunction1);
    m_gpioTx.setupGpio();
    enableUsartTx();
  }
}

uint8_t Usart::getUsartRdrRegister() const {
  return m_usartPeriph->RDR;
}

bool UsartBlocking::isDataAvailable() const {
  return (getUsartRxneRegister() & 0x20);
}

void UsartBlocking::printUsart(uint8_t t_data) const {
  m_usartPeriph->TDR = t_data;
}

uint8_t UsartBlocking::readUsart() const {
  return getUsartRdrRegister();
}
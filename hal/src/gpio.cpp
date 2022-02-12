#include "gpio.hpp"

using namespace hal;

void Gpio::setupGpio() {
  // Get the GPIO bank base adress
  getBasePortAddress();

  switch (m_cfg.mode)
  {
    case Config::Mode::modeInput: {
      setupGpioModeRegister();
      setupGpioPullRegister();
      break;
    }
    case Config::Mode::modeOutput: {
      setupGpioModeRegister();
      setupGpioOutputTypeRegister();
      setupGpioSpeedRegister();
      setupGpioPullRegister();
      break;
    }

    default: break;
  }
}

void Gpio::setupGpio(Pin t_pin, Config &t_cfg) {
  // Copy the config
  m_cfg = t_cfg;
  // Overwrite the pin
  m_cfg.pin = t_pin;

  // Check if the pin object is valid
  if (m_cfg.pin.isValid()) {
      // Setup the pin
      setupGpio();
  }
}

void Gpio::setupGpio(Pin t_pin, Config::Mode t_mode,
                    Config::Pull t_pull,
                    Config::Speed t_speed,
                    Config::OutputType t_otype) {
  // Populate the config object
  m_cfg.pin = t_pin;
  m_cfg.mode = t_mode;
  m_cfg.pull = t_pull;
  m_cfg.speed = t_speed;
  m_cfg.otype = t_otype;

  // Check if the pin object is valid
  if (m_cfg.pin.isValid()) {
    // Setup the pin
    setupGpio();
  }
}

void Gpio::getBasePortAddress() {
  switch (m_cfg.pin.port) {
    case GpioPort::gpioPortA: m_portAddress = GPIOA; break;
    case GpioPort::gpioPortB: m_portAddress = GPIOB; break;
    case GpioPort::gpioPortC: m_portAddress = GPIOC; break;
    case GpioPort::gpioPortF: m_portAddress = GPIOF; break;
    default: break;
  }
}

void Gpio::setupGpioModeRegister() const {
  // value << address
  // value : ~(0x3) = 00b clear the register
  //         0x0 = Input
  //         0x1 = Output
  //         0x2 = Alternate function
  //         0x3 = Analog
  // adress : pin number * 2 because each pin uses two bits
  m_portAddress->MODER &= ~(0x3 << (m_cfg.pin.pin * 2)); // Reset
  m_portAddress->MODER |= (uint8_t(m_cfg.mode) << (m_cfg.pin.pin * 2)); // Set
}

void Gpio::setupGpioPullRegister() const {
  // value << address
  // value : ~(0x3) = 00b clear the register
  //         0x0 = No pull up/down
  //         0x1 = Pull up
  //         0x2 = Pull down
  //         0x3 = Reserved
  // adress : pin number * 2 because each pin uses two bits
  m_portAddress->PUPDR &= ~(0x3 << (m_cfg.pin.pin * 2)); // Reset
  m_portAddress->PUPDR |= (uint8_t(m_cfg.pull) << (m_cfg.pin.pin * 2)); // Set
}

void Gpio::setupGpioSpeedRegister() const {
  // value << address
  // value : ~(0x3) = 00b clear the register
  //         0x0 = Low speed
  //         0x1 = Medium speed
  //         0x3 = High speed
  // adress : pin number * 2 because each pin uses two bits
  m_portAddress->OSPEEDR &= ~(0x3 << (m_cfg.pin.pin * 2)); // Reset
  m_portAddress->OSPEEDR |= (uint8_t(m_cfg.speed) << (m_cfg.pin.pin * 2)); // Set
}

void Gpio::setupGpioOutputTypeRegister() const {
  // value << address
  // value : ~(0x1) = 0b clear the register
  //         0x0 = Push pull
  //         0x1 = Open drain
  // adress : pin number * 1 because each pin uses one bit
  m_portAddress->OTYPER &= ~(0x1 << m_cfg.pin.pin); // Reset
  m_portAddress->OTYPER |= (uint8_t(m_cfg.otype) << m_cfg.pin.pin); // Set
}

void Gpio::setupGpioPortRegister() const
{
  #ifdef GPIOA
    if (m_portAddress == GPIOA) {
      // 0x00020000 == enabled
      if ((RCC->AHBENR & RCC_AHBENR_GPIOAEN) != 0x20000) {
        RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
      }
    }
  #endif
}
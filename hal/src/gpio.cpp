#include "gpio.hpp"

using namespace hal;

void GpioBase::setupGpio(Pin t_pin, Mode t_mode, Pull t_pull, Speed t_speed, OutputType t_otype, AlternadeFunction t_afunction) {
  // Populate the config object
  m_cfg.pin = t_pin;
  m_cfg.mode = t_mode;
  m_cfg.pull = t_pull;
  m_cfg.speed = t_speed;
  m_cfg.otype = t_otype;
  m_cfg.afunction = t_afunction;

  // Check if the pin object is valid
  if (m_cfg.pin.isValid()) {
    // Setup the pin
    getPortAddress();
    setupGpioPortRegister();

    switch (m_cfg.mode) {
      case Mode::modeInput: {
        setupModerRegister();
        setupPupdrRegister();
        break;
      }

      case Mode::modeOutput: {
        setupModerRegister();
        setupOtyperRegister();
        setupOspeedrRegister();
        setupPupdrRegister();
        break;
      }

      case Mode::modeAlternateFunction: {
        setupAfrRegister();
        setupOtyperRegister();
        setupOspeedrRegister();
        setupPupdrRegister();
        setupModerRegister();
        break;
      }

      default: break;
    }
  }
}

void GpioBase::setState(uint8_t t_state) const {
  setBssrRegister(t_state);
}

void GpioBase::setOn() const {
  setBssrRegister(1);
}

void GpioBase::setOff() const {
  setBssrRegister(0);
}

void GpioBase::toggleState() const {
  setBssrRegister(! getIdrRegister());
}

uint8_t GpioBase::getState() const {
  return getIdrRegister();
}

void GpioBase::getPortAddress() {
  switch (m_cfg.pin.port) {
    case GpioPort::portA: m_gpioPort = GPIOA; break;
    case GpioPort::portB: m_gpioPort = GPIOB; break;
    case GpioPort::portC: m_gpioPort = GPIOC; break;
    case GpioPort::portF: m_gpioPort = GPIOF; break;
    default: break;
  }
}

void GpioBase::setBssrRegister(uint8_t t_value) const {
  // value << address
  switch (t_value)
  {
    // 0x1 << pin
    // Set pin ON
    case 1: {
      m_gpioPort->BSRR = (1 << uint8_t(m_cfg.pin.pin));
      break;
    }

    // 0x1 << (pin + 16)
    // Set pin OFF
    case 0: {
      m_gpioPort->BSRR = (1 << (uint8_t(m_cfg.pin.pin) + 16));
      break;
    }

    default:
      break;
  }
}

uint8_t GpioBase::getIdrRegister() const {
  // register : IDR
  // value << address
  // value : 0x1 High
  if ((m_gpioPort->IDR & (0x1 << m_cfg.pin.pin)) == (uint32_t(0x1 << m_cfg.pin.pin))) {
    return 1;
  // value : 0x0 Low
  }
  else {
    return 0;
  }
}

void GpioBase::setupModerRegister() const {
  // register : MODER
  // value << address
  // value : ~(0x3) = 0b00 clear the register
  //         0x0 = Input
  //         0x1 = Output
  //         0x2 = Alternate function
  //         0x3 = Analog
  // adress : pin number * 2 because each pin uses two bits
  m_gpioPort->MODER &= ~(0x3 << (m_cfg.pin.pin * 2)); // Reset
  m_gpioPort->MODER |= (uint8_t(m_cfg.mode) << (m_cfg.pin.pin * 2)); // Set
}

void GpioBase::setupPupdrRegister() const {
  // register : PUPDR
  // value << address
  // value : ~(0x3) = 0b00 clear the register
  //         0x0 = No pull up/down
  //         0x1 = Pull up
  //         0x2 = Pull down
  //         0x3 = Reserved
  // adress : pin number * 2 because each pin uses two bits
  m_gpioPort->PUPDR &= ~(0x3 << (m_cfg.pin.pin * 2)); // Reset
  m_gpioPort->PUPDR |= (uint8_t(m_cfg.pull) << (m_cfg.pin.pin * 2)); // Set
}

void GpioBase::setupOspeedrRegister() const {
  // register : OSPEEDR
  // value << address
  // value : ~(0x3) = 0b00 clear the register
  //         0x0 = Low speed
  //         0x1 = Medium speed
  //         0x3 = High speed
  // adress : pin number * 2 because each pin uses two bits
  m_gpioPort->OSPEEDR &= ~(0x3 << (m_cfg.pin.pin * 2)); // Reset
  m_gpioPort->OSPEEDR |= (uint8_t(m_cfg.speed) << (m_cfg.pin.pin * 2)); // Set
}

void GpioBase::setupOtyperRegister() const {
  // register : OTYPER
  // value << address
  // value : ~(0x1) = 0b0 clear the register
  //         0x0 = Push pull
  //         0x1 = Open drain
  // adress : pin number * 1 because each pin uses one bit
  m_gpioPort->OTYPER &= ~(0x1 << m_cfg.pin.pin); // Reset
  m_gpioPort->OTYPER |= (uint8_t(m_cfg.otype) << m_cfg.pin.pin); // Set
}

void GpioBase::setupAfrRegister() const {
  // register : AFR[2]
  // register AFR[0] : low register pin 0-7
  // register AFR[1] : high register pin 8-15
  // value << address
  // value : ~(0xF) = 0b0000 clear the register
  //         0x0 = AF0
  //         0x1 = AF1
  //         0x2 = AF2
  //         0x3 = AF3
  //         0x4 = AF4
  //         0x5 = AF5
  //         0x6 = AF6
  //         0x7 = AF7
  //         0x8 = AF8
  // adress : pin < 8 = Low register = pin * 4 because each pin uses four bits
  // adress : pin > 8 = high register = (pin - 8) * 4 because each pin uses four bits and the register for pin 8 is bit 0-3
  if (m_cfg.pin.pin < 8) {
    m_gpioPort->AFR[0] &= ~(0xF << (m_cfg.pin.pin * 4)); // Reset
    m_gpioPort->AFR[0] |= (uint8_t(m_cfg.afunction) << (m_cfg.pin.pin * 4)); // Set
  }
  else {
    m_gpioPort->AFR[1] &= ~(0xF << ((m_cfg.pin.pin - 8) * 4)); // Reset
    m_gpioPort->AFR[1] |= (uint8_t(m_cfg.afunction) << ((m_cfg.pin.pin - 8) * 4)); // Set
  }
}

void GpioBase::setupGpioPortRegister() const {
  // register AHBENR
  // value << address
  // value : 0x0 = disable
  //         0x1  = enable
  // address : 1 << 17 (0x20000) = IOPAEN = Enable PORTA
  // address : 1 << 18 (0x40000) = IOPBEN = Enable PORTB
  #ifdef GPIOA
    if (m_gpioPort == GPIOA) {
      // 0x20000 == enabled
      if ((RCC->AHBENR & RCC_AHBENR_GPIOAEN) != 0x20000) {
        RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
      }
    }
  #endif

  #ifdef GPIOB
    if (m_gpioPort == GPIOB) {
      // 0x40000 == enabled
      if ((RCC->AHBENR & RCC_AHBENR_GPIOBEN) != 0x40000) {
        RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
      }
    }
  #endif
}
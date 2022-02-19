#include "led.hpp"

using namespace hal;

void Led::setupLed(Pin t_pin) {
  m_gpio.setupGpio(t_pin, Gpio::Config::Mode::modeOutput,
                  Gpio::Config::Pull::pullNoPull,
                  Gpio::Config::Speed::speedLow,
                  Gpio::Config::OutputType::outputTypePp);

  m_gpio.setGpioState(m_ledState);
}

void Led::turnLedOn() {
  m_ledState = 1;
  m_gpio.setGpioStateOn();
}

void Led::turnLedOff() {
  m_ledState = 0;
  m_gpio.setGpioStateOff();
}

void Led::toggleLedState() {
  m_ledState = !m_ledState;
  m_gpio.toggleGpioState();
}

void BlinkingLed::blinkLed(uint16_t t_period) {
  m_now = System::getNow();

  if ((m_now - m_lastBlinkTime) > t_period)
  {
    if (m_lastBlinkState)
    {
      m_lastBlinkState = 0;
      m_gpio.setGpioStateOff();
    }
    else
    {
      m_lastBlinkState = 1;
      m_gpio.setGpioStateOn();
    }

    m_lastBlinkTime = m_now;
  }
}
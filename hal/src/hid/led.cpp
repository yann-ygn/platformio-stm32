#include "led.hpp"

using namespace hal;

void Led::setupLed() {
  m_gpio.setupGpio();
  m_gpio.setState(m_ledState);
}

void Led::turnLedOn() {
  m_ledState = 1;
  m_gpio.setState(m_ledState);
}

void Led::turnLedOff() {
  m_ledState = 0;
  m_gpio.setState(m_ledState);
}

void Led::toggleLedState() {
  m_ledState = !m_ledState;
  m_gpio.setState(m_ledState);
}

void Led::blinkLed(uint16_t t_period) {
  m_now = System::getNow();

  if ((m_now - m_lastBlinkTime) > t_period)
  {
    if (m_lastBlinkState)
    {
      m_lastBlinkState = 0;
      m_gpio.setState(m_lastBlinkState);
    }
    else
    {
      m_lastBlinkState = 1;
      m_gpio.setState(m_lastBlinkState);
    }

    m_lastBlinkTime = m_now;
  }
}
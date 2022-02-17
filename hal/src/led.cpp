#include "led.hpp"

using namespace hal;

void Led::setupLed(Pin t_pin) {
  m_gpio.setupGpio(t_pin, Gpio::Config::Mode::modeOutput,
                  Gpio::Config::Pull::pullNoPull,
                  Gpio::Config::Speed::speedLow,
                  Gpio::Config::OutputType::outputTypePp);

  m_gpio.setGpioState(m_ledState);
}
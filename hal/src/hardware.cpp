#include "hardware.hpp"

using namespace hardware;

hal::System system;
hal::BlinkingLed led0;
hal::Usart serial;

void Hardware::setupHardware() {
  system.setupSytem();
}

void Hardware::setupTestStuff() {
  led0.setupLed(hardware::D13);
  serial.setupUsart(hardware::TX, hardware::RX,
                    hal::Usart::Config::Periph::Usart1,
                    hal::Usart::Config::Mode::Bidirectionnal,
                    hal::Usart::Config::BaudRate::BaudRate9600);
  serial.test();
}

void Hardware::doTestStuff() {
  led0.blinkLed(500);
}
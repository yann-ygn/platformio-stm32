#include "hardware.hpp"

using namespace hardware;

const size_t buffsize = 50;

hal::System system;
hal::BlinkingLed led0;
hal::Usart serial;
hal::CircBuff<uint8_t, buffsize> circbuff;

void Hardware::setupHardware() {
  system.setupSytem();
}

void Hardware::setupTestStuff() {
  led0.setupLed(hardware::D13);
  serial.setupUsart(hardware::TX, hardware::RX,
                    hal::Usart::Config::Periph::Usart1,
                    hal::Usart::Config::Mode::Bidirectionnal,
                    hal::Usart::Config::BaudRate::BaudRate9600);
}

void Hardware::doTestStuff() {
  if (serial.isUsartDataAvailable()) {
    circbuff.putItem(serial.readUsart());
    serial.printUsart(circbuff.getItem());
  }
  led0.blinkLed(500);
}
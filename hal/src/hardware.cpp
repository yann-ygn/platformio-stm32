#include "hardware.hpp"

using namespace hardware;

const size_t buffsize = 50;

hal::System system0;
hal::Led led0(D13);
hal::UsartBlocking serial0(TX, RX, hal::UsartBlocking::Periph::Usart1, hal::UsartBlocking::Mode::Bidirectionnal, hal::UsartBlocking::BaudRate::BaudRate9600);
hal::TemporarySwitch switch0(D6);
hal::CircBuff<uint8_t, 255> circbuff;

void testInterrupt() {
  led0.toggleLedState();
}

void Hardware::setupHardware() {
  system0.setupSytem();
}

void Hardware::setupTestStuff() {
  led0.setupLed();
  switch0.setupTempSwitch(1000);
  led0.turnLedOn();
  serial0.setupUsart();
  //hal::ExtiInterrupts.setupExternalInterrupt(D6, hal::InterruptTrigger::interruptTriggerFalling, 0, testInterrupt);
}

void Hardware::doTestStuff() {
  switch0.pollTempSwitch();
  if (switch0.isPushed()) {
    led0.toggleLedState();
    serial0.printUsart(97);
  }
  /**
  if (serial0.isDataAvailable()) {
    circbuff.putItem(serial0.readUsart());
    serial0.printUsart(circbuff.getItem());
  }
  **/
}
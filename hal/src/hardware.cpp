#include "hardware.hpp"

using namespace hardware;

hal::System system;
hal::BlinkingLed led0;

void Hardware::setupHardware() {
  system.setupSytem();
}

void Hardware::setupTestStuff() {
  led0.setupLed(hardware::D13);
}

void Hardware::doTestStuff() {
  led0.blinkLed(500);
}
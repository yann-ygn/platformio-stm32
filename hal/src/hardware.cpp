#include "hardware.hpp"

using namespace hardware;

hal::System system;

void Hardware::setupHardware() {
  system.setupSytem();
}
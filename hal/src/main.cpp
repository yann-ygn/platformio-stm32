#include "system.hpp"
#include "gpio.hpp"

int main(void) {
    hal::System hardware;
    hardware.setupSytem();
}
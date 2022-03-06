#ifndef HAL_HARDWARE_H_
#define HAL_HARDWARE_H_

#include <cstdint>
#include "system.hpp"
#include "gpio.hpp"
#include "led.hpp"
#include "uart.hpp"
#include "circbuff.hpp"

namespace hardware {
  // Pins definitions
  constexpr hal::Pin D0  = hal::Pin(hal::GpioPort::gpioPortA, 9);
  constexpr hal::Pin D1  = hal::Pin(hal::GpioPort::gpioPortA, 10);
  constexpr hal::Pin D2  = hal::Pin(hal::GpioPort::gpioPortA, 12);
  constexpr hal::Pin D3  = hal::Pin(hal::GpioPort::gpioPortB, 0);
  constexpr hal::Pin D4  = hal::Pin(hal::GpioPort::gpioPortB, 7);
  constexpr hal::Pin D5  = hal::Pin(hal::GpioPort::gpioPortB, 6);
  constexpr hal::Pin D6  = hal::Pin(hal::GpioPort::gpioPortB, 1);
  constexpr hal::Pin D7  = hal::Pin(hal::GpioPort::gpioPortF, 0);
  constexpr hal::Pin D8  = hal::Pin(hal::GpioPort::gpioPortF, 1);
  constexpr hal::Pin D9  = hal::Pin(hal::GpioPort::gpioPortA, 8);
  constexpr hal::Pin D10 = hal::Pin(hal::GpioPort::gpioPortA, 11);
  constexpr hal::Pin D11 = hal::Pin(hal::GpioPort::gpioPortB, 5);
  constexpr hal::Pin D12 = hal::Pin(hal::GpioPort::gpioPortB, 4);
  constexpr hal::Pin A7  = hal::Pin(hal::GpioPort::gpioPortA, 2);
  constexpr hal::Pin A6  = hal::Pin(hal::GpioPort::gpioPortA, 7);
  constexpr hal::Pin A5  = hal::Pin(hal::GpioPort::gpioPortA, 6);
  constexpr hal::Pin A4  = hal::Pin(hal::GpioPort::gpioPortA, 5);
  constexpr hal::Pin A3  = hal::Pin(hal::GpioPort::gpioPortA, 4);
  constexpr hal::Pin A2  = hal::Pin(hal::GpioPort::gpioPortA, 3);
  constexpr hal::Pin A1  = hal::Pin(hal::GpioPort::gpioPortA, 1);
  constexpr hal::Pin A0  = hal::Pin(hal::GpioPort::gpioPortA, 0);
  constexpr hal::Pin D13 = hal::Pin(hal::GpioPort::gpioPortB, 3);
  constexpr hal::Pin TX  = hal::Pin(hal::GpioPort::gpioPortA, 2);
  constexpr hal::Pin RX  = hal::Pin(hal::GpioPort::gpioPortA, 15);

  class Hardware {
    public:
      Hardware() = default;

      void setupHardware();

      void setupTestStuff();

      void doTestStuff();

    private:
  };
} // namespace hardware

#endif // HAL_HARDWARE_H_
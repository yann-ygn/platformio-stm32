#ifndef HAL_HARDWARE_H_
#define HAL_HARDWARE_H_

#include <cstdint>

#include "sys/system.hpp"
#include "sys/interrupts.hpp"
#include "per/gpio.hpp"
#include "per/uart.hpp"
#include "hid/led.hpp"
#include "hid/switch.hpp"
#include "util/circbuff.hpp"

namespace hardware {
  // Pins definitions
  constexpr hal::Pin D0  = hal::Pin(hal::GpioPort::portA, 9);
  constexpr hal::Pin D1  = hal::Pin(hal::GpioPort::portA, 10);
  constexpr hal::Pin D2  = hal::Pin(hal::GpioPort::portA, 12);
  constexpr hal::Pin D3  = hal::Pin(hal::GpioPort::portB, 0);
  constexpr hal::Pin D4  = hal::Pin(hal::GpioPort::portB, 7);
  constexpr hal::Pin D5  = hal::Pin(hal::GpioPort::portB, 6);
  constexpr hal::Pin D6  = hal::Pin(hal::GpioPort::portB, 1);
  constexpr hal::Pin D7  = hal::Pin(hal::GpioPort::portF, 0);
  constexpr hal::Pin D8  = hal::Pin(hal::GpioPort::portF, 1);
  constexpr hal::Pin D9  = hal::Pin(hal::GpioPort::portA, 8);
  constexpr hal::Pin D10 = hal::Pin(hal::GpioPort::portA, 11);
  constexpr hal::Pin D11 = hal::Pin(hal::GpioPort::portB, 5);
  constexpr hal::Pin D12 = hal::Pin(hal::GpioPort::portB, 4);
  constexpr hal::Pin A7  = hal::Pin(hal::GpioPort::portA, 2);
  constexpr hal::Pin A6  = hal::Pin(hal::GpioPort::portA, 7);
  constexpr hal::Pin A5  = hal::Pin(hal::GpioPort::portA, 6);
  constexpr hal::Pin A4  = hal::Pin(hal::GpioPort::portA, 5);
  constexpr hal::Pin A3  = hal::Pin(hal::GpioPort::portA, 4);
  constexpr hal::Pin A2  = hal::Pin(hal::GpioPort::portA, 3);
  constexpr hal::Pin A1  = hal::Pin(hal::GpioPort::portA, 1);
  constexpr hal::Pin A0  = hal::Pin(hal::GpioPort::portA, 0);
  constexpr hal::Pin D13 = hal::Pin(hal::GpioPort::portB, 3);
  constexpr hal::Pin TX  = hal::Pin(hal::GpioPort::portA, 2);
  constexpr hal::Pin RX  = hal::Pin(hal::GpioPort::portA, 15);

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
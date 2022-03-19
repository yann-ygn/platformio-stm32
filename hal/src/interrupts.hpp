#ifndef HAL_INTERRUPTS_H_
#define HAL_INTERRUPTS_H_

#include <functional>

#include "stm32f031x6.h"

#include "gpio.hpp"

namespace hal
{
  enum class InterruptTrigger {
    interruptTriggerNone,
    interruptTriggerRaising,
    interruptTriggerFalling,
    interruptTriggerBoth,
  };

  /**
   * @brief 
   */
  struct ExternalInterrupt {
    bool interruptActive = false;
    Pin gpioPin;
    InterruptTrigger interruptTrigger = InterruptTrigger::interruptTriggerNone;
    IRQn_Type interruptType = EXTI0_1_IRQn;
    uint8_t interruptPriority = 0;
    std::function<void()> interruptCallback;
  };

  struct PeripheralInterrupt {

  };

  /**
   * @brief Simple interface to setup an interrupt on a GPIO or a peripheral
   */
  class Interrupts {
    public:
      /**
       * @brief Holds the configuration for the interrupt
       */
      struct Config {
        /**
         * @brief 
         */
        enum class InterruptType {
          InterruptTypeExternal,
          InterruptTypePeripheral,
        };

        enum class InterruptPeripheral {
          InterruptPeripheralNone,
        };

        Pin pin;
        InterruptType type;
        InterruptPeripheral periph;
        InterruptTrigger trigger;
        uint8_t priority;
        std::function<void()> callback;

        Config() : pin(),
                   type(InterruptType::InterruptTypeExternal),
                   periph(InterruptPeripheral::InterruptPeripheralNone),
                   trigger(InterruptTrigger::interruptTriggerNone),
                   priority(0) {}
      };

      Interrupts() = default;

    private:
  };
} // namespace hal


#endif
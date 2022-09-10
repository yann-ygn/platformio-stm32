#ifndef HAL_INTERRUPTS_H_
#define HAL_INTERRUPTS_H_

#include <functional>

#include "stm32f031x6.h"

#include "per/gpio.hpp"

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
  struct ExternalInterruptSource {
    bool interruptActive = false;
    uint8_t interruptPort = 0;
    uint8_t interruptPin = 0;
    uint8_t interruptRegister = 0;
    uint8_t interruptRegisterOffset = 0;
    InterruptTrigger interruptTrigger = InterruptTrigger::interruptTriggerNone;
    IRQn_Type interruptType = EXTI0_1_IRQn;
    uint8_t interruptPriority = 0;
    std::function<void()> interruptCallback;

    void setupInterrupt();
  };

  /**
   * @brief Simple interface to setup an interrupt on a GPIO or a peripheral
   */
  class ExternalInterrupts {
    public:

      ExternalInterrupts() = default;

      static void setupExternalInterrupt(Pin t_pin, InterruptTrigger t_trigger, uint32_t t_priority, std::function<void()> t_callback);
  };

  static ExternalInterrupts ExtiInterrupts;
} // namespace hal


#endif
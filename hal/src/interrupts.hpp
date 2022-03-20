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
        enum class InterruptPeripheral {
          InterruptPeripheralNone,
        };

        Pin pin;
        InterruptPeripheral periph;
        InterruptTrigger trigger;
        uint32_t priority;
        std::function<void()> callback;

        Config() : pin(),
                   periph(InterruptPeripheral::InterruptPeripheralNone),
                   trigger(InterruptTrigger::interruptTriggerNone),
                   priority(0) {}
      };

      Interrupts() = default;

      void setupExternalInterrupt(Pin t_pin, InterruptTrigger t_trigger, uint32_t t_priority, std::function<void()> t_callback);
      void setupPeripheralInterrupt();

    private:
      Config m_cfg;
  };
} // namespace hal


#endif
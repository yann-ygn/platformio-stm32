#include "interrupts.hpp"

using namespace hal;

constexpr uint8_t extiLines = 16;

ExternalInterrupt *initExtiInterrupts() {
  // Blank object to initialize the actual interrupt object array
  ExternalInterrupt intr;

  // Create the object array and initialize it
  static ExternalInterrupt extiIntr[extiLines];
  for (uint8_t i = 0; i < extiLines; ++i) {
    extiIntr[i] = intr;
  }

  uint8_t exticrReg = 0; // SYSCFG->EXTICR[i] Register counter, 4 lines per
  uint8_t exticrOffset = 0; // Offset within the register, 4 bits per line
  for (uint8_t i = 0; i < extiLines; ++i) {
    extiIntr[i].interruptRegister = exticrReg;
    extiIntr[i].interruptRegisterOffset = exticrOffset * 4;

    // Max value for the register, switch to the next one
    if (++exticrOffset >= 4) {
      ++exticrReg;
      exticrOffset = 0;
    }
  }

  return extiIntr;
}

// Construct the external interrupts array
static ExternalInterrupt *extiInterrupts = initExtiInterrupts();

void ExternalInterrupt::setupInterrupt() {
  // register : EXTICR[i]
  // port << offset
  // port :  0x0 = GPIO PORT A
  //         0x1 = GPIO PORT B
  //         0x2 = GPIO PORT C
  //         0x3 = GPIO PORT D
  //         0x4 = GPIO PORT E
  //         0x5 = GPIO PORT F
  // offset : Offset within the register, a line uses 4 bits
  SYSCFG->EXTICR[interruptRegister] |= (interruptPort << interruptRegisterOffset);

  // register : EXTI_IMR
  // value << address
  // value :  0x0 = Mask request
  //          0x1 = Don't mask request
  // address : interrupt line = pin number
  EXTI->IMR |= (1 << interruptPin);

  // Setup the interrupt trigger type
  switch (interruptTrigger)
  {
    case InterruptTrigger::interruptTriggerRaising: {
      // register : EXTI_RTSR
      // value << address
      // value : ~(0x1) = 0b0 clear the register
      //         0x0 = Disable the raising trigger
      //         0x1 = Enable the raising trigger
      // address : interrupt line = pin number
      EXTI->RTSR |= (1 << interruptPin);

      // register : EXTI_FTSR
      // value << address
      // value : ~(0x1) = 0b0 clear the register
      //         0x0 = Disable the falling trigger
      //         0x1 = Enable the falling trigger
      // address : interrupt line = pin number
      EXTI->FTSR &= ~(1 << interruptPin);
      break;
    }

    case InterruptTrigger::interruptTriggerFalling: {
      EXTI->RTSR &= ~(1 << interruptPin);
      EXTI->FTSR |= (1 << interruptPin);
      break;
    }

    case InterruptTrigger::interruptTriggerBoth: {
      EXTI->RTSR |= (1 << interruptPin);
      EXTI->FTSR |= (1 << interruptPin);
      break;
    }

    default: break;
  }

  // Set the interrupt type value according to the pin #
  if (interruptPin == 0 || interruptPin == 1) {
    interruptType = EXTI0_1_IRQn;
  }
  else if (interruptPin == 2 || interruptPin == 3) {
    interruptType = EXTI2_3_IRQn;
  }
  else if (interruptPin > 3 && interruptPin < 16) {
    interruptType = EXTI4_15_IRQn;
  }

  // Set the priority and enable the interrupt
  NVIC_SetPriority(interruptType, interruptPriority);
  NVIC_EnableIRQ(interruptType);

  // Mark as active
  interruptActive = true;
}

// ISR definitions
extern "C" {
  // ISR for EXTI lines 0 and 1
  void EXTI0_1_IRQHandler(void) {
    // Check if line 1 or 0 received an event
    if (EXTI->PR & EXTI_PR_PR1) {
      EXTI->PR |= EXTI_PR_PR1; // Reset the pending register
      extiInterrupts[1].interruptCallback(); // Line 1 callback
    }
    else {
      EXTI->PR |= EXTI_PR_PR0; // Reset the pending register
      extiInterrupts[0].interruptCallback(); //  Line 0 callback
    }
  }

  // ISR for EXTI lines 2 and 3
  void EXTI2_3_IRQHandler(void) {
    // Check if line 2 or 3 received an event
    if (EXTI->PR & EXTI_PR_PR2) {
      EXTI->PR |= EXTI_PR_PR2; // Reset the pending register
      extiInterrupts[2].interruptCallback(); // Line 2 callback
    }
    else {
      EXTI->PR |= EXTI_PR_PR3; // Reset the pending register
      extiInterrupts[3].interruptCallback(); // Line 3 callback
    }
  }

  // ISR for EXTI lines 4 to 15
  void EXTI4_15_IRQHandler(void) {
    // Go thru each line and check if they received an event
    for (uint8_t i = 4; i < extiLines; ++i) {
      if (EXTI->PR & (1 << i)) {
        EXTI->PR |= (1 << i); // Reset the pending register
        extiInterrupts[i].interruptCallback(); // Line i callback
      }
    }
  }
}

void Interrupts::setupExternalInterrupt(Pin t_pin, InterruptTrigger t_trigger, uint32_t t_priority, std::function<void()> t_callback) {
  m_cfg.pin = t_pin;
  m_cfg.trigger = t_trigger;
  m_cfg.priority = t_priority;
  m_cfg.callback = t_callback;

  // Retrieve the underlying interrupt object
  ExternalInterrupt &extiIntr = extiInterrupts[m_cfg.pin.pin];

  // Set it up
  extiIntr.interruptPort = (uint32_t)m_cfg.pin.port;
  extiIntr.interruptPin = m_cfg.pin.pin;
  extiIntr.interruptTrigger = m_cfg.trigger;
  extiIntr.interruptPriority = m_cfg.priority;
  extiIntr.interruptCallback = m_cfg.callback;
  extiIntr.setupInterrupt();
}

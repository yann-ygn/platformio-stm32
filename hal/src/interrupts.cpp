#include "interrupts.hpp"

using namespace hal;

constexpr uint8_t extiLines = 16;

ExternalInterrupt *setupExtiInterrupts() {
  // Blank object to initialize the actual interrupt object array
  ExternalInterrupt intr;

  // Create the object array and initialize it
  static ExternalInterrupt extiIntr[extiLines];
  for (uint8_t i = 0; i < extiLines; ++i) {
    extiIntr[i] = intr;
  }

  return extiIntr;
}

static ExternalInterrupt *extiInterrupts = setupExtiInterrupts();

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

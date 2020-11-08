#include "main.h"


uint8_t led_on = 1;
extern "C" {
  void EXTI0_1_IRQ_handler(void) {
  // Check that EXTI1 (or 0?) is the line that triggered.
  if (EXTI->PR & (1 << BUTTON_PIN)) {
    // If it was, clear the interrupt flag.
    EXTI->PR |= (1 << BUTTON_PIN);

    // If you are using a button, toggle the LED state:
    led_on = !led_on;
    }
  }
}
  
/**
 * Main program.
 */
int main() {
  // Initialize global variables.

  // Enable the SYSCFG peripheral.
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  // Enable the GPIOB peripheral.
  RCC->AHBENR   |= RCC_AHBENR_GPIOBEN;
  // Initialize the GPIOB pins.
  // Reset all options, because the L0 lines reset to 0xFFFFFFFF.
  // B0-1 should be set to 'input' mode with pull-up.
  GPIOB->MODER  &= ~(0x3 << (BUTTON_PIN*2));
  GPIOB->PUPDR  &= ~(0x3 << (BUTTON_PIN*2));
  GPIOB->PUPDR  |=  (0x1 << (BUTTON_PIN*2));
  GPIOB->MODER  &= ~(0x3 << (ROTARY_PIN_B*2));
  GPIOB->PUPDR  &= ~(0x3 << (ROTARY_PIN_B*2));
  GPIOB->PUPDR  |=  (0x1 << (ROTARY_PIN_B*2));
  // B3 is connected to an LED on the 'Nucleo' board.
  //    It should be set to push-pull low-speed output.
  GPIOB->MODER  &= ~(0x3 << (LED_PIN*2));
  GPIOB->MODER  |=  (0x1 << (LED_PIN*2));
  GPIOB->OTYPER &= ~(0x1 << LED_PIN);
  GPIOB->PUPDR  &= ~(0x3 << (LED_PIN*2));

  // Set SYSCFG to connect the button EXTI line to GPIOB.
  SYSCFG->EXTICR[(BUTTON_PIN/4)] &= ~(0xF << ((BUTTON_PIN % 4) * 4));
  SYSCFG->EXTICR[(BUTTON_PIN/4)] |=  (0x1 << ((BUTTON_PIN % 4) * 4));
  // (Or, if you don't feel like using pin macros:)
  //SYSCFG->EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI1_Msk);
  //SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PB;
  // Setup EXTI interrupts for falling input on the button pin.
  EXTI->IMR |= (1 << BUTTON_PIN);
  // Disable the 'rising edge' trigger (button release).
  EXTI->RTSR &= ~(1 << BUTTON_PIN);
  // Enable the 'falling edge' trigger (button press).
  EXTI->FTSR |= (1 << BUTTON_PIN);
  // Enable the NVIC interrupt at minimum priority.
  NVIC_SetPriority(EXTI0_1_IRQn, 0x03);
  NVIC_EnableIRQ(EXTI0_1_IRQn);

  // Light the button only if it should be on.
  while (1) {
    if (led_on) {
      GPIOB->ODR |= (1 << LED_PIN);
    }
    else {
      GPIOB->ODR &= ~(1 << LED_PIN);
    }
  }
}

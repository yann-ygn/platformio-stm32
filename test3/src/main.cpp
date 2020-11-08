#include "main.h"


uint8_t led_on = 0;
uint8_t systick = 0;

uint16_t led_delay_count = 0;

void init_systick(void)
{
    int tick_time = 8000000/1000;       // Generate interrupt each 1 ms
    SysTick_Config(tick_time);                  // Configure systick timer
}

void SysTick_Handler(void)
{
    // update heartbeat LED delay counter and toggle state when needed
    led_delay_count = ( (led_delay_count + 1) % LED_DELAY_MS );
    if(led_delay_count == 0)
    {
        led_on = ! led_on;
    }
}

void EXTI0_1_IRQHandler(void) {
  // Check that EXTI1 (or 0?) is the line that triggered.
  if (EXTI->PR & (1 << BUTTON_PIN)) {
    // If it was, clear the interrupt flag.
    EXTI->PR |= (1 << BUTTON_PIN);

    // If you are using a button, toggle the LED state:
    led_on = !led_on;

    // If you are using a rotary encoder, turn the
    // LED on or off depending on the direction.
    // (Comment this out if using a single button)
    /**if (GPIOB->IDR & (1 << ROTARY_PIN_B)) {
      // Turn the LED on.
      led_on = 1;
    }
    else {
      // Turn the LED off.
      led_on = 0;
    }**/
  }
}

/**
 * Main program.
 */
int main(void) {
  int cpp_count = 0;
  int cpp_size = &(_epreinit_array[0]) - &(_spreinit_array[0]);
  for (cpp_count = 0; cpp_count < cpp_size; ++cpp_count) {
    _spreinit_array[cpp_count]();
  }
  // ('init_array' sections call static constructors)
  cpp_size = &(_einit_array[0]) - &(_sinit_array[0]);
  for (cpp_count = 0; cpp_count < cpp_size; ++cpp_count) {
    _sinit_array[cpp_count]();
  }

  init_systick();

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

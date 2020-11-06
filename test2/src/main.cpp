#include "main.h"
#include <stm32f030x6.h>

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

    class Gpio
    {
        private:
            uint8_t m_pin;

        public:
            Gpio(uint8_t pin) : m_pin(pin)
            {

            };

            void gpioSetup()
            {
                // Enable the GPIOB peripheral in 'RCC_AHBENR'.
                RCC->AHBENR   |= RCC_AHBENR_GPIOBEN;
                // Initialize the GPIOB pins.
                // B1 should be set to 'input' mode with pull-up.
                GPIOB->MODER  &= ~(0x3 << (m_pin*2));
                GPIOB->PUPDR  &= ~(0x3 << (m_pin*2));
                GPIOB->PUPDR  |=  (0x1 << (m_pin*2));
            }

            uint8_t getPin()
            {
                return m_pin;
            }
    };

    Gpio tempSwitch(4);
    tempSwitch.gpioSetup();
  
    // B3 is connected to an LED on the 'Nucleo' board.
    //    It should be set to push-pull low-speed output.
    GPIOB->MODER  &= ~(0x3 << (LED_PIN*2));
    GPIOB->MODER  |=  (0x1 << (LED_PIN*2)); 
    GPIOB->OTYPER &= ~(1 << LED_PIN);
    // Keep track of whether the button is pressed.
  uint8_t button_down = 0;
  while (1) {
    // Invert the IDR register since '0' means 'pressed'.
    uint32_t idr_val = ~GPIOB->IDR;
    if (idr_val & (1 << tempSwitch.getPin())) {
      // The button is pressed; if it was not already
      // pressed, change the LED state.
      if (!button_down) {
        GPIOB->ODR ^= (1 << LED_PIN);
      }
      button_down = 1;
    }
    else {
      button_down = 0;
    }
  }
}

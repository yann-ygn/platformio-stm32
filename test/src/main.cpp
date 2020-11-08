#include "main.h"
#include "gpio.h"
#include "utils.h"

#define LED_DELAY_MS        500

uint16_t led_delay_count = 0;
uint8_t led_on = 0;
uint32_t test = 0;

extern "C"
{
    void SysTick_Handler(void)
    {
        //led_delay_count = ( (led_delay_count + 1) % LED_DELAY_MS );
        //if(led_delay_count == 0)
        //{
        //    led_on = !led_on;
        //}

        Utils::incrementSysTick();
    }
}

/**
 * Main program.
 */
int main(void) 
{
    int cpp_count = 0;
    int cpp_size = &(_epreinit_array[0]) - &(_spreinit_array[0]);
    for (cpp_count = 0; cpp_count < cpp_size; ++cpp_count)
    {
        _spreinit_array[cpp_count]();
    }
    // ('init_array' sections call static constructors)
    cpp_size = &(_einit_array[0]) - &(_sinit_array[0]);
    for (cpp_count = 0; cpp_count < cpp_size; ++cpp_count)
    {
        _sinit_array[cpp_count]();
    }

    Utils::setClock();
    Utils::setSysTickTimer();

    Bank ledBank(GPIOB);
    ledBank.bankSetup();

    Pin ledPin(& ledBank, LED_PIN, pinOutputPushPull);
    ledPin.pinSetup();
    
    Pin buttonPin(& ledBank, BUTTON_PIN, pinInputPullUp);
    buttonPin.pinSetup();
    
  uint8_t button_down = 0;
  uint32_t lastLedTime = 0;
    while (1) 
    {
        if (! buttonPin.getPinState())
        {
            // The button is pressed; if it was not already
            // pressed, change the LED state.
            if (!button_down) 
            {
                led_on = !led_on;
            }

            button_down = 1;
        }
        else
        {
            button_down = 0;
        }

        if ((Utils::getSysTick() - lastLedTime) > 500)
        {
            led_on = !led_on;
            lastLedTime = Utils::getSysTick();
        }

        if (led_on) {
            GPIOB->ODR |= (1 << LED_PIN);
        }
        else {
            GPIOB->ODR &= ~(1 << LED_PIN);
        }
    }
}

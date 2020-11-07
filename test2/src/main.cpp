#include "main.h"
#include "gpio.h"

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
    
    Bank ledBank(GPIOB);
    ledBank.bankSetup();

    Pin ledPin(& ledBank, LED_PIN, pinOutputPushPull);
    ledPin.pinSetup();
    
    Pin buttonPin(& ledBank, BUTTON_PIN, pinInputPullUp);
    buttonPin.pinSetup();
    
  uint8_t button_down = 0;
    while (1) 
    {
        if (! buttonPin.getPinState())
        {
            // The button is pressed; if it was not already
            // pressed, change the LED state.
            if (!button_down) 
            {
                ledPin.togglePinState();
            }

            button_down = 1;
        }
        else
        {
            button_down = 0;
        }
    }
}

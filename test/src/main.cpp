#include "main.h"
#include "utils.h"
#include "hardware.h"
#include "gpio.h"
#include "switch.h"
#include "led.h"

int main(void) 
{
    Utils::setClock();
    Utils::setSysTickTimer();

    Bank ledBank(GPIOB);
    ledBank.bankSetup();

    TemporarySwitch tempSwitch(& ledBank, 1, pinInputPullUp, 500);
    tempSwitch.tempSwitchSetup();

    Led led(& ledBank, 3, pinOutputPushPull);
    led.ledSetup();
    
    while (1)
    {
        tempSwitch.tempSwitchPoll();
        led.blinkLed(500);

        if (tempSwitch.tempSwitchPushed())
        {
            led.ledSwitchState();
        }

        if (tempSwitch.tempSwitchLongPress())
        {
            led.ledSwitchState();
        }
    }
}

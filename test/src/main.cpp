#include "main.h"
#include "utils.h"
#include "hardware.h"
#include "serial.h"
#include "gpio.h"
#include "switch.h"
#include "led.h"
#include "dma.h"
#include "buffer.h"
#include "log.h"

int main(void) 
{
    Utils::clockSetup();
    Utils::setSysTickTimer();

    Bank bankA(GPIOA);
    bankA.bankSetup();
    Bank bankB(GPIOB);
    bankB.bankSetup();

    TemporarySwitch tempSwitch(& bankB, 1, pinInputPullUp, 500);
    tempSwitch.tempSwitchSetup();

    Led led(& bankB, 3, pinOutputPushPull);
    led.ledSetup();

    Serial serialPort1(USART1, & bankA, 15, 2, pinAlternateFunctionPP, 9600);
    serialPort1.serialSetup();
    serialPort1.enableDmaTx(DMA1, DMA1_Channel2);

    Logger log(& serialPort1, 63);

    CircularBuffer buffer(8);

    while (1)
    {
        tempSwitch.tempSwitchPoll();
        led.blinkLed(500);

        if (tempSwitch.tempSwitchPushed())
        {
            log.log("zert");
        }

        if (tempSwitch.tempSwitchLongPress())
        {
            led.ledSwitchState();
        }
    }
}

#include "main.h"
#include "utils.h"
#include "hardware.h"
#include "serial.h"
#include "gpio.h"
#include "switch.h"
#include "led.h"

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

    Serial serialPort1(USART1 ,& bankA, 15, 2, pinAlternateFunctionPP, 9600);
    serialPort1.serialSetup();

    RCC->AHBENR |= RCC_AHBENR_DMAEN;

    char rxb = '\0';

    while (1)
    {
        /**
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
        **/

        while( !( USART1->ISR & USART_ISR_RXNE ) ) {};
        rxb = USART1->RDR;

        while( !( USART1->ISR & USART_ISR_TXE ) ) {};
        USART1->TDR = rxb;
    }
}

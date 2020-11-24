#include "main.h"
#include "utils.h"
#include "hardware.h"
#include "serial.h"
#include "gpio.h"
#include "switch.h"
#include "led.h"
#include "dma.h"

#include <stdlib.h>
#include <stdarg.h>

size_t m_size = 5;
char m_buffer[5] = { 0 };
size_t m_read = 0;
size_t m_write = 0;

bool isEmpty()
{
    return (m_read == m_write);
}

void advance(size_t& value)
{
    value = (value + 1) % m_size;
}

void write(uint8_t item)
{
    m_buffer[m_write] = item;
    advance(m_write);
    if (isEmpty())
    {
        advance(m_read);
    }
}

char read()
{
    if (! isEmpty())
    {
        size_t oldRead = m_read;
        advance(m_read);
        return m_buffer[oldRead];
    }
}



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

    char test1 = 'a';
    char test2 = 'b';
    char test3 = 'c';
    char test4 = 'd';
    write(test1);
    write(test2);
    write(test3);
    write(test4);

    for (uint8_t i = 0; i < 7; i++)
    {
        char testout = read();
        serialPort1.print(&testout);
    }    

    while (1)
    {
        tempSwitch.tempSwitchPoll();
        led.blinkLed(500);

        if (tempSwitch.tempSwitchPushed())
        {
            serialPort1.print("Test test test !\r\n\0");
        }

        if (tempSwitch.tempSwitchLongPress())
        {
            led.ledSwitchState();
        }
    }
}

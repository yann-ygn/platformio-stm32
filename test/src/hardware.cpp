#include "hardware.h"

extern "C"
{
    void SysTick_Handler(void)
    {
        Utils::incrementSysTickCounter();
    }
}
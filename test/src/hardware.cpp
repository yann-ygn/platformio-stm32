#include "hardware.h"

extern "C"
{
    void SysTick_Handler(void)
    {
        Utils::incrementSysTickCounter();
    }

    void DMA1_Channel2_3_IRQHandler(void)
    {
        
    }
}


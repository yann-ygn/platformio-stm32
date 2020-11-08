#include "utils.h"

void Utils::setClock()
{
    FLASH->ACR &= ~(0x17); // Reset the Flash ACR register
    FLASH->ACR |= (FLASH_ACR_LATENCY | FLASH_ACR_PRFTBE); // Set the latency and prefecth buffer bit

    RCC->CFGR &= ~(RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC); // Reset the PLL
    RCC->CFGR |= (RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLMUL12); //

    RCC->CR |= (RCC_CR_PLLON); //
    while (! (RCC->CR & RCC_CR_PLLRDY)) { }

    RCC->CFGR &= ~(RCC_CFGR_SW);
    RCC->CFGR |= (RCC_CFGR_SW_PLL);
    while (! (RCC->CFGR & RCC_CFGR_SWS_PLL)) { }

    clockFrequency = 48000000;
}

void Utils::setSysTickTimer()
{
    SysTick->LOAD = ((clockFrequency / 1000) - 1);
    NVIC_SetPriority(SysTick_IRQn, 0x3);
    SysTick->VAL = 0;
    SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

void Utils::incrementSysTick()
{
    sysTick++;
}

uint32_t Utils::getSysTick()
{
    return sysTick;
}

#include "system.hpp"

using namespace hal;

extern "C" {
  // Systick interrupt handler
  void SysTick_Handler(void) {
    hal::System::incrementSystickCounter();
  }
}

uint32_t System::m_sysClockFrequency = 0;
uint32_t System::m_systickCounter = 0;

uint32_t System::getSysClockFrequency() {
  return m_sysClockFrequency;
}

void System::incrementSystickCounter() {
  ++m_systickCounter;
}

uint32_t System::getNow() {
  return m_systickCounter;
}

void System::setupSytem() {
  setupSystemClock();
  setupSystickCounter();
  setupSyscfgPeripheral();
}

void System::setupSystemClock() const {
  switch (m_config.sysClk) {
    case Config::SysClkFreq::FREQ_48MHZ: {
      // Set the clock at 48Mhz using the HSI into the PLL : (HSI/2)*12

      // Flash latency register needs to be set for a 48Mhz clock
      // Registers : ACR : 0x1 << 0 = One wait state
      //             PRFTBE : 0x1 << 4 = prefecth buffer enable
      // 0x17 = 0b10111 to clear both registers
      FLASH->ACR &= ~(0x17);
      // Set them
      FLASH->ACR |= (FLASH_ACR_LATENCY | FLASH_ACR_PRFTBE);

      // Registers : PLLSRC : 0x0 << 15 (0x0) = HSI/2
      //             PLLMUL : 0xA << 18 (0x280000) = Input clock *12
      // Clear the PLLMUL and PLLSRC registers
      RCC->CFGR &= ~(RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC);
      // Set them
      RCC->CFGR |= (RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLMUL12);

      // Enable the PLL
      // Registers : PLLON : 0x1 << 24 = PLL unlocked
      RCC->CR |= (RCC_CR_PLLON);
      // Wait for the PLL to be enabled
      while (! (RCC->CR & RCC_CR_PLLRDY)) {}

      // Set the SYSCLK source to the PLL
      // Registers : SW : 0x2 << 0 = Select the PLL
      // Clear the register
      RCC->CFGR &= ~(RCC_CFGR_SW);
      // Set it
      RCC->CFGR |= (RCC_CFGR_SW_PLL);
      // Wait for the clock to be started
      while (! (RCC->CFGR & RCC_CFGR_SWS_PLL)) {}

      m_sysClockFrequency = 48000000;
      break;
    }

    default:
      break;
  }
}

void System::setupSystickCounter() const {
  // Setup the systick to generate an interrupt every millisecond
  SysTick_Config(uint32_t(m_config.sysClk) / 1000);
}

void System::setupSyscfgPeripheral()  const {
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}
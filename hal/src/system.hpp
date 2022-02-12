#ifndef HAL_SYSTEM_H_
#define HAL_SYSTEM_H_

#include <cstdint>

#include "stm32f031x6.h"

namespace hal {
  class System {
    public:
      /**
       * @brief Holds the system configuration, clock settings and such
       */
      struct Config
      {
        /**
         * @brief Clock frenquency
         */
        enum class SysClkFreq : uint32_t
        {
            FREQ_48MHZ = 48000000,
        };

        SysClkFreq sysClk;

        /**
         * @brief Constructor with no arguments to hold the default configuration
         */
        Config() : sysClk(SysClkFreq::FREQ_48MHZ) {}
      };

      /**
       * @brief Static method to incrmeent the systick counter
       */
      static void incrementSystickCounter();

      /**
       * @brief Initialize the clock, systick
       */
      void setupSytem();

    private:
      Config m_config;

      // Holds the systick counter value
      static uint32_t m_systickCounter;

      /**
       * @brief Initialize the system clock
       */
      void setupSystemClock() const;

      /**
       * @brief Initialize the systick registers and interrupt
       */
      void setupSystickCounter() const;
  };
} // namespace hal

#endif // HAL_SYSTEM_H_
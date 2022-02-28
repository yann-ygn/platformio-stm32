#ifndef HAL_DMA_H_
#define HAL_DMA_H_

#include <cstdint>

#include "stm32f031x6.h"
#include "gpio.hpp"

namespace hal {
  class Usart {
    struct Config {
      enum class Periph {
        Usart1,
        Usart2,
      };

      Pin txPin;
      Pin rxPin;
    };
  };
}

#endif
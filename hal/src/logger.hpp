#pragma once

#include "cstdint"
#include "circbuff.hpp"
#include "uart.hpp"

namespace hal
{
  class Logger {
    public:
      enum class LogLevel {
        LogLevelTrace,
        LogLevelDebug,
        LogLevelInfo,
        LogLevelAction,
      };

      Logger() = default;

      void log()
    protected:
      CircBuff<uint8_t, 128> m_buffer;
  };
} // namespace hal

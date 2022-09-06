#pragma once

#include "cstdint"
#include "circbuff.hpp"
#include "uart.hpp"

namespace utils
{
  class LoggerUsart {
    public:
      enum class LogLevel {
        LogLevelTrace,
        LogLevelDebug,
        LogLevelInfo,
        LogLevelAction,
      };

      enum class LogType {
        LogTypeMessage,
        LogTypeAction,
      };

      static void setupLoggerUsart(hal::UsartBlocking* t_usart, LogLevel t_loglevel);

    private:
      static CircBuff<uint8_t, 128> m_buffer;
      static hal::UsartBlocking* m_usart;
      static uint8_t m_logLevel;
  };
} // namespace hal

#include "logger.hpp"

using namespace util;

hal::UsartBlocking* LoggerUsart::m_usart = nullptr;
LoggerUsart::LogLevel LoggerUsart::m_logLevel = LogLevel::LogLevelTrace;

void LoggerUsart::setupLoggerUsart(hal::UsartBlocking* t_usart, LogLevel t_loglevel) {
    m_usart = t_usart;
    m_logLevel = t_loglevel;
}
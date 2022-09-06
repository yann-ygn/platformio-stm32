#include "logger.hpp"

using namespace utils;

hal::UsartBlocking* LoggerUsart::m_usart = nullptr;
uint8_t LoggerUsart::m_logLevel = 0;

void LoggerUsart::setupLoggerUsart(hal::UsartBlocking* t_usart, LogLevel t_loglevel) {

}
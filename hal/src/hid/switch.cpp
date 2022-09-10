#include "switch.hpp"

using namespace hal;

void TemporarySwitch::setupTempSwitch(uint16_t t_period) {
  m_longPressPeriod = t_period;
  m_gpio.setupGpio();
}


void TemporarySwitch::pollTempSwitch() {
  m_tempSwitchState = m_gpio.getState();
  m_now = System::getNow();

  if (m_tempSwitchState == m_lasttempswithState) {
    m_rawState = 1;
  }
  else {
    m_rawState = 0;
    m_deglitchTime = m_now;
  }

  if (m_rawState && ((m_now - m_deglitchTime) > m_deglitchPeriod)) {
    m_deglitchedState = m_tempSwitchState;
    m_deglitchTime = m_now;
  }

  m_lasttempswithState = m_tempSwitchState;
  m_tempSwitchSwitched = 0;

  if ((m_deglitchedState != m_debouncedState) && (m_now - m_lastSwitchedTime) > m_debouncePeriod) {
    m_debouncedState = m_deglitchedState;
    m_tempSwitchSwitched = 1;
  }

  m_tempSwitchLongPress = 0;

  if (isReleased()) {
    m_longPressActive = false;
  }

  if (!m_longPressActive) {
    m_tempSwitchLongPress = !isSwitched() && isOn() && ((m_now - m_lastPushedTime) > m_longPressPeriod);
    m_longPressActive = m_tempSwitchLongPress;
  }

  if (isSwitched()) {
    m_lastSwitchedTime = m_now;

    if (isPushed()) {
      m_lastPushedTime = m_now;
    }
  }
}

bool TemporarySwitch::isSwitched() {
  return m_tempSwitchSwitched;
}

bool TemporarySwitch::isOn() {
  return !m_debouncedState;
}

bool TemporarySwitch::isPushed() {
  return m_tempSwitchSwitched && !m_debouncedState;
}

bool TemporarySwitch::isReleased() {
  return m_tempSwitchSwitched && m_debouncedState;
}

bool TemporarySwitch::isLongPressed() {
  return m_tempSwitchLongPress;
}
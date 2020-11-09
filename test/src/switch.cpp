#include "switch.h"

void TemporarySwitch::tempSwitchSetup()
{
    m_pin.pinSetup();
}


void TemporarySwitch::tempSwitchPoll()
{
    m_tempSwitchState = m_pin.getPinState();
    m_now = Utils::getSysTickCounter();

    if (m_tempSwitchState == m_lasttempswithState)
    {
        m_rawState = 1;
    }
    else
    {
        m_rawState = 0;
        m_deglitchTime = m_now;
    }
    
    if (m_rawState && ((m_now - m_deglitchTime) > m_deglitchPeriod))
    {
        m_deglitchedState = m_tempSwitchState;
        m_deglitchTime = m_now;
    }

    m_lasttempswithState = m_tempSwitchState;

    m_tempSwitchSwitched = 0;

    if ((m_deglitchedState != m_debouncedState) && (m_now - m_lastSwitchedTime) > m_debouncePeriod)
    {
        m_debouncedState = m_deglitchedState;
        m_tempSwitchSwitched = 1;
    }

    m_tempSwitchLongPress = 0;

    if (tempSwitchReleased())
    {
        m_longPressActive = false;

        #ifdef DEBUG
            Serial.print("tempSwitch ");
            Serial.print(m_pin);
            Serial.println(" released");
        #endif
    }

    if (!m_longPressActive)
    {
        m_tempSwitchLongPress = !tempSwitchSwitched() && tempSwitchOn() &&((m_now - m_lastPushedTime) > m_longPressPeriod);
        m_longPressActive = m_tempSwitchLongPress;

        #ifdef DEBUG
            if (tempSwitchLongPress())
            {
                Serial.print("tempSwitch ");
                Serial.print(m_pin);
                Serial.println(" long press");
            }
        #endif
    }

    if (tempSwitchSwitched())
    {
        m_lastSwitchedTime = m_now;

        #ifdef DEBUG
            Serial.print("tempSwitch ");
            Serial.print(m_pin);
            Serial.println(" switched");
        #endif

        if (tempSwitchPushed())
        {
            m_lastPushedTime = m_now;

            #ifdef DEBUG
                Serial.print("tempSwitch ");
                Serial.print(m_pin);
                Serial.println(" pushed");
            #endif
        }
    }
}

bool TemporarySwitch::tempSwitchSwitched()
{
    return m_tempSwitchSwitched;
}

bool TemporarySwitch::tempSwitchOn()
{
    return !m_debouncedState;
}

bool TemporarySwitch::tempSwitchPushed()
{
    return m_tempSwitchSwitched && !m_debouncedState;
}

bool TemporarySwitch::tempSwitchReleased()
{
    return m_tempSwitchSwitched && m_debouncedState;
}

bool TemporarySwitch::tempSwitchLongPress()
{
    return m_tempSwitchLongPress;
}

uint32_t TemporarySwitch::getLastPushedTime()
{
    return m_lastPushedTime;
}

void TemporarySwitch::setLastPushedTime(uint32_t time)
{
    m_lastPushedTime = time;
}
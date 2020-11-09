#include "led.h"

void Led::ledSetup()
{
    m_pin.pinSetup();
    m_pin.setPinState(m_ledState);
}

void Led::ledTurnOn()
{
    m_ledState = 1;
    m_pin.setPinState(m_ledState);

    #ifdef DEBUG
        Serial.print("LED ");
        Serial.print(m_pin);
        Serial.println(" on");
    #endif
}

void Led::ledTurnOff()
{
    m_ledState = 0;
    m_pin.setPinState(m_ledState);

    #ifdef DEBUG
        Serial.print("LED ");
        Serial.print(m_pin);
        Serial.println(" off");
    #endif
}

void Led::ledSetState(uint8_t state)
{
    m_ledState = state;
    m_pin.setPinState(m_ledState);

    #ifdef DEBUG
        Serial.print("LED ");
        Serial.print(m_pin);
        Serial.print(" switched state : ");
        Serial.println(m_ledState);
    #endif
}

void Led::ledSwitchState()
{
    m_ledState = !m_ledState;
    m_pin.setPinState(m_ledState);

    #ifdef DEBUG
        Serial.print("LED ");
        Serial.print(m_pin);
        Serial.print(" switched state : ");
        Serial.println(m_ledState);
    #endif
}

void Led::blinkLed(uint16_t interval)
{
    m_now = Utils::getSysTickCounter();

    if ((m_now - m_lastBlinkTime) > interval)
    {
        if (m_lastBlinkState)
        {
            m_lastBlinkState = 0;
            ledTurnOff();
        }
        else
        {
            m_lastBlinkState = 1;
            ledTurnOn();
        }

        m_lastBlinkTime = m_now;
    }
}

uint8_t Led::getLedState()
{
    return m_ledState;
}

void Led::setLedState(uint8_t state)
{
    m_ledState = state;
}

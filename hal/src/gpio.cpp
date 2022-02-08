#include "gpio.hpp"

using namespace hal;

void Gpio::setupGpio() {
    // Get the GPIO bank base adress
    getBasePortAddress();

    switch (m_cfg.mode)
    {
        case Mode::modeInput: {
            setupGpioModeRegister();
            setupGpioPullRegister();
            break;
        }
        case Mode::modeOutput: {
            setupGpioModeRegister();
            setupGpioOutputTypeRegister();
            setupGpioSpeedRegister();
            setupGpioPullRegister();
            break;
        }

        default: break;
    }
}

void Gpio::setupGpio(Pin t_pin, Config &t_cfg) {
    // Copy the config
    m_cfg = t_cfg;
    // Overwrite the pin
    m_cfg.pin = t_pin;

    // Check if the pin object is valid
    if (m_cfg.pin.isValid()) {
        // Setup the pin
        setupGpio();
    }
}

void Gpio::setupGpio(Pin t_pin, Mode t_mode, Pull t_pull, Speed t_speed, OutputType t_otype) {
    // Populate the config object
    m_cfg.pin = t_pin;
    m_cfg.mode = t_mode;
    m_cfg.pull = t_pull;
    m_cfg.speed = t_speed;
    m_cfg.otype = t_otype;

    // Check if the pin object is valid
    if (m_cfg.pin.isValid()) {
        // Setup the pin
        setupGpio();
    }
}

void Gpio::getBasePortAddress() {
    switch (m_cfg.pin.port)
    {
        case GpioPort::gpioPortA: m_portAddress = GPIOA; break;
        case GpioPort::gpioPortB: m_portAddress = GPIOB; break;
        case GpioPort::gpioPortC: m_portAddress = GPIOC; break;
        case GpioPort::gpioPortF: m_portAddress = GPIOF; break;
        default: break;
    }
}

void Gpio::setupGpioModeRegister()
{
    // value << address
    // value : ~(0x3) = 00b clear the register
    //         0x0 = Input
    //         0x1 = Output
    //         0x2 = Alternate function
    //         0x3 = Analog
    // adress : pin number * 2 because each pin uses two bits
    m_portAddress->MODER &= ~(0x3 << (m_cfg.pin.pin * 2));
    m_portAddress->MODER |= (uint8_t(m_cfg.mode) << (m_cfg.pin.pin * 2));
}
#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include <cstdint>

#include "stm32f031x6.h"

namespace hal {
  /**
   * @brief GPIO port names
   */
  enum class GpioPort {
    gpioPortA,
    gpioPortB,
    gpioPortC,
    gpioPortD,
    gpioPortX,
  };

  /**
   * @brief Representation of a hardware pin which is comprised of a port name and a pin number
   */
  struct Pin {
    GpioPort port;
    uint8_t pin;

    /**
     * @brief Construct a valid Pin object
     *
     * @param t_port Port name
     * @param t_pin Pin number
     */
    constexpr Pin(const GpioPort t_port, const uint8_t t_pin) : port(t_port), pin(t_pin) {}

    /**
     * @brief Construct an invalid Pin object
     */
    constexpr Pin() : port(GpioPort::gpioPortX), pin(255) {}

    /**
     * @brief Checks for the validity of a pin
     *
     * @return true if the pin is a combination of a valid port/pin
     */
    constexpr bool isValid() const { return port != GpioPort::gpioPortX && pin < 16; }
  };

  class Gpio {
   public:
    /**
     * @brief Mode of operation of the GPIO
     */
    enum class Mode {
      modeInput = 0x0,              // Input
      modeOutput = 0x1,             // Output PP
      modeOutputOd = 0x1,           // Output OD
      modeAlternateFunction = 0x2,  // Alternate function
      modeAnalog = 0x3,             // Analog
    };

    /**
     * @brief State of the internal pull up/down resistor
     */
    enum class Pull {
      pullNoPull = 0x0,
      pullPullUp = 0x1,
      pullPullDown = 0x2,
    };

    /**
     * @brief Output speed of the GPIO
     */
    enum class Speed {
      speedLow = 0x0,
      speedMed = 0x1,
      speedHigh = 0x2,
    };

    /**
     * @brief Output type of the GPIO
     */
    enum class OutputType {
      outputTypePp = 0x0,
      outputTypeOd = 0x1,
    };

    /**
     * @brief Holds the configuration for a GPIO
     */
    struct Config {
      Pin pin;
      Mode mode;
      Pull pull;
      Speed speed;

      /**
       * @brief Constructor with no arguments defines an invalid pin set to input with no pullup
       */
      Config() : pin(), mode(Mode::modeInput), pull(Pull::pullNoPull), speed(Speed::speedLow) {}
    };

    Gpio();

    void setupGpio(Config &t_cfg);

    void setupGpio(Pin t_pin, Config &t_cfg);

    void setupGpio(Pin t_pin, Mode t_mode = Mode::modeInput,
              Pull t_pull = Pull::pullNoPull,
              Speed t_speed = Speed::speedLow);

   private:
    Config m_cfg;
    GPIO_TypeDef *m_portAddress = nullptr;

    GPIO_TypeDef *getBasePortAddress();

    void setupGpioModeRegister();
    void setupGpioPullRegister();
    void setupGpioSpeedRegister();
    void setupGpioOutputTypeRegister();
    void setupGpioPortRegister();
  };
} // namespace hal

#endif  // HAL_GPIO_H_

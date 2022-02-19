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
    gpioPortF,
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
       * @brief Holds the configuration for a GPIO
       */
      struct Config {
        /**
         * @brief Mode of operation of the GPIO
         */
        enum class Mode: uint8_t {
          modeInput = 0x0,              // Input
          modeOutput = 0x1,             // Output PP
          modeAlternateFunction = 0x2,  // Alternate function
          modeAnalog = 0x3,             // Analog
        };

        /**
         * @brief State of the internal pull up/down resistor
         */
        enum class Pull: uint8_t {
          pullNoPull = 0x0,
          pullPullUp = 0x1,
          pullPullDown = 0x2,
        };

        /**
         * @brief Output speed of the GPIO
         */
        enum class Speed: uint8_t {
          speedLow = 0x0,
          speedMed = 0x1,
          speedHigh = 0x2,
        };

        /**
         * @brief Output type of the GPIO
         */
        enum class OutputType: uint8_t {
          outputTypePp = 0x0,
          outputTypeOd = 0x1,
        };

        Pin pin;
        Mode mode;
        Pull pull;
        Speed speed;
        OutputType otype;

        /**
         * @brief Constructor with no arguments defines an invalid pin set to input with no pullup
         */
        Config() : pin(), mode(Mode::modeInput), pull(Pull::pullNoPull), speed(Speed::speedLow), otype(OutputType::outputTypeOd) {}
      };

      Gpio() = default;

      void setupGpio();

      void setupGpio(Pin t_pin, Config &t_cfg);

      void setupGpio(Pin t_pin, Config::Mode t_mode = Config::Mode::modeInput,
                    Config::Pull t_pull = Config::Pull::pullNoPull,
                    Config::Speed t_speed = Config::Speed::speedLow,
                    Config::OutputType t_otype = Config::OutputType::outputTypeOd);

      /**
       * @brief Set the pin state
       *
       * @param state 1 : high | 0 : low
       */
      void setGpioState(uint8_t t_state) const;

      /**
       * @brief Set the GPIO high
       */
      void setGpioStateOn() const;

      /**
       * @brief Set the Gpio low
       */
      void setGpioStateOff() const;

      /**
       * @brief Toggle the Gpio state
       */
      void toggleGpioState() const;

      /**
       * @brief Get the gpio state
       *
       * @return uint8_t 1 : high | 0 : low
       */
      uint8_t getGpioState() const;

    private:
      Config m_cfg;
      uint8_t test = 0;

      // Low level address of the GPIO bank
      GPIO_TypeDef *m_portAddress = nullptr;

      /**
       * @brief Set the bit set/reset register to turn the gpio high/low
       *
       * @param t_value 1 : on | 0 : off
       */
      void setGpioBssrRegister(uint8_t t_value) const;

      /**
       * @brief Read the IDR register
       *
       * @return uint8_t Register value
       */
      uint8_t getGpioIdrRegister() const;

      /**
       * @brief Sets port address pointer according to the config pin object and the CMSIS header value
       */
      void getBasePortAddress();

      /**
       * @brief Set the GPIO MODER register according to the config pin object and mode value
       */
      void setupGpioModeRegister() const;

      /**
       * @brief Set the GPIO PUPDR register according to the config pin object and pull value
       */
      void setupGpioPullRegister() const;

      /**
       * @brief Set the GPIO SPEEDR register according to the config pin object and speed value
       */
      void setupGpioSpeedRegister() const;

      /**
       * @brief Set the GPIO OTYPER register according to the config pin object and otype value
       */
      void setupGpioOutputTypeRegister() const;

      /**
       * @brief Set the RCC_AHBENR register for the corresponding port according to the pin object
       */
      void setupGpioPortRegister() const;
  };
} // namespace hal

#endif  // HAL_GPIO_H_

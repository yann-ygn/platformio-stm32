#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include <cstdint>

#include "stm32f031x6.h"

#include "system.hpp"
#include "gpio.hpp"

namespace hal {
  /**
   * @brief GPIO port names
   */
  enum class GpioPort {
    portA,
    portB,
    portC,
    portF,
    portX,
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
    constexpr Pin() : port(GpioPort::portX), pin(255) {}

    /**
     * @brief Checks for the validity of a pin
     *
     * @return true if the pin is a combination of a valid port/pin
     */
    constexpr bool isValid() const { return port != GpioPort::portX && pin < 16; }
  };

  class GpioBase {
    public:
      /**
       * @brief Mode of operation of the GPIO
       */
      enum class Mode {
        modeInput,              // Input
        modeOutput,             // Output PP
        modeAlternateFunction,  // Alternate function
        modeAnalog,             // Analog
      };

      /**
       * @brief State of the internal pull up/down resistor
       */
      enum class Pull {
        noPull,
        pullUp,
        pullDown,
      };

      /**
       * @brief Output speed of the GPIO
       */
      enum class Speed {
        speedLow,
        speedMed,
        reserved,
        speedHigh,
      };

      /**
       * @brief Output type of the GPIO
       */
      enum class OutputType {
        outputTypePp,
        outputTypeOd,
      };

      /**
       * @brief Alternate function of the GPIO
       */
      enum class AlternadeFunction {
        alternateFunction0,
        alternateFunction1,
        alternateFunction2,
        alternateFunction3,
        alternateFunction4,
        alternateFunction5,
        alternateFunction6,
        alternateFunction7,
        noAlternateFunction,
      };

      /**
       * @brief Holds the configuration for a GPIO
       */
      struct Config {
        Pin pin;
        Mode mode;
        Pull pull;
        Speed speed;
        OutputType otype;
        AlternadeFunction afunction;

        /**
         * @brief Constructor with no arguments defines an invalid pin set to input with no pullup
         */
        Config() : pin(),
                  mode(Mode::modeInput),
                  pull(Pull::noPull),
                  speed(Speed::speedLow),
                  otype(OutputType::outputTypeOd),
                  afunction(AlternadeFunction::noAlternateFunction) {}
      };

      /**
      GpioBase() = default;

      void setupGpio(Pin t_pin,
                     Mode t_mode = Mode::modeInput,
                     Pull t_pull = Pull::noPull,
                     Speed t_speed = Speed::speedLow,
                     OutputType t_otype = OutputType::outputTypeOd,
                     AlternadeFunction t_afunction = AlternadeFunction::noAlternateFunction);
      **/

     GpioBase();

     virtual void setupGpio();

      /**
       * @brief Set the GPIO high
       */
      void setOn() const;

      /**
       * @brief Set the Gpio low
       */
      void setOff() const;

      /**
       * @brief Toggle the Gpio state
       */
      void toggleState() const;

      /**
       * @brief Set the pin state
       *
       * @param state 1 : high | 0 : low
       */
      void setState(uint8_t t_state) const;

      /**
       * @brief Get the gpio state
       *
       * @return uint8_t 1 : high | 0 : low
       */
      uint8_t getState() const;

    protected:
      Config m_cfg;

      // Low level address of the GPIO bank
      GPIO_TypeDef *m_gpioPort = nullptr;

      /**
       * @brief Set the bit set/reset register to turn the gpio high/low
       *
       * @param t_value 1 : on | 0 : off
       */
      void setBssrRegister(uint8_t t_value) const;

      /**
       * @brief Read the IDR register
       *
       * @return uint8_t Register value
       */
      uint8_t getIdrRegister() const;

      /**
       * @brief Sets port address pointer according to the config pin object and the CMSIS header value
       */
      void getPortAddress();

      /**
       * @brief Set the GPIO MODER register according to the config pin object and mode value
       */
      void setupModerRegister() const;

      /**
       * @brief Set the GPIO PUPDR register according to the config pin object and pull value
       */
      void setupPupdrRegister() const;

      /**
       * @brief Set the GPIO SPEEDR register according to the config pin object and speed value
       */
      void setupOspeedrRegister() const;

      /**
       * @brief Set the GPIO OTYPER register according to the config pin object and otype value
       */
      void setupOtyperRegister() const;

      /**
       * @brief Set the GPIO AFSEL register according to the config pin object and afunction value
       */
      void setupAfrRegister() const;

      /**
       * @brief Enable the GPIO port
       */
      void setupGpioPortRegister() const;
  };

  class GpioOutputPP : public GpioBase {
    public:
      GpioOutputPP();

      void setupGpio(Pin t_pin);
  };
} // namespace hal

#endif  // HAL_GPIO_H_

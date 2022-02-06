#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include <cstdint>

#include "stm32f031x6.h"

namespace hal {
  /**
   * @brief GPIO port names
   */
  enum class GpioPort {
    kPortA,
    kPortB,
    kPortC,
    kPortD,
    kPortX,
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
     * @param pt Port name
     * @param pn Pin number
     */
    constexpr Pin(const GpioPort pt, const uint8_t pn) : port(pt), pin(pn) {}

    /**
     * @brief Construct an invalid Pin object
     */
    constexpr Pin() : port(GpioPort::kPortX), pin(255) {}

    /**
     * @brief Checks for the validity of a pin
     *
     * @return true if the pin is a combination of a valid port/pin
     */
    constexpr bool isValid() const { return port != GpioPort::kPortX && pin < 16; }
  };

  class Gpio {
   public:
    /**
     * @brief Mode of operation of the GPIO
     */
    enum class Mode {
      kInput = 0x0,              // Input
      kOutput = 0x1,             // Output PP
      kOutputOd = 0x1,           // Output OD
      kAlternateFunction = 0x2,  // Alternate function
      kAnalog = 0x3,             // Analog
    };

    /**
     * @brief State of the internal pull up/down resistor
     */
    enum class Pull {
      kNoPull = 0x0,
      kPullUp = 0x1,
      kPullDown = 0x2,
    };

    /**
     * @brief Output speed of the GPIO
     */
    enum class Speed {
      kLow = 0x0,
      kMed = 0x1,
      kHigh = 0x2,
    };

    /**
     * @brief Output type of the GPIO
     */
    enum class OutputType {
      kPp = 0x0,
      kOd = 0x1,
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
      Config() : pin(), mode(Mode::kInput), pull(Pull::kNoPull), speed(Speed::kLow) {}
    };

    void init(Config &cfg);

    void init(Pin p, Config &cfg);

    void init(Pin p, Mode m = Mode::kInput, Pull pu = Pull::kNoPull, Speed sp = Speed::kLow);

   private:
    Config cfg_;
    GPIO_TypeDef *port_address_ = nullptr;

    GPIO_TypeDef *GetGPIOPortAddress();
  };
}

#endif  // HAL_GPIO_H_

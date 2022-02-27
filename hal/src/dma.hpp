#ifndef HAL_DMA_H_
#define HAL_DMA_H_

#include <cstdint>

#include "stm32f031x6.h"

namespace hal {
  /**
   * @brief Generic inteface for a DMA peripheral/channel, it support no transfer opeartions
   * and can only initialize the hardware
   */
  class Dma {
    public:
      /**
       * @brief Holds the configuration of the DMA channel
       */
      struct Config
      {
        /**
         * @brief DMA controller
         */
        enum class Controller {
          dmaController1,
          dmaController2,
        };

        /**
         * @brief DMA channel
         */
        enum class Channel {
          dmaChannel1,
          dmaChannel2,
          dmaChannel3,
          dmaChannel4,
          dmaChannel5,
        };

        /**
         * @brief Memory to memory mode
         */
        enum class MemToMem {
          memToMemDisabled,
          memToMemEnabled,
        };

        /**
         * @brief Channel priority level
         */
        enum class Priority {
          priorityLow,
          priorityMed,
          priorityHigh,
          priorityVeryHigh,
        };

        /**
         * @brief Memory size
         */
        enum class MemSize {
          memSize8Bits,
          memSize16Bits,
          memSize32Bits,
          reserved,
        };

        /**
         * @brief Peripheral size
         */
        enum class PeriphSize {
          periphSize8Bits,
          periphSize16Bits,
          periphSize32Bits,
          reserved,
        };

        /**
         * @brief Memory increment mode
         */
        enum class MemIncMode {
          memIncModeDisabled,
          memIncModeEnabled,
        };

        /**
         * @brief Peripheral increment mode
         */
        enum class PeriphIncMode {
          periphIncModeDisabled,
          periphIncModeEnabled,
        };

        /**
         * @brief Circular mode
         */
        enum class CircularMode {
          circularModeDisabled,
          circularModeEnabled,
        };

        /**
         * @brief Data transfer direction
         */
        enum class DataDirection {
          readFromPeriph,
          readFromMemory,
        };

        /**
         * @brief Transfer error interrupt
         */
        enum class TransferErrorInterrupt {
          teInterruptDisabled,
          teInterruptEnabled,
        };

        /**
         * @brief Half transfer interrupt
         */
        enum class HalfTransfertInterrupt {
          htInterruptDisabled,
          htInterruptEnabled,
        };

        /**
         * @brief Transfer complete interrupt
         */
        enum class TransferCompleteInterrupt {
          tcInterruptDisabled,
          tcInterruptEnabled,
        };

        Controller controller;
        Channel channel;
        MemToMem memtomem;
        Priority priority;
        MemSize memsize;
        PeriphSize periphsize;
        MemIncMode memincmode;
        PeriphIncMode periphincmode;
        CircularMode circularmode;
        DataDirection direction;
        TransferErrorInterrupt teinterrupt;
        HalfTransfertInterrupt htinterrupt;
        TransferCompleteInterrupt tcinterrupt;

        /**
         * @brief Constructor with no arguments defines an invalid dma object
         */
        Config() : controller(Controller::dmaController1),
                  channel(Channel::dmaChannel1),
                  memtomem(MemToMem::memToMemDisabled),
                  priority(Priority::priorityLow),
                  memsize(MemSize::memSize8Bits),
                  periphsize(PeriphSize::periphSize8Bits),
                  memincmode(MemIncMode::memIncModeDisabled),
                  periphincmode(PeriphIncMode::periphIncModeDisabled),
                  circularmode(CircularMode::circularModeDisabled),
                  direction(DataDirection::readFromPeriph),
                  teinterrupt(TransferErrorInterrupt::teInterruptDisabled),
                  htinterrupt(HalfTransfertInterrupt::htInterruptDisabled),
                  tcinterrupt(TransferCompleteInterrupt::tcInterruptDisabled) {}
      };

      Dma() = default;

      void setupDma();

      virtual void setupDma(Config::Controller t_controller,
                            Config::Channel t_channel,
                            Config::MemToMem t_memtomem = Config::MemToMem::memToMemDisabled,
                            Config::Priority t_priority = Config::Priority::priorityLow,
                            Config::MemSize t_memsize = Config::MemSize::memSize8Bits,
                            Config::PeriphSize t_periphsize = Config::PeriphSize::periphSize8Bits,
                            Config::MemIncMode t_memincmode = Config::MemIncMode::memIncModeDisabled,
                            Config::PeriphIncMode t_periphincmode = Config::PeriphIncMode::periphIncModeDisabled,
                            Config::CircularMode t_circularmode = Config::CircularMode::circularModeDisabled,
                            Config::DataDirection t_direction = Config::DataDirection::readFromPeriph,
                            Config::TransferErrorInterrupt t_teinterrupt = Config::TransferErrorInterrupt::teInterruptDisabled,
                            Config::HalfTransfertInterrupt t_htinterrupt = Config::HalfTransfertInterrupt::htInterruptDisabled,
                            Config::TransferCompleteInterrupt t_tcinterrupt = Config::TransferCompleteInterrupt::tcInterruptDisabled);

    private:
      Config m_cfg;

      // Memory address of the DMA controller
      DMA_TypeDef *m_dmaController = nullptr;
      // Memory address of the DMA channel
      DMA_Channel_TypeDef *m_dmaChannel = nullptr;

      /**
       * @brief Sets the controller address pointer according to the config object and the CMSIS header value
       */
      void getDmaControllerAddress();

      /**
       * @brief Sets the channel address pointer according to the config boject and the CMSIS header value
       */
      void getDmaChannelAddress();

      /**
       * @brief Enable the DMA channel
       */
      void enableDmaChannel() const;

      /**
       * @brief Disable the DMA channel
       */
      void disableDmaChannel() const;

      void setDmaMem2memRegister() const;

      void setDmaPriorityRegister() const;

      void setDmaMsizeRegister() const;

      void setDmaPsizeRegister() const;

      void setDmaMincRegister() const;

      void setDmaPincRegister() const;

      void setDmaCircRegister() const;

      void setDmaDirRegister() const;

      void setDmaTeieRegister() const;

      void setDmaHtieRegister() const;

      void setDmaTcieRegister() const;

      void setDmaCmarRegister(uint32_t *address) const;

      void setDmaCparRegister(uint32_t *address) const;

      void setDmaCndtrRegister(uint16_t length) const;
  };
} // namespace hal

#endif // HAL_DMA_H_
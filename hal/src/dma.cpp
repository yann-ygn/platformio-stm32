#include "dma.hpp"

using namespace hal;

void Dma::setupDma() {

}

void Dma::setupDma(Config::Controller t_controller,
                  Config::Channel t_channel,
                  Config::MemToMem t_memtomem,
                  Config::Priority t_priority,
                  Config::MemSize t_memsize,
                  Config::PeriphSize t_periphsize,
                  Config::MemIncMode t_memincmode,
                  Config::PeriphIncMode t_periphincmode,
                  Config::CircularMode t_circularmode,
                  Config::DataDirection t_direction,
                  Config::TransferErrorInterrupt t_teinterrupt,
                  Config::HalfTransfertInterrupt t_htinterrupt,
                  Config::TransferCompleteInterrupt t_tcinterrupt) {
  // Populate the config object
  m_cfg.controller = t_controller;
  m_cfg.channel = t_channel;
  m_cfg.memtomem = t_memtomem;
  m_cfg.priority = t_priority;
  m_cfg.memsize = t_memsize;
  m_cfg.periphsize = t_periphsize;
  m_cfg.memincmode = t_memincmode;
  m_cfg.periphincmode = t_periphincmode;
  m_cfg.circularmode = t_circularmode;
  m_cfg.direction = t_direction;
  m_cfg.teinterrupt = t_teinterrupt;
  m_cfg.htinterrupt = t_htinterrupt;
  m_cfg.tcinterrupt = t_tcinterrupt;

  setupDma();
}

void Dma::getDmaControllerAddress() {
  switch (m_cfg.controller)
  {
    case Config::Controller::dmaController1: m_dmaController = DMA1; break;
    // case Config::Controller::dmaController2: m_dmaController = DMA1; break;
    default: break;
  }
}

void Dma::getDmaChannelAddress() {
  switch (m_cfg.controller)
  {
    case Config::Controller::dmaController1: {
      switch (m_cfg.channel)
      {
        case Config::Channel::dmaChannel1: m_dmaChannel = DMA1_Channel1; break;
        case Config::Channel::dmaChannel2: m_dmaChannel = DMA1_Channel2; break;
        case Config::Channel::dmaChannel3: m_dmaChannel = DMA1_Channel3; break;
        case Config::Channel::dmaChannel4: m_dmaChannel = DMA1_Channel4; break;
        case Config::Channel::dmaChannel5: m_dmaChannel = DMA1_Channel5; break;
        default: break;
      }

      break;
    }

    case Config::Controller::dmaController2: {

      break;
    }

    default:
      break;
  }
}

void Dma::enableDmaChannel() const {
  // Register : EN
  // value << address
  // value : 0x1 = enable
  // address : 0
  m_dmaChannel->CCR |= DMA_CCR_EN;
}

void Dma::disableDmaChannel() const {
  // Register : EN
  // value << address
  // value : ~(0x1) = 0b0 = disable
  // address : 0
  m_dmaChannel->CCR &= ~(DMA_CCR_EN);
}

void Dma::setDmaMem2memRegister() const {
  // Register : MEM2MEM
  // value << address
  // value : ~(0x1) = 0b0 = disable
  //         0x1 = enable
  // address : 14
  switch (m_cfg.memtomem) {
    case Config::MemToMem::memToMemDisabled: m_dmaChannel->CCR &= ~(DMA_CCR_MEM2MEM); break;
    case Config::MemToMem::memToMemEnabled: m_dmaChannel->CCR |= (DMA_CCR_MEM2MEM); break;
    default: break;
  }
}

void Dma::setDmaPriorityRegister() const {
  // register : PL
  // value << address
  // value : ~(0x3) = 0b00 clear the register
  //         0x0 = Low
  //         0x1 = Medium
  //         0x2 = High
  //         0x3 = Very high
  // adress : 12
  switch (m_cfg.priority) {
    case Config::Priority::priorityLow: m_dmaChannel->CCR &= ~(DMA_CCR_PL); // Reset
        break;

    case Config::Priority::priorityMed: {
      m_dmaChannel->CCR &= ~(DMA_CCR_PL); // Reset
      m_dmaChannel->CCR |= DMA_CCR_PL_0; // Set
      break;
    }

    case Config::Priority::priorityHigh: {
      m_dmaChannel->CCR &= ~(DMA_CCR_PL); // Reset
      m_dmaChannel->CCR |= DMA_CCR_PL_1; // Set
      break;
    }

    case Config::Priority::priorityVeryHigh: m_dmaChannel->CCR |= DMA_CCR_PL; break; // Set

    default:
      break;
  }
}

void Dma::setDmaMsizeRegister() const {
  // register : MSIZE
  // value << address
  // value : ~(0x3) = 0b00 clear the register
  //         0x0 = 8 bits
  //         0x1 = 16 bits
  //         0x2 = 32 bits
  //         0x3 = Reserved
  // adress : 10
  switch (m_cfg.memsize) {
    case Config::MemSize::memSize8Bits: m_dmaChannel->CCR &= ~(DMA_CCR_MSIZE); break; // Reset

    case Config::MemSize::memSize16Bits: {
      m_dmaChannel->CCR &= ~(DMA_CCR_MSIZE); // Reset
      m_dmaChannel->CCR |= DMA_CCR_MSIZE_0; // Set
      break;
    }

    case Config::MemSize::memSize32Bits: {
      m_dmaChannel->CCR &= ~(DMA_CCR_MSIZE); // Reset
      m_dmaChannel->CCR |= DMA_CCR_MSIZE_1; // Set
      break;
    }

    default:
      break;
    }
}

void Dma::setDmaPsizeRegister() const {
  // register : PSIZE
  // value << address
  // value : ~(0x3) = 0b00 clear the register
  //         0x0 = 8 bits
  //         0x1 = 16 bits
  //         0x2 = 32 bits
  //         0x3 = Reserved
  // adress : 8
  switch (m_cfg.periphsize) {
    case Config::PeriphSize::periphSize8Bits: m_dmaChannel->CCR &= ~(DMA_CCR_PSIZE); break; // Reset

    case Config::PeriphSize::periphSize16Bits: {
      m_dmaChannel->CCR &= ~(DMA_CCR_PSIZE); // Reset
      m_dmaChannel->CCR |= DMA_CCR_PSIZE_0; // Set
      break;
    }

    case Config::PeriphSize::periphSize32Bits: {
      m_dmaChannel->CCR &= ~(DMA_CCR_PSIZE); // Reset
      m_dmaChannel->CCR |= DMA_CCR_PSIZE_1; // Set
      break;
    }

    default:
      break;
    }
}

void Dma::setDmaMincRegister() const {
  // Register : MINC
  // value << address
  // value : ~(0x1) = 0b0 = disable
  //         0x1 = enable
  // address : 7
  switch (m_cfg.memincmode)
  {
    case Config::MemIncMode::memIncModeDisabled: m_dmaChannel->CCR &= ~(DMA_CCR_MINC); break;
    case Config::MemIncMode::memIncModeEnabled: m_dmaChannel->CCR |= DMA_CCR_MINC; break;

    default:
      break;
  }
}

void Dma::setDmaPincRegister() const {
  // Register : PINC
  // value << address
  // value : ~(0x1) = 0b0 = disable
  //         0x1 = enable
  // address : 6
  switch (m_cfg.periphincmode)
  {
    case Config::PeriphIncMode::periphIncModeDisabled: m_dmaChannel->CCR &= ~(DMA_CCR_PINC); break;
    case Config::PeriphIncMode::periphIncModeEnabled: m_dmaChannel->CCR |= DMA_CCR_PINC; break;

    default:
      break;
  }
}

void Dma::setDmaCircRegister() const {
  // Register : CIRC
  // value << address
  // value : ~(0x1) = 0b0 = disable
  //         0x1 = enable
  // address : 5
  switch (m_cfg.circularmode)
  {
    case Config::CircularMode::circularModeDisabled: m_dmaChannel->CCR &= ~(DMA_CCR_CIRC); break;
    case Config::CircularMode::circularModeEnabled: m_dmaChannel->CCR |= DMA_CCR_CIRC; break;

    default:
      break;
  }
}

void Dma::setDmaDirRegister() const {
  // Register : DIR
  // value << address
  // value : ~(0x1) = 0b0 = disable
  //         0x1 = enable
  // address : 4
  switch (m_cfg.direction)
  {
    case Config::DataDirection::readFromPeriph: m_dmaChannel->CCR &= ~(DMA_CCR_DIR); break;
    case Config::DataDirection::readFromMemory: m_dmaChannel->CCR |= DMA_CCR_DIR; break;

    default:
      break;
  }
}

void Dma::setDmaTeieRegister() const {
  // Register : TEIE
  // value << address
  // value : ~(0x1) = 0b0 = disable
  //         0x1 = enable
  // address : 3
  switch (m_cfg.teinterrupt)
  {
    case Config::TransferErrorInterrupt::teInterruptDisabled: m_dmaChannel->CCR &= ~(DMA_CCR_TEIE); break;
    case Config::TransferErrorInterrupt::teInterruptEnabled: m_dmaChannel->CCR |= DMA_CCR_TEIE; break;

    default:
      break;
  }
}

void Dma::setDmaHtieRegister() const {
  // Register : HTIE
  // value << address
  // value : ~(0x1) = 0b0 = disable
  //         0x1 = enable
  // address : 2
  switch (m_cfg.htinterrupt)
  {
    case Config::HalfTransfertInterrupt::htInterruptDisabled: m_dmaChannel->CCR &= ~(DMA_CCR_HTIE); break;
    case Config::HalfTransfertInterrupt::htInterruptEnabled: m_dmaChannel->CCR |= DMA_CCR_HTIE; break;

    default:
      break;
  }
}

void Dma::setDmaTcieRegister() const {
  // Register : TCIE
  // value << address
  // value : ~(0x1) = 0b0 = disable
  //         0x1 = enable
  // address : 1
  switch (m_cfg.tcinterrupt)
  {
    case Config::TransferCompleteInterrupt::tcInterruptDisabled: m_dmaChannel->CCR &= ~(DMA_CCR_TCIE); break;
    case Config::TransferCompleteInterrupt::tcInterruptEnabled: m_dmaChannel->CCR |= DMA_CCR_TCIE; break;

    default:
      break;
  }
}

void Dma::setDmaCmarRegister(uint32_t *address) const {
  // Register : CMAR
  // value : Memory address
  m_dmaChannel->CMAR = address;
}

void Dma::setDmaCparRegister(uint32_t *address) const {
  // Register : CMAR
  // value : Memory address
  m_dmaChannel->CPAR = address;
}
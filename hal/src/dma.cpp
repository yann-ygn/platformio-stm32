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
    case Config::Controller::dmaController2: m_dmaController = DMA1; break;
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

void Dma::setDmaMem2memRegister() const {
  switch (m_cfg.memtomem) {
    case Config::MemToMem::memToMemDisabled: m_dmaChannel->CCR &= ~(DMA_CCR_MEM2MEM); break;
    case Config::MemToMem::memToMemEnabled: m_dmaChannel->CCR |= ~(DMA_CCR_MEM2MEM); break;
    default: break;
  }
}
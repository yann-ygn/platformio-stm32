#include "dma.hpp"

using namespace hal;

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

}

void Dma::getDmaControllerAddress() {
  switch (m_cfg.controller)
  {
    case Config::Controller::dmaController1: m_dmaController = DMA1; break;
    case Config::Controller::dmaController2: m_dmaController = DMA1; break;

    default:
        break;
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
#include "ads1015.h"

namespace Gaggiuino::Pressure {
  ADS1015Sensor::ADS1015Sensor(int address, bool initOnConstruction): m_ads(address) {
    if (initOnConstruction) { init(); }
  }

  void ADS1015Sensor::init() {
    m_ads.begin();
    m_ads.setGain(0);      // 6.144 volt
    m_ads.setDataRate(4);  // fast
    m_ads.setMode(0);      // continuous mode
    m_ads.readADC(0);      // first read to trigger
  }

  float ADS1015Sensor::getPressure() {
    // voltageZero = 0.5V --> 25.6 (8 bit) or 102.4 (10 bit) or 2666.7 (ADS 15 bit)
    // voltageMax = 4.5V --> 230.4 (8 bit) or 921.6 (10 bit) or 24000 (ADS 15 bit)
    // range 921.6 - 102.4 = 204.8 or 819.2 or 21333.3
    // pressure gauge range 0-1.2MPa - 0-12 bar
    // 1 bar = 17.1 or 68.27 or 1777.8
    return static_cast<float>(m_ads.getValue() - 166) / 111.11f; // 12bit
  }
}

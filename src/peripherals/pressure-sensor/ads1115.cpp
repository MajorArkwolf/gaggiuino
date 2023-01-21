#include "ads1115.h"
#include "../i2c_bus_reset.h"
#include "pindef.h"
#include "log.h"

namespace Gaggiuino::Pressure {
  ADS1115Sensor::ADS1115Sensor(int address, bool initOnConstruction): m_ads(address) {
    if (initOnConstruction) { init(); }
  }

  void ADS1115Sensor::init() {
    m_ads.begin();
    m_ads.setGain(0);      // 6.144 volt
    m_ads.setDataRate(4);  // fast
    m_ads.setMode(0);      // continuous mode
    m_ads.readADC(0);      // first read to trigger
  }

  void ADS1115Sensor::resetI2C() {
    if (digitalRead(hw_SCL) != HIGH || digitalRead(hw_SDA) != HIGH || m_ads.isConnected()) {
      LOG_INFO("Reset I2C pins");
      short result = I2C_ClearBus(hw_SDA, hw_SCL);
      char tmp[25];
      snprintf(tmp, sizeof(tmp), "I2C error code: %i", result);
      if (result == 0) {
        init();
      }
      else {

      }
      delay(50);
    }
  }

  float ADS1115Sensor::getPressure() {
    // voltageZero = 0.5V --> 25.6 (8 bit) or 102.4 (10 bit) or 2666.7 (ADS 15 bit)
    // voltageMax = 4.5V --> 230.4 (8 bit) or 921.6 (10 bit) or 24000 (ADS 15 bit)
    // range 921.6 - 102.4 = 204.8 or 819.2 or 21333.3
    // pressure gauge range 0-1.2MPa - 0-12 bar
    // 1 bar = 17.1 or 68.27 or 1777.8
    return static_cast<float>(m_ads.getValue() - 2666) / 1777.8f; // 16bit
  }
}

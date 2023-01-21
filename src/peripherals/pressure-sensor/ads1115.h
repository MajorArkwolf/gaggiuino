#pragma once
#include "ADS1X15.h"
namespace Gaggiuino::Pressure {
  class ADS1115Sensor {
  public:
    ADS1115Sensor(int address = 0x48, bool initOnConstruction = false);
    void init();
    float getPressure();
  private:
    void resetI2C();
    ADS1115 m_ads;
  };
}

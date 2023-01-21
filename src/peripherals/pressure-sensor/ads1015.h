#pragma once
#include "ADS1X15.h"
namespace Gaggiuino::Pressure {
  class ADS1015Sensor {
  public:
    ADS1015Sensor(int address = 0x48, bool initOnConstruction = false);
    void init();
    float getPressure();
  private:
    ADS1015 m_ads;
  };
}

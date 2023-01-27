#pragma once
#include <SimpleKalmanFilter.h>
#include "pressure_state.h"

namespace Gaggiuino::Pressure::Template {
  template<class T>
  class IPressureSensor {
  public:
    static constexpr float LowBandReading = 0.05f;
    static constexpr float HighBandReading = 0.1f;
    static constexpr float SmoothedHighBandReading = 2.55f;

    IPressureSensor(T pressureSensor): m_pressureSensor(pressureSensor) {};

    void init() { m_pressureSensor.init(); }

    void pollSensor() {
      m_previousPressure = m_currentPressure;
      m_currentPressure = m_pressureSensor.getPressure();
      m_previousSmoothedPressure = m_currentSmoothedPressure;
      m_currentSmoothedPressure = m_smoothPressure.updateEstimate(m_currentPressure);
    }

    float getPressure() {
      return m_currentPressure;
    }

    float getSmoothedPressure() { return m_currentSmoothedPressure; }

    State getPressureState() {
      if (m_currentSmoothedPressure >= m_previousSmoothedPressure + SmoothedHighBandReading) {
        return State::RaisingFast;
      }
      else if (m_currentPressure > m_previousPressure + LowBandReading) {
        return State::Raising;
      }
      else if (m_currentPressure < m_previousPressure - HighBandReading) {
        return State::FallingFast;
      }
      else if (m_currentPressure < m_previousPressure - LowBandReading) {
        return State::Falling;
      }
      else {
        return State::None;
      }
    }

  private:
    T m_pressureSensor;
    SimpleKalmanFilter m_smoothPressure = { 0.2f, 0.2f, 0.1f };
    float m_previousPressure = {};
    float m_currentPressure = {};
    float m_previousSmoothedPressure = {};
    float m_currentSmoothedPressure = {};
  };

}

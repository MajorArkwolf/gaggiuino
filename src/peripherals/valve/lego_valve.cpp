#include "lego_valve.h"
#include <Arduino.h>

namespace Gaggiuino::Valve {
  LegoValve::LegoValve(uint8_t addressPin): m_addressPin(addressPin) {
    pinMode(m_addressPin, OUTPUT_OPEN_DRAIN);
  }

  void LegoValve::setValve(State state) {
    // The lego valve has an inverted input and therefor
    // we set low for on and high for off.
    switch (state) {
    case State::Open:
      digitalWrite(m_addressPin, LOW);
      break;
    case State::Closed:
      digitalWrite(m_addressPin, HIGH);
      break;
    default:
      // Invalid state, do nothing and dont update.
      return;
    }
    m_currentState = state;
  }

  State LegoValve::getState() {
    return m_currentState;
  }
}

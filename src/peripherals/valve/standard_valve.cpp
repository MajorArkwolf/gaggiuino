#include "standard_valve.h"
#include <Arduino.h>

namespace Gaggiuino::Valve {
  StandardValve::StandardValve(uint8_t addressPin): m_addressPin(addressPin) {
    pinMode(m_addressPin, OUTPUT);
  }

  void StandardValve::setValve(State state) {
    // The lego valve has an inverted input and therefor
    // we set low for on and high for off.
    switch (state) {
    case State::Open:
      digitalWrite(m_addressPin, HIGH);
      break;
    case State::Closed:
      digitalWrite(m_addressPin, LOW);
      break;
    default:
      // Invalid state, do nothing and dont update.
      return;
    }
    m_currentState = state;
  }

  State StandardValve::getState() {
    return m_currentState;
  }
}

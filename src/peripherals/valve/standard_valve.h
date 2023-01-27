#pragma once
#include <cstdint>
#include "ivalve.h"
namespace Gaggiuino::Valve {
  class StandardValve: public IValve {
  public:
    StandardValve(uint8_t addressPin);
    void setValve(State state);
    State getState();
  private:
    uint8_t m_addressPin;
    State m_currentState = State::Closed;
  };
}

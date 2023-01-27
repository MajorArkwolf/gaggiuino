#pragma once
#include <cstdint>
#include "ivalve.h"
namespace Gaggiuino::Valve {
  class LegoValve: public IValve {
  public:
    LegoValve(uint8_t addressPin);
    void setValve(State state) override;
    State getState() override;
  private:
    uint8_t m_addressPin;
    State m_currentState = State::Closed;
  };
}

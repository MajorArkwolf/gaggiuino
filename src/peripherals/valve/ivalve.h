#pragma once
#include "valve_state.h"
namespace Gaggiuino::Valve {
  class IValve {
  public:
    virtual ~IValve() {};
    virtual void setValve(State state) = 0;
    virtual State getState() = 0;
  };
}

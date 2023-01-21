#include "pressure_state.h"

namespace Gaggiuino::Pressure {
  bool IsOverallRaising(State currentState) {
    return currentState == State::Raising || currentState == State::RaisingFast;
  }

  bool IsOverallFalling(State currentState) {
    return currentState == State::Falling || currentState == State::FallingFast;
  }
}

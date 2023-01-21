#pragma once
namespace Gaggiuino::Pressure {
  enum class State {
    None,
    Raising,
    RaisingFast,
    Falling,
    FallingFast,
  };

  bool IsOverallRaising(State currentState);

  bool IsOverallFalling(State currentState);
}

#ifndef PRESSURE_H
#define PRESSURE_H

namespace Common {

  enum class PressureState {
    Neutral,
    Rising,
    RisingFast,
    Falling,
    FallingFast,
  };

  bool IsRising(PressureState value);
  bool isFalling(PressureState value);
}
#endif

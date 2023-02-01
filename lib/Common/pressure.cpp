#include "pressure.h"
namespace Common {
  bool IsRising(PressureState value) {
    return value == PressureState::Rising || value == PressureState::RisingFast;
  }
  bool isFalling(PressureState value) {
    return value == PressureState::Falling || value == PressureState::FallingFast;
  }
}

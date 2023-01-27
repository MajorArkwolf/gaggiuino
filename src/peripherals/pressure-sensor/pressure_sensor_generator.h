#pragma once
#include "pressure_sensor.h"
#if defined SINGLE_BOARD
#include "ads1015.h"
using PressureSensor = Gaggiuino::Pressure::Template::IPressureSensor<Gaggiuino::Pressure::ADS1015Sensor>;
#else
#include "ads1115.h"
using PressureSensor = Gaggiuino::Pressure::Template::IPressureSensor<Gaggiuino::Pressure::ADS1115Sensor>;
#endif


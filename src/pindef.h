#ifndef PINDEF_H
#define PINDEF_H

#ifdef ESP_CORE
#include "../mcu/esp32-impl/esp_pindef.h"
#else
#include "../mcu/stm32-impl/stm32_pindef.h"
#endif
#endif

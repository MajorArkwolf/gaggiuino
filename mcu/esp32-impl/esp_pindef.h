#ifndef ESP_PINDEF_H
#define ESP_PINDEF_H
#include "esp32-hal-gpio.h"
// ESP32 pins definitions
#define thermoDO GPIO_NUM_37
#define thermoCS GPIO_NUM_35
#define thermoCLK GPIO_NUM_36

// Dimmer
#define zcPin GPIO_NUM_9
#define dimmerPin GPIO_NUM_6

// Physical Switch
#define brewPin GPIO_NUM_11
#define steamPin GPIO_NUM_12

// Opto Relay
#define relayPin GPIO_NUM_17

// Relay for Valve
#define valvePin GPIO_NUM_5

// Unknown
#define waterPin GPIO_NUM_43  // NOT BOUND YET

// Scales
#define HX711_sck_1 GPIO_NUM_44   // NOT BOUND YET
#define HX711_sck_2 GPIO_NUM_48   // NOT BOUND YET
#define HX711_dout_1 GPIO_NUM_47  // NOT BOUND YET
#define HX711_dout_2 GPIO_NUM_46  // NOT BOUND YET

#define USART_LCD Serial1   // 39(TX) & 38(RX)
#define USART_ESP Serial2   // NOT BOUND YET
#define USART_DEBUG Serial  // NOT BOUND YET

#define hw_SCL 15  // NOT BOUND YET
#define hw_SDA 16  // NOT BOUND YET

#endif

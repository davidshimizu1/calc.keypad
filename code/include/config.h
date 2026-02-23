#pragma once
#include <Arduino.h>

// ESP32 PINS
const uint8_t ROW_PINS[5] = {13, 14, 21, 47, 48};
const uint8_t COL_PINS[5] = {5, 6, 7, 15, 18};

#define HMI_RX 16
#define HMI_TX 17

// HMI ADDRESSES
const uint16_t ADDR_INPUT_VP  = 0x1080;
const uint16_t ADDR_EQ_1      = 0x1020;     
const uint16_t ADDR_ANS_1     = 0x1030;     
const uint16_t ADDR_EQ_2      = 0x1040;    
const uint16_t ADDR_ANS_2     = 0x1050;     
const uint16_t ADDR_EQ_3      = 0x1060;     
const uint16_t ADDR_ANS_3     = 0x1070;

// sleep
#define SLEEP_TIMEOUT_MS 300000
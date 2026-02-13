#ifndef CLOCK_H
#define CLOCK_H
#include <Arduino.h>
#include <WiFi.h>
#include "HMI_Driver.h"

class ClockManager {
public:
    ClockManager(HardwareSerial& hmiSerial);
    void begin();
    bool sync();
    void update(); 

private:
    HardwareSerial& _hmiSerial;
    int _lastMinute = -1;
    const uint16_t ADDR_CLOCK = 0x1100;
    void sendString(uint16_t addr, String text);
};

#endif
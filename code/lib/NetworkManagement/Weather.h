#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "WifiManager.h"

class WeatherManager {
public:
    WeatherManager(HardwareSerial& hmiSerial, WifiManager& wifi);
    
    void begin();
    
    void update();

private:
    HardwareSerial& _hmiSerial;
    WifiManager& _wifi;
    
    unsigned long _lastWeatherUpdate;
    static const unsigned long WEATHER_UPDATE_INTERVAL = 900000;
    

    static const uint16_t ADDR_WEATHER_STRING = 0x1140;

    void fetchWeather();
    void sendString(uint16_t addr, String text);
};

#endif // WEATHER_MANAGER_H
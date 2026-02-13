/*
#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>
struct WeatherData {
    float temperature;
    int humidity;
    int conditionCode;
    char description[32];
};

class WeatherManager {
public:
    WeatherManager(HardwareSerial& hmiSerial);
    
    bool updateWeather();

private:
    HardwareSerial& _hmiSerial;
    void sendToHMI(const WeatherData& data);
    uint16_t mapConditionToIcon(int code);
};

#endif
*/
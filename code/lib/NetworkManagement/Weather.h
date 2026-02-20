#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>
#include <HardwareSerial.h>

class WeatherManager {
public:
    WeatherManager(HardwareSerial& hmiSerial);
    
    // Call this once in setup() after WiFi connects
    void begin();
    
    // Call this continuously in loop()
    void update();

private:
    HardwareSerial& _hmiSerial;
    
    // Timer tracking
    unsigned long _lastWeatherUpdate;
    static const unsigned long WEATHER_UPDATE_INTERVAL = 900000;
    
    // UI Addresses
    static const uint16_t ADDR_WEATHER_STRING = 0x1140;

    // Internal methods
    void fetchWeather();
    void sendString(uint16_t addr, String text);
};

#endif // WEATHER_MANAGER_H
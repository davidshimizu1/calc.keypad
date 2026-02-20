#include "Weather.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

WeatherManager::WeatherManager(HardwareSerial& hmiSerial) : 
    _hmiSerial(hmiSerial), 
    _lastWeatherUpdate(0) {}

void WeatherManager::begin() {
    fetchWeather();
}

void WeatherManager::update() {
    // update every 15  mins
    if (millis() - _lastWeatherUpdate > WEATHER_UPDATE_INTERVAL) {
        fetchWeather();
    }
}

void WeatherManager::fetchWeather() {
    if (WiFi.status() != WL_CONNECTED) return;

    try {
        HTTPClient http;
        // weather for la jolla
        String url = "http://api.openweathermap.org/data/2.5/weather?lat=32.8683&lon=-117.2171&units=imperial&appid=a4d6261bf67dabb04bf836a442a1f227";
        
        http.begin(url);
        int httpCode = http.GET();

        if (httpCode == HTTP_CODE_OK) {
            JsonDocument doc; 
            
            DeserializationError error = deserializeJson(doc, http.getString());
            
            if (!error) {
                float rawTemp = doc["main"]["temp"];
                int tempF = (int)round(rawTemp);
                
                char weatherBuf[16];
                snprintf(weatherBuf, sizeof(weatherBuf), "%d\xB0""F", tempF);

                sendString(ADDR_WEATHER_STRING, String(weatherBuf));
            } else {
                Serial.print("JSON Parsing failed: ");
                Serial.println(error.c_str());
            }
        }
        http.end();
        
        _lastWeatherUpdate = millis();
        
    } catch (...) {
        Serial.println("Weather logic failed safely. Will retry next cycle.");
    }
}
void WeatherManager::sendString(uint16_t addr, String text) {
    try {
        const int WIPE_LEN = 12; 
        uint8_t packetLen = 3 + WIPE_LEN;

        _hmiSerial.write(0x5A);
        _hmiSerial.write(0xA5);
        _hmiSerial.write(packetLen);
        _hmiSerial.write(0x10); 
        _hmiSerial.write((uint8_t)(addr >> 8));
        _hmiSerial.write((uint8_t)(addr & 0xFF));

        for (int i = 0; i < WIPE_LEN; i++) {
            if (i < (int)text.length()) {
                _hmiSerial.write(text[i]);
            } else {
                _hmiSerial.write(0x00); 
            }
        }
    } catch (...) {
        Serial.println("Serial write to HMI failed.");
    }
}
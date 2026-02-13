/*
#include "weather.h"
#include <HTTPClient.h>
#include <ArduinoJson.h> // Essential for modern ESP32 API handling

WeatherManager::WeatherManager(HardwareSerial& hmiSerial) : _hmiSerial(hmiSerial) {}

// API KEY a4d6261bf67dabb04bf836a442a1f227
// lat, long 32.868385842663045, -117.2171590299589
bool WeatherManager::updateWeather() {
    try {
        HTTPClient http;
        http.begin("http://api.openweathermap.org/data/2.5/weather?q=LaJolla&units=imperial&appid=a4d6261bf67dabb04bf836a442a1f227");
        
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            StaticJsonDocument<1024> doc;
            deserializeJson(doc, payload);

            WeatherData data;
            data.temperature = doc["main"]["temp"];
            data.humidity = doc["main"]["humidity"];
            data.conditionCode = doc["weather"][0]["id"];
            strlcpy(data.description, doc["weather"][0]["main"], sizeof(data.description));

            sendToHMI(data);
            return true;
        }
    } catch (...) {
        Serial.println("Weather Update Failed: Network or Parsing Error");
    }
    return false;
}

void WeatherManager::sendToHMI(const WeatherData& data) {
    // Logic: Map values to the Variable Addresses (RAM) you set in UI_Editor-II
    // Example: Temp -> 0x2000, Humidity -> 0x2002, Icon -> 0x2004
    
    uint16_t tempScaled = (uint16_t)(data.temperature * 10); // HMI handles decimals as integers [cite: 477, 480]
    
    // Send Temperature to a 'Text Number Display' widget [cite: 197, 476]
    // Packet: Header(5AA5) + Len(07) + Cmd(10) + Addr(2000) + Data(2 Bytes) + CRC [cite: 466]
    uint8_t packet[] = { 0x5A, 0xA5, 0x07, 0x10, 0x20, 0x00, 
                         (uint8_t)(tempScaled >> 8), (uint8_t)(tempScaled & 0xFF), 
                         0x00, 0x00 }; // CRC Placeholder
    _hmiSerial.write(packet, sizeof(packet));
}
    */
#include "Clock.h"
#include <WiFi.h>
#include <time.h>

static const char* SERVER = "pool.ntp.org";
static const char* TIMEZONE = "PST8PDT,M3.2.0,M11.1.0";

ClockManager::ClockManager(HardwareSerial& hmiSerial) : _hmiSerial(hmiSerial) {}

void ClockManager::begin() {
    configTime(0, 0, SERVER);
    setenv("TZ", TIMEZONE, 1);
    tzset();
}

bool ClockManager::sync() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo, 5000)) return false;
    _lastMinute = -1; 
    return true;
}

void ClockManager::sendString(uint16_t addr, String text) {
    const int WIPE_LEN = 40; 
    uint8_t packetLen = 3 + WIPE_LEN;

    _hmiSerial.write(0x5A);
    _hmiSerial.write(0xA5);
    _hmiSerial.write(packetLen);
    _hmiSerial.write(0x10); 
    _hmiSerial.write((uint8_t)(addr >> 8));
    _hmiSerial.write((uint8_t)(addr & 0xFF));

    for (int i = 0; i < WIPE_LEN; i++) {
        if (i < (int)text.length()) _hmiSerial.write(text[i]);
        else _hmiSerial.write(0x00); 
    }
}

void ClockManager::update() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return;

    static int lastDay = -1;
    bool dayChanged = (timeinfo.tm_mday != lastDay);

    if (timeinfo.tm_min != _lastMinute || dayChanged) {
        try {
            _lastMinute = timeinfo.tm_min;
            lastDay = timeinfo.tm_mday;

            char fullBuf[20];
            
            strftime(fullBuf, sizeof(fullBuf), "%b %d | %H:%M", &timeinfo);
            sendString(ADDR_CLOCK, String(fullBuf));
        } catch (...) {
        }
    }
}
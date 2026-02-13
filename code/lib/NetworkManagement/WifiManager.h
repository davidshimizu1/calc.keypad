#ifndef WifiManager_h
#define WifiManager_h

#include <Arduino.h>
#include <WiFi.h>

class WifiManager {
public:
    WifiManager();

    bool connect(); 

    void disconnect();

    bool isConnected();

private:
    const unsigned long CONNECTION_TIMEOUT = 10000; 
};

#endif
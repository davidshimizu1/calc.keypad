#include "WifiManager.h"

const char* WIFI_SSID = "Noahisfat";
const char* WIFI_PASS = "t8dxguuqhya%";

WifiManager::WifiManager() {

}

bool WifiManager::connect() {

    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }

    Serial.print("Connecting to WiFi: ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED && 
           millis() - startAttemptTime < CONNECTION_TIMEOUT) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("Success! IP: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("Error: Connection Timed Out.");
        return false;
    }
}

void WifiManager::disconnect() {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi Disconnected.");
}

bool WifiManager::isConnected() {
    return (WiFi.status() == WL_CONNECTED);
}
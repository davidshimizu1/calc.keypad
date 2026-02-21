#include "bluetoothkeypad.h"


BluetoothKeypadController::BluetoothKeypadController() 
    : bleKeyboard("Smart Numpad", "YourBrand", 100), 
      currentMode(DeviceMode::CALCULATOR), 
      isInitialized(false) {}

void BluetoothKeypadController::begin() {
    try {

        bleKeyboard.begin();
        isInitialized = true;
        Serial.println("BLE Keyboard initialized successfully.");
    } catch (const std::exception& e) {
        Serial.printf("CRITICAL ERROR: Failed to initialize BLE Keyboard. Reason: %s\n", e.what());
        isInitialized = false;
    } catch (...) {
        Serial.println("CRITICAL ERROR: Unknown exception during BLE initialization.");
        isInitialized = false;
    }
}

void BluetoothKeypadController::setMode(DeviceMode mode) {
    currentMode = mode;
    if (mode == DeviceMode::BLUETOOTH_KEYPAD) {
        Serial.println("Switched to Bluetooth Keypad Mode.");
    } else {
        Serial.println("Switched to Local Calculator Mode.");
    }
}

bool BluetoothKeypadController::isConnected() {
    if (!isInitialized) return false;
    return bleKeyboard.isConnected();
}

void BluetoothKeypadController::sendKey(uint8_t keyCode) {
    try {
        if (!isInitialized) {
            throw std::runtime_error("BLE not initialized.");
        }

        if (currentMode != DeviceMode::BLUETOOTH_KEYPAD) {
            return; 
        }
    
        if (!bleKeyboard.isConnected()) {
            throw std::runtime_error("No active BLE connection to host.");
        }

        bleKeyboard.write(keyCode);
        
    } catch (const std::exception& e) {
        Serial.printf("Error sending key: %s\n", e.what());
        // UI Action: Briefly flash a red error icon on the HMI display.
    }
}

void BluetoothKeypadController::sendString(const String& text) {
    try {
        if (!isInitialized || currentMode != DeviceMode::BLUETOOTH_KEYPAD || !bleKeyboard.isConnected()) {
            throw std::runtime_error("Invalid state for sending string.");
        }
        
        bleKeyboard.print(text);
        
    } catch (const std::exception& e) {
        Serial.printf("Error sending string: %s\n", e.what());
    }
}
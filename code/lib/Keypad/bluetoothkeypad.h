#ifndef bluetoothkeypad_H
#define bluetoothkeypad_H

#include <Arduino.h>
#include <BleKeyboard.h>
#include <stdexcept>

enum class DeviceMode {
    CALCULATOR,
    BLUETOOTH_KEYPAD
};

class BluetoothKeypadController {
private:
    BleKeyboard bleKeyboard;
    DeviceMode currentMode;
    bool isInitialized;

public:
    BluetoothKeypadController();

    void begin();

    void setMode(DeviceMode mode);

    bool isConnected();

    void sendKey(uint8_t keyCode);
    
    void sendString(const String& text);
};

#endif 
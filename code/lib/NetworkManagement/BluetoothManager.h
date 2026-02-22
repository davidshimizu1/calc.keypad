#pragma once
#include <Arduino.h>
#include <BleKeyboard.h>
#include <stdexcept>

class BLEManager {
private:
    BleKeyboard _bleKeyboard;

public:
    BLEManager() : _bleKeyboard("Smart Numpad", "Maker", 100) {}

    void begin() {
        try {
            _bleKeyboard.begin();
            Serial.println("BLE HID Stack Initialized.");
        } catch (...) {
            Serial.println("CRITICAL: Failed to initialize BLE Keyboard.");
        }
    }

    bool isConnected() {
        return _bleKeyboard.isConnected();
    }

    void sendKey(const String& key) {
        try {
            if (!_bleKeyboard.isConnected()) {
                return; 
            }

            if (key.length() == 1) {
                char c = key[0];
                if ((c >= '0' && c <= '9') || c == '.' || c == '+' || c == '-' || c == '*' || c == '/') {
                    _bleKeyboard.write(c);
                    return;
                }
                if (c == ' ') {
                    _bleKeyboard.write(' ');
                    return;
                }
            }

            if (key == "enter") {
                _bleKeyboard.write(KEY_RETURN); 
            } 
            else if (key == "del" || key == "clr") {
                _bleKeyboard.write(KEY_BACKSPACE);
            }
            else if (key == "home") {
                _bleKeyboard.write(KEY_HOME);
            }
            else if (key == "up") {
                _bleKeyboard.write(KEY_UP_ARROW);
            }
            else if (key == "down") {
                _bleKeyboard.write(KEY_DOWN_ARROW);
            }
            else if (key == "left") {
                _bleKeyboard.write(KEY_LEFT_ARROW);
            }
            else if (key == "right") {
                _bleKeyboard.write(KEY_RIGHT_ARROW);
            }
            else if (key == "F2") {
                _bleKeyboard.write(KEY_F2);
            }
            else if (key == "F3") {
                _bleKeyboard.write(KEY_F3);
            }
            else if (key == "F4") {
                _bleKeyboard.write(KEY_F4);
            }
            
            else if (key == "sin") {
                _bleKeyboard.press(KEY_LEFT_CTRL);
                _bleKeyboard.press('a');
                _bleKeyboard.releaseAll();
            }
            else if (key == "cos") {
                _bleKeyboard.press(KEY_LEFT_CTRL);
                _bleKeyboard.press('c');
                _bleKeyboard.releaseAll();
            }
            else if (key == "tan") {
                _bleKeyboard.press(KEY_LEFT_CTRL);
                _bleKeyboard.press('v');
                _bleKeyboard.releaseAll();
            }
            else if (key == "ln") {
                _bleKeyboard.press(KEY_LEFT_ALT);
                _bleKeyboard.press(KEY_TAB);
                _bleKeyboard.releaseAll();
            }
            else if (key == "^") {
                _bleKeyboard.press(KEY_LEFT_CTRL);
                _bleKeyboard.press('t');
                _bleKeyboard.releaseAll();
            }
            else if (key == "neg") {
                _bleKeyboard.press(KEY_LEFT_CTRL);
                _bleKeyboard.press('w');
                _bleKeyboard.releaseAll();
            }
            else {
                Serial.printf("Notice: Key '%s' has no PC HID mapping. Ignored.\n", key.c_str());
            }

        } catch (const std::exception& e) {
            Serial.printf("Error dispatching BLE Key: %s\n", e.what());
        } catch (...) {
            Serial.println("Unknown error dispatching BLE Key.");
        }
    }
};
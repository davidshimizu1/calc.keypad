#include "Keypad.h"
#include <string.h>

KeypadScanner::KeypadScanner() : _debounceDelay(200), _lastPressTime(0), _isShifted(false) {}

void KeypadScanner::begin(const uint8_t* rows, const uint8_t* cols) {
    try {
        memcpy(_rowPins, rows, 5 * sizeof(uint8_t));
        memcpy(_colPins, cols, 5 * sizeof(uint8_t));

        // initialize column inputs
        for (int i = 0; i < 5; i++) {
            pinMode(_colPins[i], INPUT_PULLUP);
        }
        
        // initialize row outputs
        for (int i = 0; i < 5; i++) { 
            pinMode(_rowPins[i], OUTPUT); 
            digitalWrite(_rowPins[i], HIGH);
        }
    } catch (...) {
        Serial.println("Error initializing keypad pins.");
    }
}

// scans the matrix and returns the pressed key
const char* KeypadScanner::getKey() {
    if (millis() - _lastPressTime < _debounceDelay) return nullptr;
    
    for (int r = 0; r < 5; r++) {
        digitalWrite(_rowPins[r], LOW);
        delayMicroseconds(5); 

        for (int c = 0; c < 5; c++) {
            if (digitalRead(_colPins[c]) == LOW) {
                _lastPressTime = millis();
                digitalWrite(_rowPins[r], HIGH);
                
                const char* baseKeyChar = KEY_LAYOUT[r][c];

                if (strcmp(baseKeyChar, "2nd") == 0) {
                    _isShifted = !_isShifted;
                    return "SHIFT_CMD"; 
                }

                const char* finalKeyChar = nullptr;
                
                if (_isShifted) {
                    finalKeyChar = KEY_LAYOUT_2ND[r][c];
                    _isShifted = false; 
                } else {
                    finalKeyChar = baseKeyChar;
                }

                return finalKeyChar;
            }
        }
        digitalWrite(_rowPins[r], HIGH);
    }
    
    return nullptr; 
}
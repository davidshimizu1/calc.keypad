#include "Keypad.h"

KeypadScanner::KeypadScanner() : _debounceDelay(200), _lastPressTime(0), _isShifted(false) {}

void KeypadScanner::begin(const uint8_t* rows, const uint8_t* cols) {
    memcpy(_rowPins, rows, 5 * sizeof(uint8_t));
    memcpy(_colPins, cols, 5 * sizeof(uint8_t));

    // columns inputs
    for (int i = 0; i < 5; i++) pinMode(_colPins[i], INPUT_PULLUP);
    
    // rows outputs
    for (int i = 0; i < 5; i++) { 
        pinMode(_rowPins[i], OUTPUT); 
        digitalWrite(_rowPins[i], HIGH);
    }
}
// scans
const char* KeypadScanner::getKey() {
    if (millis() - _lastPressTime < _debounceDelay) return nullptr;
    
    for (int r = 0; r < 5; r++) {
        digitalWrite(_rowPins[r], LOW);
        delayMicroseconds(5);

        for (int c = 0; c < 5; c++) {
            if (digitalRead(_colPins[c]) == LOW) {
                _lastPressTime = millis();
                digitalWrite(_rowPins[r], HIGH);
 
                if (r == 0 && c == 0) {
                    _isShifted = !_isShifted;
                    return "SHIFT_CMD";
                }

                const char* keyChar;
                
                if (_isShifted) {
                    keyChar = KEY_LAYOUT_2ND[r][c];
                    _isShifted = false;
                } else {
                    keyChar = KEY_LAYOUT[r][c];
                }

                return keyChar;
            }
        }
        digitalWrite(_rowPins[r], HIGH);
    }
    return nullptr;
}
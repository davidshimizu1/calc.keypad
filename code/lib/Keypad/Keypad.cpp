#include "Keypad.h" // Ensure this matches your actual header file name
#include <string.h>

KeypadScanner::KeypadScanner() : _debounceDelay(200), _lastPressTime(0), _isShifted(false) {}

void KeypadScanner::begin(const uint8_t* rows, const uint8_t* cols) {
    try {
        memcpy(_rowPins, rows, 5 * sizeof(uint8_t));
        memcpy(_colPins, cols, 5 * sizeof(uint8_t));

        // Initialize column inputs
        for (int i = 0; i < 5; i++) {
            pinMode(_colPins[i], INPUT_PULLUP);
        }
        
        // Initialize row outputs
        for (int i = 0; i < 5; i++) { 
            pinMode(_rowPins[i], OUTPUT); 
            digitalWrite(_rowPins[i], HIGH);
        }
    } catch (...) {
        Serial.println("Error initializing keypad pins.");
    }
}

// Scans the matrix and returns the pressed key
const char* KeypadScanner::getKey() {
    // 1. Debounce check
    if (millis() - _lastPressTime < _debounceDelay) return nullptr;
    
    for (int r = 0; r < 5; r++) {
        digitalWrite(_rowPins[r], LOW);
        delayMicroseconds(5); // Allow voltage to settle on the lines

        for (int c = 0; c < 5; c++) {
            if (digitalRead(_colPins[c]) == LOW) {
                // Key press detected
                _lastPressTime = millis();
                digitalWrite(_rowPins[r], HIGH); // Reset row before returning
                
                // 2. Identify the base key string from the matrix
                const char* baseKeyChar = KEY_LAYOUT[r][c];

                // 3. Check if the pressed key is the Shift/2nd command
                if (strcmp(baseKeyChar, "2nd") == 0) {
                    _isShifted = !_isShifted; // Toggle the shift state
                    return "SHIFT_CMD";       // Tell the main loop to update the UI
                }

                // 4. Handle standard key processing
                const char* finalKeyChar = nullptr;
                
                if (_isShifted) {
                    finalKeyChar = KEY_LAYOUT_2ND[r][c];
                    // Reset shift state after a single key press (Standard calculator behavior)
                    _isShifted = false; 
                } else {
                    finalKeyChar = baseKeyChar;
                }

                return finalKeyChar;
            }
        }
        digitalWrite(_rowPins[r], HIGH);
    }
    
    return nullptr; // No key pressed
}
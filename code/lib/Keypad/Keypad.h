#pragma once
#include <Arduino.h>

class KeypadScanner {
private:
    uint8_t _rowPins[5];
    uint8_t _colPins[5];
    unsigned long _lastPressTime;
    const unsigned long _debounceDelay;

    bool _isShifted; 

    // 1st 
    const char* KEY_LAYOUT[5][5] = {

      {"/",    "tan",   "cos",  "sin",  "2nd"},        // row 0
      {"*",     "9",    "8",    "7",    "del"},        // row 1
      {"-",     "6",    "5",    "4",    "ln"},         // row 2
      {"+",     "3",    "2",    "1",    "^"},          // row 3
      {"enter", "neg",  ".",    "0",    "home"}        // row 4
    };

    // 2nd/shift
    const char* KEY_LAYOUT_2ND[5][5] = {

      {"pi",    "atan",   "acos",  "asin",  "2nd"},    // row 0
      {"EE",    ")",      "up",    "(",     "clr"},    // row 1:
      {"log",   "right",  "F4",    "left",  "exp"},    // row 2:
      {"10^x",  "F2",     "down",  "F1",    "sqrt"},   // row 3:
      {"enter", "ans",    "F3",    " ",     "home"}    // row 4
    };

public:
    KeypadScanner();
    void begin(const uint8_t* rows, const uint8_t* cols);
    const char* getKey();

    bool isShiftActive() { return _isShifted; } 
};
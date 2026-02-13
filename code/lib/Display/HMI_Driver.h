#pragma once
#include <Arduino.h>

struct CalcHistory {
    String equation;
    String answer;
};

class HMIDriver {
private:
    HardwareSerial* _serial;
    void sendRaw(uint16_t addr, String text);

public:
    void begin(HardwareSerial* serial);
    void updateInput(String text);
    void updateHistory(CalcHistory h1, CalcHistory h2, CalcHistory h3);
    
    uint16_t addr_input;
    uint16_t addr_eq_1;
    uint16_t addr_ans_1;
    uint16_t addr_eq_2;
    uint16_t addr_ans_2;
    uint16_t addr_eq_3;
    uint16_t addr_ans_3;
};
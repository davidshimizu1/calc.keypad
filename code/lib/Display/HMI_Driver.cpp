#include "HMI_Driver.h"

void HMIDriver::begin(HardwareSerial* serial) {
    _serial = serial;
}

void HMIDriver::sendRaw(uint16_t addr, String text) {
    const int WIPE_LEN = 40; 
    uint8_t packetLen = 3 + WIPE_LEN;

    _serial->write(0x5A);
    _serial->write(0xA5);
    _serial->write(packetLen);
    _serial->write(0x10); 
    _serial->write(highByte(addr));
    _serial->write(lowByte(addr));

    for (int i = 0; i < WIPE_LEN; i++) {
        if (i < text.length()) _serial->write(text[i]);
        else _serial->write(0x00); 
    }
}

void HMIDriver::updateInput(String text) {
    sendRaw(addr_input, text);
}

void HMIDriver::updateHistory(CalcHistory h1, CalcHistory h2, CalcHistory h3) {
    sendRaw(addr_eq_1, h1.equation);
    sendRaw(addr_ans_1, h1.answer);
    sendRaw(addr_eq_2, h2.equation);
    sendRaw(addr_ans_2, h2.answer);
    sendRaw(addr_eq_3, h3.equation);
    sendRaw(addr_ans_3, h3.answer);
}
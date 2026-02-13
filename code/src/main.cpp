#include <Arduino.h>
#include "Config.h"
#include "Calculator.h"
#include "HMI_Driver.h"
#include "Keypad.h"
#include "WifiManager.h"
#include "Clock.h"

ExpressionParser parser;
HMIDriver hmi;
KeypadScanner keypad;

WifiManager myNet;
ClockManager myClock(Serial2);

String inputBuffer = ""; 
double lastResult = 0.0;
bool hasLastResult = false;
CalcHistory history[3]; 

void pushHistory(String eq, double val) {
    history[0] = history[1]; 
    history[1] = history[2];
    history[2].equation = eq;

    String ansStr = String(val, 8);

    while (ansStr.endsWith("0")) ansStr.remove(ansStr.length() - 1);
    if (ansStr.endsWith(".")) ansStr.remove(ansStr.length() - 1);
    
    history[2].answer = "= " + ansStr;
    
    hmi.updateHistory(history[0], history[1], history[2]);
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, HMI_RX, HMI_TX);
    delay(2000);
    Serial.println("starting");
    Serial.flush();
    Serial.println("Initializing Time");
    myClock.begin();

    if (myNet.connect()) { 
        myClock.sync(); 
        myNet.disconnect(); 
    }

    keypad.begin(ROW_PINS, COL_PINS);
    hmi.begin(&Serial2);

    // HMI ADDRESSES
    hmi.addr_input = ADDR_INPUT_VP;
    hmi.addr_eq_1  = ADDR_EQ_1;
    hmi.addr_ans_1 = ADDR_ANS_1;
    hmi.addr_eq_2  = ADDR_EQ_2;
    hmi.addr_ans_2 = ADDR_ANS_2;
    hmi.addr_eq_3  = ADDR_EQ_3;
    hmi.addr_ans_3 = ADDR_ANS_3;

    hmi.updateInput("");
    hmi.updateHistory(history[0], history[1], history[2]);
}

void loop() {
    const char* key = keypad.getKey();
    if (!key) return;
    String keyStr = String(key);

    myClock.update();
    
    // UI
    if (keyStr == "SHIFT_CMD") {
        bool active = keypad.isShiftActive();

        Serial.print("Shift: "); Serial.println(active);
        return; 
    }

    // clear
    if (keyStr == "clr") {
        inputBuffer = "";
        hmi.updateInput(inputBuffer);
        return;
    }

    // delete
    if (keyStr == "del") {
        if (inputBuffer.length() > 0) {
            inputBuffer.remove(inputBuffer.length() - 1);
            hmi.updateInput(inputBuffer);
        }
        return;
    }

    // home
    if (keyStr == "home") {
        inputBuffer = "";
        history[0] = {"", ""};
        history[1] = {"", ""};
        history[2] = {"", ""};
        hasLastResult = false;
        hmi.updateHistory(history[0], history[1], history[2]);
        hmi.updateInput(inputBuffer);
        return;
    }

    // enter
    if (keyStr == "enter") {
        if (inputBuffer.length() > 0) {
            double result = parser.solve(inputBuffer);
            pushHistory(inputBuffer, result);
            lastResult = result;
            hasLastResult = true;
            inputBuffer = "";
            hmi.updateInput(inputBuffer);
        }
        return;
    }

    // special
    if (keyStr == "up" || keyStr == "down" || keyStr == "left" || keyStr == "right" ||
        keyStr == "F1" || keyStr == "F2"   || keyStr == "F3"   || keyStr == "F4") {
        return;
    }

    // logic
    if (inputBuffer == "" && hasLastResult) {
        if (keyStr == "+" || keyStr == "-" || keyStr == "*" || keyStr == "/" || keyStr == "^") {
            String resStr = String(lastResult);
            if (resStr.endsWith(".00")) resStr.remove(resStr.length() - 3);
            inputBuffer = resStr;
        }
    }

    if (keyStr == "neg") {
        inputBuffer += "-";
    }
    else if (keyStr == "ans") {
        if (hasLastResult) inputBuffer += String(lastResult);
    }
    else if (keyStr == "10^x") {
        inputBuffer += "10^(";
    }
    else if (keyStr == "sin" || keyStr == "cos" || keyStr == "tan" || 
             keyStr == "asin"|| keyStr == "acos"|| keyStr == "atan"||
             keyStr == "ln"  || keyStr == "log" || keyStr == "sqrt" || 
             keyStr == "exp") {
        inputBuffer += keyStr + "(";
    }
    else {
        inputBuffer += keyStr;
    }

    hmi.updateInput(inputBuffer);
}
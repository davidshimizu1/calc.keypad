#pragma once
#include <Arduino.h>
#include <math.h>

class ExpressionParser {
private:
    String _expr;
    int _pos;
    char _currChar;
    bool _useDegrees;

    void nextChar();
    bool eat(char charToEat);
    double parseExpression();
    double parseTerm();
    double parsePower();
    double parseFactor();

public:
    ExpressionParser() : _useDegrees(true) {}

    void setMode(bool degrees) { _useDegrees = degrees; }
    
    double solve(const String &expression);
};
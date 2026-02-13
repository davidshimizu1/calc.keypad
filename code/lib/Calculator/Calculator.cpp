#include "Calculator.h"

// next char
void ExpressionParser::nextChar() {
    _currChar = (++_pos < _expr.length()) ? _expr[_pos] : -1;
}

// consume char
bool ExpressionParser::eat(char charToEat) {
    while (_currChar == ' ') nextChar();
    if (_currChar == charToEat) {
        nextChar();
        return true;
    }
    return false;
}

// solver
double ExpressionParser::solve(const String &expression) {
    _expr = expression;
    _pos = -1;
    
    int openCount = 0;
    for(char c : _expr) if(c == '(') openCount++; else if(c == ')') openCount--;
    while(openCount > 0) { _expr += ")"; openCount--; }

    nextChar();
    double res = parseExpression();

    if (isnan(res) || isinf(res)) return 0.0;
    return res;
}

// addition and subtraction
double ExpressionParser::parseExpression() {
    double x = parseTerm();
    for (;;) {
        if      (eat('+')) x += parseTerm();
        else if (eat('-')) x -= parseTerm();
        else return x;
    }
}

// multiplication and division
double ExpressionParser::parseTerm() {
    double x = parsePower();
    for (;;) {
        if      (eat('*')) x *= parsePower();
        else if (eat('/')) x /= parsePower();
        else return x;
    }
}

// exponents
double ExpressionParser::parsePower() {
    double x = parseFactor();
    if (eat('^')) {
        x = pow(x, parsePower()); 
    }
    return x;
}

double ExpressionParser::parseFactor() {
    if (eat('+')) return parseFactor();
    if (eat('-')) return -parseFactor();

    double x = 0;
    int startPos = _pos;
    
    // parenthesis
    if (eat('(')) { 
        x = parseExpression();
        eat(')');
    } 
    // numbers
    else if ((_currChar >= '0' && _currChar <= '9') || _currChar == '.') {
        while ((_currChar >= '0' && _currChar <= '9') || _currChar == '.') nextChar();
        
        if (_currChar == 'E' || _currChar == 'e') {
            nextChar();
            if (_currChar == '+' || _currChar == '-') nextChar();
            while (_currChar >= '0' && _currChar <= '9') nextChar();
        }
        
        x = _expr.substring(startPos, _pos).toDouble();
    } 
    // functions
    else if (_currChar >= 'a' && _currChar <= 'z') {
        while (_currChar >= 'a' && _currChar <= 'z') nextChar();
        String func = _expr.substring(startPos, _pos);
        
        x = parseFactor();

        double angle = _useDegrees ? (x * M_PI / 180.0) : x;

        if      (func == "sin") x = sin(angle);
        else if (func == "cos") x = cos(angle);
        else if (func == "tan") x = tan(angle);
        else if (func == "asin") x = _useDegrees ? (asin(x) * 180.0 / M_PI) : asin(x);
        else if (func == "acos") x = _useDegrees ? (acos(x) * 180.0 / M_PI) : acos(x);
        else if (func == "atan") x = _useDegrees ? (atan(x) * 180.0 / M_PI) : atan(x);
        
        else if (func == "ln")   x = log(x);
        else if (func == "log")  x = log10(x);
        else if (func == "exp")  x = exp(x);
        else if (func == "sqrt") x = sqrt(x);
        else if (func == "abs")  x = abs(x);
        
        else if (func == "pi")   x = M_PI;
        else if (func == "e")    x = M_E;
    }
    return x;
}
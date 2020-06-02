#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <avr/pgmspace.h>
#include <stdint.h>

namespace Calculator {
enum class Error : uint8_t {
    NONE,
    SYNTAX,
    INVALID_RANGE,
    MISMATCHED_OPERATOR,
    MISMATCHED_PARENTHESES,
    NESTING_NOT_ALLOWED,
    OUT_OF_MEMORY,
    UNKNOWN = 0xFF
};

namespace Tokens {
    enum class Type : uint8_t {
        NUMERIC, SYMBOLIC, OPERATOR, FUNCTION, COMPOUND, SPECIAL
    };

    enum class Assoc : uint8_t {
        LEFT, RIGHT
    };

    struct Token {
        uint8_t order : 4;
        Type    type  : 3;
        Assoc   assoc : 1;
        uint8_t args  : 3;
        uint8_t len   : 5;
        const char*   str;
    };    

    enum Name : uint8_t {
        STOP, COMMA, LEFT_PARENT, RIGHT_PARENT, ZERO, ONE, TWO, THREE,
        FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, POINT, SCI, VAR_X, VAR_Y, 
        VAR_A, VAR_B, VAR_C, VAR_D, VAR_E, VAR_F, ANS, RND, EULER, PI, OR,
        XOR, AND, SUBTRACT, ADD, MODULO, MULTIPLY, DIVIDE, COMBINATION,
        PERMUTATION, POWER, MINUS, PLUS, ROOT, INVERT, FACTORIAL, SINE,
        COSINE, TANGENT, ARCSIN, ARCCOS, ARCTAN, SINH, COSH, TANH, LOG10,
        LN, SQRT, EXPONENT, ABS, MINIMUM, MAXIMUM, SUM, INTEGRAL, DERIVATIVE,
        LENGTH
    };
}

Tokens::Token get(uint8_t id);
const char* test();
void set(uint8_t id, uint8_t pos);
double evaluate();
}

#endif

#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <avr/pgmspace.h>
#include <stdint.h>

/** Place for custom symbols **/
#define EULER_SYMBOL    0x02
#define ROOT_SYMBOL     0x03
#define INTEGRAL_SYMBOL 0x04
#define PERM_SYMBOL     0x05
#define COMBI_SYMBOL    0x06
#define SCI_SYMBOL      0x07
/******************************/

namespace Calculator {
enum class Error : uint8_t {
    NONE,
    EMPTY,
    SYNTAX,
    OVERFLOW,
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
        PERMUTATION, SQR_POW, CUB_POW, POWER, MINUS, PLUS, SQRT, CUBE_ROOT,
        ROOT, INVERT, FACTORIAL, SINE, COSINE, TANGENT, ARCSIN, ARCCOS,
        ARCTAN, SINH, COSH, TANH, LOG10, LN, EXPONENT, POW10, ABS, MINIMUM,
        MAXIMUM, SUM, INTEGRAL, DERIVATIVE, PRODUCT,
        LENGTH
    };

    enum Variable : uint8_t {
        X, Y, A, B, C, D, E, F
    };
}

uint8_t capacity();
void add(uint8_t id);
void insert(uint8_t id, uint8_t pos);
void remove(uint8_t pos);
Tokens::Token at(uint8_t pos);
Tokens::Token get(uint8_t id);
void store(uint8_t var, long double val);
long double recall(uint8_t var);
void clear(bool memory = false);
long double evaluate();
Error check();
uint8_t error_at();
const char* get_err_msg();
}

#endif

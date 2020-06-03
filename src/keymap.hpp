#ifndef KEYMAP_HPP
#define KEYMAP_HPP

enum class Key : uint8_t {
    _2ND   =  0, /**********/ LEFT   =  2, RIGHT  =  3, PWR    =  4,
    /**********/ /**********/ /**********/ /**********/ /**********/
    /**********/ /**********/ SIN    = 12, COS    = 13, TAN    = 14,
    /**********/ /**********/ /**********/ /**********/ /**********/
    SEVEN  = 20, EIGHT  = 21, NINE   = 22, LPAR   = 23, RPAR   = 24,
    FOUR   = 25, FIVE   = 26, SIX    = 27, MUL    = 28, DIV    = 29,
    ONE    = 30, TWO    = 31, THREE  = 32, PLUS   = 33, MINUS  = 34,
    ZERO   = 35, DOT    = 36, EXP    = 37, ANS    = 38, ENTER  = 39,
    NONE   = 0xFF
};

#endif

#include "lcd.hpp"
#include "keypad.hpp"
#include "blink.hpp"
#include "calculator.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

namespace {
const char  left_arrow[] PROGMEM = { 0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02, 0x00 }; // #0
const char right_arrow[] PROGMEM = { 0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08, 0x00 }; // #1
const char euler_const[] PROGMEM = { 0x06, 0x09, 0x1A, 0x1C, 0x18, 0x19, 0x0E, 0x00 }; // #2
const char root_symbol[] PROGMEM = { 0x07, 0x04, 0x04, 0x04, 0x04, 0x14, 0x0C, 0x04 }; // #3
const char integral_ch[] PROGMEM = { 0x02, 0x05, 0x04, 0x04, 0x04, 0x04, 0x14, 0x08 }; // #4
const char perm_symbol[] PROGMEM = { 0x1E, 0x19, 0x19, 0x19, 0x1E, 0x18, 0x18, 0x18 }; // #5
const char comb_symbol[] PROGMEM = { 0x0E, 0x19, 0x18, 0x18, 0x18, 0x18, 0x19, 0x0E }; // #6
const char  sci_symbol[] PROGMEM = { 0x00, 0x00, 0x17, 0x15, 0x15, 0x15, 0x15, 0x17 }; // #7
const char       title[] PROGMEM = { (char) 0xE4, 'S', 'c', 'i', '\0' };

const char* const symbols[] PROGMEM = {
    left_arrow, right_arrow, euler_const,
    root_symbol, integral_ch, perm_symbol,
    comb_symbol, sci_symbol
};

constexpr char LEFT_ARROW  = 0x00;
constexpr char RIGHT_ARROW = 0x01;

enum Modifier : uint8_t {
    ACTIVE = 0b10000000,
    ALPHA  = 0b00000001,
    BETA   = 0b00000010,
    INVERT = 0b00000100,
    HYPER  = 0b00001000,
    RECALL = 0b00010000,
    STORE  = 0b00100000,
    CLEAR  = 0b00000000
};

const char modifiers[] PROGMEM = {
    (char) 0xE0, (char) 0xE2, 'I', 'h', 'R', 'S'
};

uint8_t modifier = Modifier::CLEAR;

/// Shows whether the calculation result is being displayed right now.
bool displaying = false;
uint8_t cursor = 0;
uint8_t window = 0;
}

void show_title() {
    LCD::pos(6, 0);
    LCD::puts_P(title);
    for (uint8_t i = 0; i < 10; i++) {
        _delay_ms(100);
        wdt_reset();
    }
    LCD::clear();
}

void load_symbols() {
    for (uint8_t i = 0; i < ARRAY_SIZE(symbols); i++)
        LCD::define_char_P((const char*) pgm_read_word(&symbols[i]));
}

void print_hex(uint8_t v, bool space = true) {
    uint8_t ch = (v & 0xF0) >> 4;
    if (ch != 0 || !space)
        LCD::putc((ch >= 10 ? 'A' : '0') + (ch % 10));
    ch = v & 0x0F;
    LCD::putc((ch >= 10 ? 'A' : '0') + (ch % 10));
    if (space)
        LCD::putc(' ');
}

void print(long double v) {
    union {
        long double d;
        uint64_t bits;
    } strip;
    strip.d = v;

    for (uint8_t i = 0; i < 8; i++) {
        print_hex((strip.bits >> 56) & 0xFF, false);
        strip.bits <<= 8;
    }
}

void error(Calculator::Error err) {
    if (err == Calculator::Error::EMPTY)
        return;

    LCD::clear(1);
    LCD::puts_P(Calculator::get_err_msg());
}

void clear(bool memory = false) {
    LCD::clear();
    Calculator::clear(memory);
    displaying = false;
    modifier = Modifier::CLEAR;
    cursor = 0;
    window = 0;
}

void print_expr() {
    using namespace Calculator;
    Tokens::Token token;
    uint8_t start = 0, line = 16;

    LCD::clear(0);
    if (window != 0) {
        LCD::putc(LEFT_ARROW);
        start = 1;
        line = 15;
    }

    for (uint8_t i = window, cursor = start; 
            (token = Calculator::at(i)).len != 0 && cursor < line; i++) {
        cursor += token.len - 1;
        LCD::puts_P(token.str);
    }
}

void add(uint8_t id) {
    using namespace Calculator;
    auto token = Calculator::get(id);

    if (Calculator::size() >= Calculator::capacity() - 2)
        return;

    if (displaying) {
        ::clear();
        if (token.type == Tokens::Type::OPERATOR)
            ::add(Tokens::ANS);
    }

    if (token.len > 0) {
        cursor += token.len - 1;
        if (cursor >= 16) {
            if (window == 0)
                cursor++;

            for (Tokens::Token old_token; 
                    (old_token = Calculator::at(window)).len != 0 && cursor > 15; window++)
                cursor -= old_token.len - 1;

            print_expr();
        }

        LCD::puts_P(token.str);
    }

    Calculator::add(id);
    if (token.type == Tokens::Type::FUNCTION 
     || token.type == Tokens::Type::COMPOUND)
        ::add(Tokens::LEFT_PARENT);
}

void remove() {
    if (Calculator::size() == 0)
        return;

    auto token = Calculator::remove(window + cursor - 1);
    cursor -= token.len - 1;
    print_expr();
}

void display(long double val, uint8_t id = Calculator::Tokens::STOP) {
    static char buffer[16];
    auto err = Calculator::check();
    
    if (id != Calculator::Tokens::STOP) {
        auto token = Calculator::get(id);
        LCD::clear(0);
        LCD::puts_P(token.str);
    }

    if (err == Calculator::Error::NONE) {
        LCD::clear(1);
        
        uint8_t digits = fabs(floor(val) - val) < 1e-7 ? 0 : 7;
        if (log10(fabs(val)) >= 13)
            dtostre(val, buffer, 10, 0);
        else
            dtostrf(val, 16, digits, buffer);

        if (digits != 0) {
            uint8_t i, last;
            for (i = 0, last = 0; buffer[i] != '\0'; i++)
                if (buffer[i] != '0' && buffer[i] != '.')
                    last = i;
            LCD::pos(15 - last, 1);
        } else {
            LCD::pos(16 - strlen(buffer), 1);
        }

        LCD::puts(buffer);
    } else {
        error(err);
    }

    displaying = true;    
}

void clear_modifier() {
    modifier = Modifier::CLEAR;
    LCD::pos(0, 1);
    LCD::putc(' ');
    LCD::pos(cursor, 0);
}

void set_modifier(Modifier mod) {
    if (modifier & mod) {
        clear_modifier();
        return;
    }

    modifier = Modifier::ACTIVE | mod;
    LCD::pos(0, 1);
    for (uint8_t i = 0, n = (uint8_t) mod; n != 0; i++, n >>= 1) {
        if (n & 1)
            LCD::putc(pgm_read_byte(&modifiers[i]));
    }
    LCD::pos(cursor, 0);
}

long double finalize() {
    if (!displaying)
        ::add(Calculator::Tokens::STOP);
    auto result = Calculator::evaluate();
    display(result);
    clear_modifier();
    return result;
}

void interpret(Keypad::Key key) {
    using namespace Calculator;
    using namespace Keypad;
    uint8_t new_token = Tokens::STOP;

    switch (key) {
        case Key::A1:
            set_modifier(Modifier::ALPHA);
            return;
        case Key::B1:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::POW10 : Tokens::LOG10;
            break;
        case Key::C1:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::DERIVATIVE : Tokens::INTEGRAL;
            break;
        case Key::D1:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::INVERT : Tokens::FACTORIAL;
            break;
        case Key::E1:
            if (modifier & Modifier::ALPHA)
                ;//turn_off();
            else
                ::clear(true);
            return;

        case Key::A2:
            set_modifier(Modifier::BETA);
            return;
        case Key::B2:
            new_token = (modifier & Modifier::ALPHA) ? 
                Tokens::EXPONENT : Tokens::LN;
            break;
        case Key::C2:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::PRODUCT : Tokens::SUM;
            break;
        case Key::D2:
            // cursor left
            break;
        case Key::E2:
            // cursor right
            break;

        case Key::A3:
            set_modifier(Modifier::STORE);
            return;
        case Key::B3:
            set_modifier(modifier & Modifier::ALPHA ? 
                Modifier::HYPER : Modifier::INVERT);
            return;
        case Key::C3:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::ABS : (modifier & Modifier::HYPER) ?
                Tokens::SINH : (modifier & Modifier::INVERT) ?
                Tokens::ARCSIN : Tokens::SINE;
            break;
        case Key::D3:
            new_token = (modifier & Modifier::ALPHA) ? 
                Tokens::MINIMUM : (modifier & Modifier::HYPER) ?
                Tokens::COSH : (modifier & Modifier::INVERT) ?
                Tokens::ARCCOS : Tokens::COSINE;
            break;
        case Key::E3:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::MAXIMUM : (modifier & Modifier::HYPER) ?
                Tokens::TANH : (modifier & Modifier::INVERT) ?
                Tokens::ARCTAN : Tokens::TANGENT;
            break;

        case Key::A4:
            set_modifier(Modifier::RECALL);
            return;
        case Key::B4:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::CUB_POW : (modifier & Modifier::BETA) ?
                Tokens::POWER : Tokens::SQR_POW;
            break;
        case Key::C4:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::CUBE_ROOT : (modifier & Modifier::BETA) ?
                Tokens::ROOT : Tokens::SQRT;
            break;
        case Key::D4:
            if (modifier & Modifier::RECALL) {
                display(Calculator::recall(Tokens::Variable::X), Tokens::VAR_X);
            } else if (modifier & Modifier::STORE) {
                Calculator::store(Tokens::Variable::X, finalize());
            } else {
                new_token = (modifier & Modifier::ALPHA) ?
                    Tokens::COMMA : (modifier & Modifier::BETA) ?
                    Tokens::VAR_X : Tokens::LEFT_PARENT;
                break;
            }
            return;
        case Key::E4:
            if (modifier & Modifier::RECALL) {
                display(Calculator::recall(Tokens::Variable::Y), Tokens::VAR_Y);
            } else if (modifier & Modifier::STORE) {
                Calculator::store(Tokens::Variable::Y, finalize());
            } else {
                new_token = (modifier & Modifier::BETA) ?
                    Tokens::VAR_Y : Tokens::RIGHT_PARENT;
                break;
            }
            return;
        case Key::A5:
            if (modifier & Modifier::RECALL) {
                display(Calculator::recall(Tokens::Variable::A), Tokens::VAR_A);
            } else if (modifier & Modifier::STORE) {
                Calculator::store(Tokens::Variable::A, finalize());
            } else {
                new_token = (modifier & Modifier::BETA) ?
                    Tokens::VAR_A : Tokens::SEVEN;
                break;
            }
            return;
        case Key::B5:
            if (modifier & Modifier::RECALL) {
                display(Calculator::recall(Tokens::Variable::B), Tokens::VAR_B);
            } else if (modifier & Modifier::STORE) {
                Calculator::store(Tokens::Variable::B, finalize());
            } else {
                new_token = (modifier & Modifier::BETA) ?
                    Tokens::VAR_B : Tokens::EIGHT;
                break;
            }
            return;
        case Key::C5:
            if (modifier & Modifier::RECALL) {
                display(Calculator::recall(Tokens::Variable::C), Tokens::VAR_C);
            } else if (modifier & Modifier::STORE) {
                Calculator::store(Tokens::Variable::X, finalize());
            } else {
                new_token = (modifier & Modifier::BETA) ?
                    Tokens::VAR_C : Tokens::NINE;
                break;
            }
            return;
        case Key::D5:
            remove();
            break;
        case Key::E5:
            ::clear();
            return;

        case Key::A6:
            if (modifier & Modifier::RECALL) {
                display(Calculator::recall(Tokens::Variable::D), Tokens::VAR_D);
            } else if (modifier & Modifier::STORE) {
                Calculator::store(Tokens::Variable::D, finalize());
            } else {
                new_token = (modifier & Modifier::BETA) ?
                    Tokens::VAR_D : Tokens::FOUR;
                break;
            }
            return;
        case Key::B6:
            if (modifier & Modifier::RECALL) {
                display(Calculator::recall(Tokens::Variable::E), Tokens::VAR_E);
            } else if (modifier & Modifier::STORE) {
                Calculator::store(Tokens::Variable::E, finalize());
            } else {
                new_token = (modifier & Modifier::BETA) ?
                    Tokens::VAR_E : Tokens::FIVE;
                break;
            }
            return;
        case Key::C6:
            if (modifier & Modifier::RECALL) {
                display(Calculator::recall(Tokens::Variable::F), Tokens::VAR_F);
            } else if (modifier & Modifier::STORE) {
                Calculator::store(Tokens::Variable::F, finalize());
            } else {
                new_token = (modifier & Modifier::BETA) ?
                    Tokens::VAR_F : Tokens::SIX;
                break;
            }
            return;
        case Key::D6:
            if (modifier & Modifier::ALPHA) {
                ;// turn off backlight
            } else if (modifier & Modifier::BETA) {
                ;// turn on backlight
            } else {
                new_token = Tokens::MULTIPLY;
                break;
            }
            return;
        case Key::E6:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::MODULO : Tokens::DIVIDE;
            break;
        
        case Key::A7:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::AND : Tokens::ONE;
            break;
        case Key::B7:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::OR : Tokens::TWO;
            break;
        case Key::C7:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::XOR : Tokens::THREE;
            break;
        case Key::D7:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::PERMUTATION : Tokens::ADD;
            break;
        case Key::E7:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::COMBINATION : Tokens::SUBTRACT;
            break;
        
        case Key::A8:
            new_token = Tokens::ZERO;
            break;
        case Key::B8:
            new_token = (modifier & Modifier::ALPHA) ?
                Tokens::RND : Tokens::POINT;
            break;
        case Key::C8:
            new_token = (modifier & Modifier::ALPHA) ? 
                Tokens::PI : (modifier & Modifier::BETA) ?
                Tokens::EULER : Tokens::SCI;
            break;
        case Key::D8:
            new_token = Tokens::ANS;
            break;
        case Key::E8:
            finalize();
            return;
        default:
            return;
    }

    if (modifier & Modifier::ACTIVE)
        clear_modifier();

    if (new_token != Tokens::STOP)
        ::add(new_token);
}

void init() {
    MCUSR &= ~_BV(WDRF);
    WDTCSR |= _BV(WDCE) | _BV(WDIE);
    WDTCSR = _BV(WDE) | _BV(WDP3) | _BV(WDP0);

    PRR = _BV(PRTWI) | _BV(PRSPI) | _BV(PRUSART0) | _BV(PRADC);
}

int main() {
    init();
    LCD::init();
    Blink::init();
    Keypad::init();
    load_symbols();
    clear();

    show_title();
    Blink::start();
    sei();

    for (;;) {
        wdt_reset();

        auto key = Keypad::scan();
        if (key == Keypad::Key::NONE)
            continue;
        
        interpret(key);
    }

    return 0;
}

ISR (WDT_vect) {
    if (Calculator::check() != Calculator::Error::NONE)
        Calculator::clear();
}

/**
 * TODO
 *  number parses should handle negative exponent
 *  incorrect way of determining if the operator is unary
 *  cursor operations needs to be implemented
 *  backlight operations not implemented
 *  on/off not implemented
 *  proper print for float64
 */

/**
 * FORMAT
 *  16 char display
 *  0123456789012345
 *  M -1234567890123
 *  M -1.234567e+300
 */

/*

Cursor scrolling example:
|0123456789012345| pos | cur | win |
|_               |  0  |  0  |  0  |
|sin(_           |  2  |  4  |  0  |
|sin(2_          |  3  |  5  |  0  |
|sin(2x_         |  4  |  6  |  0  |
|sin(2x+_        |  5  |  7  |  0  |
|sin(2x+5_       |  6  |  8  |  0  |
|sin(2x+5+_      |  7  |  9  |  0  |
|sin(2x+5+1_     |  8  | 10  |  0  |
|sin(2x+5+1+_    |  9  | 11  |  0  |
|sin(2x+5+1+2_   | 10  | 12  |  0  |
|sin(2x+5+1+2+_  | 11  | 13  |  0  |
|sin(2x+5+1+2+3_ | 12  | 14  |  0  |
|sin(2x+5+1+2+3+_| 13  | 15  |  0  |
|<(2x+5+1+2+3+4_ | 14  | 14  |  1  |
|<(2x+5+1+2+3+4+_| 15  | 15  |  1  |
|<5+1+2+3+4+cos(_| 16  | 15  |  5  |
|<+1+2+3+4+cos(3_| 17  | 15  |  6  |
|<+2+3+4+cos(3^2_| 18  | 15  |  8  |

|0123456789012345| pos | cur | win |
|_               |  0  |  0  |  0  |
|sin(_           |  2  |  4  |  0  |
|sin(cos(_       |  4  |  8  |  0  |
|sin(cos(tan(_   |  6  |  C  |  0  |
|<(cos(tan(sin(_ |  8  |  E  |  1  |
|<(cos(tan(sin(2_|  9  |  F  |  1  |
|<cos(tan(sin(2X_|  A  |  F  |  2  |

*/
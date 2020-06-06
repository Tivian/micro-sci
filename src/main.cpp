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

const char  left_arrow[] PROGMEM = { 0x00, 0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02 }; // #0
const char right_arrow[] PROGMEM = { 0x00, 0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08 }; // #1
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
uint8_t pos = 0;

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
        uint64_t raw;
    } strip;
    strip.d = v;
    
    decltype(strip.raw) mask = 0xFF;
    uint8_t shift = (sizeof(strip.d) * 8) - 8;
    for (uint8_t i = 0; i < sizeof(strip.d); i++, shift -= 8)
        print_hex((strip.raw & (mask << shift)) >> shift, false);
}

void error(Calculator::Error err) {
    if (err == Calculator::Error::EMPTY)
        return;

    LCD::clear(1);
    LCD::puts_P(Calculator::get_msg());
}

void clear(bool memory = false) {
    LCD::clear();
    Calculator::clear(memory);
    displaying = false;
    modifier = Modifier::CLEAR;
    cursor = 0;
    pos = 0;
}

void add(uint8_t id) {
    auto token = Calculator::get(id);

    if (displaying) {
        clear();
        if (token.type == Calculator::Tokens::Type::OPERATOR)
            ::add(Calculator::Tokens::ANS);
    }

    if (token.len > 0) {
        LCD::puts_P(token.str);
        cursor += token.len - 1;

        if (cursor >= 16) {

        }
    }

    Calculator::add(id);
    if (token.type == Calculator::Tokens::Type::FUNCTION 
     || token.type == Calculator::Tokens::Type::COMPOUND)
        ::add(Calculator::Tokens::LEFT_PARENT);

    pos++;
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
                if (buffer[i] != '0')
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
            new_token = Tokens::SUM;
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
            new_token = Tokens::POWER;
            break;
        case Key::C4:
            new_token = Tokens::ROOT;
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
            // delete
            break;
        case Key::E5:
            // clear
            break;

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

int main() {
    MCUSR &= ~_BV(WDRF);
    WDTCSR |= _BV(WDCE) | _BV(WDIE);
    WDTCSR = _BV(WDE) | _BV(WDP3) | _BV(WDP0);

    LCD::init();
    Blink::init();
    Keypad::init();
    load_symbols();
    clear();

    //show_title();
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
 *  Ans is broken for some reason
 *  cursor operations needs to be implemented
 *  integral doesn't work
 *  derivative gives syntax ERROR
 *  backlight operations not implemented
 *  store, recall not implemented
 *  on/off not implemented
 */

/**
 * FORMAT
 *  16 char display
 *  0123456789012345
 *  M -1234567890123
 *  M -1.234567e+300
 */
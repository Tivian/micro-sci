#include "lcd.hpp"
#include "keypad.hpp"
#include "blink.hpp"
#include "calculator.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdlib.h>

const char  left_arrow[] PROGMEM = { 0x00, 0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02 }; // #0
const char right_arrow[] PROGMEM = { 0x00, 0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08 }; // #1
const char euler_const[] PROGMEM = { 0x06, 0x09, 0x1A, 0x1C, 0x18, 0x19, 0x0E, 0x00 }; // #2
const char root_symbol[] PROGMEM = { 0x07, 0x04, 0x04, 0x04, 0x04, 0x14, 0x0C, 0x04 }; // #3
const char integral_ch[] PROGMEM = { 0x02, 0x05, 0x04, 0x04, 0x04, 0x04, 0x14, 0x08 }; // #4
const char perm_symbol[] PROGMEM = { 0x1E, 0x19, 0x19, 0x19, 0x1E, 0x18, 0x18, 0x18 }; // #5
const char comb_symbol[] PROGMEM = { 0x0E, 0x19, 0x18, 0x18, 0x18, 0x18, 0x19, 0x0E }; // #6
const char    x_symbol[] PROGMEM = { 0x00, 0x19, 0x06, 0x04, 0x04, 0x0C, 0x13, 0x00 }; // #7
const char       title[] PROGMEM = { (char) 0xE4, 'S', 'c', 'i', '\0' };

const char* const symbols[] PROGMEM = {
    left_arrow, right_arrow, euler_const,
    root_symbol, integral_ch, perm_symbol,
    comb_symbol, x_symbol
};

/// Shows whether the calculation result is being displayed right now.
bool displaying = false;

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

void add(uint8_t id) {    
    auto token = Calculator::get(id);
    if (token.len > 0)
        LCD::puts_P(token.str);
    if (token.type == Calculator::Tokens::Type::FUNCTION 
     || token.type == Calculator::Tokens::Type::COMPOUND)
        Calculator::add(Calculator::Tokens::LEFT_PARENT);
    Calculator::add(id);
}

void display(long double val) {
    static char buffer[16];
    auto err = Calculator::check();
    
    if (err == Calculator::Error::NONE) {
        //dtostrf(val, 16, 10, buffer);
        dtostre(val, buffer, 16, 0);
        LCD::clear(1);
        LCD::pos(3, 1);
        LCD::puts(buffer);
        //LCD::pos(0, 1);
        //print(val);
    } else {
        error(err);
    }

    displaying = true;    
}

void clear() {
    LCD::clear();
    Calculator::clear();
    displaying = false;
}

enum Modifier : uint8_t {
    ACTIVE = 0b10000000,
    SECOND = 0b00000001,
    ALPHA  = 0b00000010,
    INVERT = 0b00000100,
    RECALL = 0b00001000,
    STORE  = 0b00010000,
    CLEAR  = 0b00000000
};

void interpret(Keypad::Key key) {
    using namespace Calculator;
    using namespace Keypad;
    uint8_t modifier = Modifier::CLEAR;
    uint8_t new_token = Tokens::STOP;

    switch (key) {
        case Key::A1:
            modifier = Modifier::ACTIVE | Modifier::SECOND;
            break;
        case Key::B1:
            break;
        case Key::C1:
            new_token = (modifier & Modifier::SECOND) ?
                Tokens::DERIVATIVE : Tokens::INTEGRAL;
            break;
        case Key::D1:
            new_token = Tokens::FACTORIAL;
            break;
        case Key::E1:
            if (modifier & Modifier::SECOND)
                ;//turn_off();
            else
                ::clear();
            return;

        case Key::A2:
            modifier = Modifier::ACTIVE | Modifier::ALPHA;
            break;
        case Key::B2:
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
            modifier = Modifier::ACTIVE | Modifier::STORE;
            break;
        case Key::B3:
            modifier = Modifier::ACTIVE | Modifier::INVERT;
            break;
        case Key::C3:
            new_token = Tokens::SINE;
            break;
        case Key::D3:
            new_token = Tokens::COSINE;
            break;
        case Key::E3:
            new_token = Tokens::TANGENT;
            break;

        case Key::A4:
            modifier = Modifier::ACTIVE | Modifier::RECALL;
            break;
        case Key::B4:
            new_token = (modifier & Modifier::SECOND) ? 
                Tokens::EXPONENT : Tokens::LN;
            break;
        case Key::C4:
            new_token = /*(modifier & Modifier::SECOND) ?
                Tokens::POW10 : */Tokens::LOG10;
            break;
        case Key::D4:
            new_token = Tokens::LEFT_PARENT;
            break;
        case Key::E4:
            new_token = Tokens::RIGHT_PARENT;
            break;

        case Key::A5:
            new_token = Tokens::SEVEN;
            break;
        case Key::B5:
            new_token = Tokens::EIGHT;
            break;
        case Key::C5:
            new_token = Tokens::NINE;
            break;
        case Key::D5:
            // delete
            break;
        case Key::E5:
            // clear
            break;

        case Key::A6:
            new_token = Tokens::FOUR;
            break;
        case Key::B6:
            new_token = Tokens::FIVE;
            break;
        case Key::C6:
            new_token = Tokens::SIX;
            break;
        case Key::D6:
            new_token = Tokens::MULTIPLY;
            break;
        case Key::E6:
            new_token = Tokens::DIVIDE;
            break;

        
        case Key::A7:
            new_token = Tokens::ONE;
            break;
        case Key::B7:
            new_token = Tokens::TWO;
            break;
        case Key::C7:
            new_token = Tokens::THREE;
            break;
        case Key::D7:
            new_token = Tokens::ADD;
            break;
        case Key::E7:
            new_token = Tokens::SUBTRACT;
            break;
        
        case Key::A8:
            new_token = Tokens::ZERO;
            break;
        case Key::B8:
            new_token = (modifier & Modifier::SECOND) ?
                Tokens::RND : Tokens::POINT;
            break;
        case Key::C8:
            new_token = (modifier & Modifier::SECOND) ? 
                Tokens::PI : (modifier & Modifier::ALPHA) ?
                Tokens::EULER : Tokens::SCI;
            break;
        case Key::D8:
            new_token = Tokens::ANS;
            break;
        case Key::E8:
            if (!displaying)
                ::add(Tokens::STOP);
            display(Calculator::evaluate());
            return;
        default:
            return;
    }

    if (displaying)
        ::clear();
    else if (modifier & Modifier::ACTIVE)
        modifier = Modifier::CLEAR;

    ::add(new_token);
}

int main() {
    MCUSR &= ~_BV(WDRF);
    WDTCSR |= _BV(WDCE) | _BV(WDIE);
    WDTCSR = _BV(WDE) | _BV(WDP3) | _BV(WDP0);

    LCD::init();
    Blink::init();
    Keypad::init();

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
 *  - keyboard matrix support
 *  - greater long double precision
 *  - menu
 * 
 * Target
 *  10-digit precision
 * 
 * Need function for displaying the IEEE754 64-bit numbers
 *  max 16 characters, precision 10 digits
 */

/**
 * FORMAT
 *  XXXXXXXXXX
 *  if more then use sci notation
 *  +X.XXXXXXXXXeXXX
 */

/**  KEYBOARD LAYOUT
 *     1   2   3   4   5
 *   ┌───┬───┬───┬───┬───┐
 * 1 │2nd│   │   │   │PWR│
 *   ├───┼───┼───┼───┼───┤
 * 2 │   │   │   │   │DEL│
 *   ├───┼───┼───┼───┼───┤
 * 3 │   │   │SIN│COS│TAN│
 *   ├───┼───┼───┼───┼───┤
 * 4 │   │   │   │   │   │
 *   ├───┼───┼───┼───┼───┤
 * 5 │ 7 │ 8 │ 9 │ ( │ ) │
 *   ├───┼───┼───┼───┼───┤
 * 6 │ 4 │ 5 │ 6 │ x │ / │
 *   ├───┼───┼───┼───┼───┤
 * 7 │ 1 │ 2 │ 3 │ + │ - │
 *   ├───┼───┼───┼───┼───┤
 * 8 │ 0 │ . │SCI│ANS│ = │
 *   └───┴───┴───┴───┴───┘
 */
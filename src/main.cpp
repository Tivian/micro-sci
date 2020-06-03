#include "lcd.hpp"
#include "keypad.hpp"
#include "blink.hpp"
#include "calculator.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "loader.hpp"
#include <stdlib.h>
#include <math.h>

const char  left_arrow[] PROGMEM = { 0x00, 0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02 };
const char right_arrow[] PROGMEM = { 0x00, 0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08 };
const char       title[] PROGMEM = { (char) 0xE4, 'S', 'c', 'i', '\0' };

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

void interpret(Keypad::Key key) {
    using namespace Calculator;
    using namespace Keypad;
    uint8_t new_token = Tokens::STOP;

    switch (key) {
        case Key::E1:
            ::clear();
            return;
        case Key::A8:
            new_token = Tokens::ZERO;
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
        case Key::A6:
            new_token = Tokens::FOUR;
            break;
        case Key::B6:
            new_token = Tokens::FIVE;
            break;
        case Key::C6:
            new_token = Tokens::SIX;
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
        case Key::B8:
            new_token = Tokens::POINT;
            break;
        case Key::C8:
            new_token = Tokens::SCI;
            break;
        case Key::D8:
            new_token = Tokens::ANS;
            break;
        case Key::D7:
            new_token = Tokens::ADD;
            break;
        case Key::E7:
            new_token = Tokens::SUBTRACT;
            break;
        case Key::D6:
            new_token = Tokens::MULTIPLY;
            break;
        case Key::E6:
            new_token = Tokens::DIVIDE;
            break;
        case Key::D4:
            new_token = Tokens::LEFT_PARENT;
            break;
        case Key::E4:
            new_token = Tokens::RIGHT_PARENT;
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
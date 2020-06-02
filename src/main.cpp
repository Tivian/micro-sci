#include "lcd.hpp"
#include "keypad.hpp"
//#include "keymap.hpp"
#include "blink.hpp"
#include "calculator.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "loader.hpp"
#include <stdlib.h>

const char      cursor[] PROGMEM = { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 };
const char  left_arrow[] PROGMEM = { 0x00, 0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02 };
const char right_arrow[] PROGMEM = { 0x00, 0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08 };
const char       title[] PROGMEM = { (char) 0xE4, 'S', 'c', 'i', '\0' };

void show_title() {
    LCD::pos(6, 0);
    LCD::puts_P(title);
    //_delay_ms(1000);
    for (uint8_t i = 0; i < 10; i++) {
        _delay_ms(100);
        wdt_reset();
    }
    LCD::clear();
}

void print_hex(uint8_t v) {
    uint8_t ch = (v & 0xF0) >> 4;
    if (ch != 0)
        LCD::putc((ch >= 10 ? 'A' : '0') + (ch % 10));
    ch = v & 0x0F;
    LCD::putc((ch >= 10 ? 'A' : '0') + (ch % 10));
    LCD::putc(' ');
}

uint8_t id = 1;
void print() {
    LCD::clear();
    using namespace Calculator::Tokens;

    auto token = Calculator::get(id);
    print_hex(id);
    print_hex(token.order);
    print_hex((uint8_t) token.type);
    print_hex((uint8_t) token.assoc);
    print_hex(token.args);
    print_hex(token.len);
    LCD::pos(0, 1);
    LCD::puts_P(token.str);
}

void interpret(uint8_t key) {
    using namespace Calculator;

    if (key == 35) {
        id--;
        if (id == 1)
            id = Tokens::LENGTH - 1;
    } else if (key == 36) {
        id++;
        if (id >= Tokens::LENGTH)
            id = 1;
    } else {
        return;
    }

    print();
}

int main() {
    MCUSR &= ~_BV(WDRF);
    WDTCSR |= _BV(WDCE) | _BV(WDE);
    WDTCSR = _BV(WDE) | _BV(WDP2) | _BV(WDP0);

    LCD::init();
    Blink::init();
    Keypad::init();

    show_title();
    Blink::start();
    sei();

    char buffer[16];
    Calculator::set(Calculator::Tokens::PI, 0);
    Calculator::set(Calculator::Tokens::EULER, 1);
    Calculator::set(Calculator::Tokens::STOP, 2);
    dtostrf(Calculator::evaluate(), 16, 8, buffer);
    LCD::puts(buffer);

    //print();
    for (;;) {
        wdt_reset();

        uint8_t key = Keypad::scan();
        if (key == Keypad::NONE)
            continue;
        
        //interpret(key);
    }

    return 0;
}

/**
 * TODO
 *  - keyboard matrix support
 *  - greater double precision
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
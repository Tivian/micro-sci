#include "keypad.hpp"
#include <util/delay.h>

using namespace Keypad;
namespace {
    Key last = Key::NONE;
}

void Keypad::init() {
    for (uint8_t i = 0; i < ARRAY_SIZE(rows); i++)
        *rows[i].port |= _BV(rows[i].pin);

    for (uint8_t i = 0; i < ARRAY_SIZE(cols); i++)
        *cols[i].port &= ~_BV(cols[i].pin);
}

Key Keypad::scan() {
    uint8_t pressed = 0;
    Key keystroke = Key::NONE;

    for (uint8_t c = 0; c < ARRAY_SIZE(cols); c++) {
        DDR(*cols[c].port) |= _BV(cols[c].pin);

        for (uint8_t r = 0; r < ARRAY_SIZE(rows); r++) {
            if (bit_is_clear(PIN(*rows[r].port), rows[r].pin)) {
                keystroke = static_cast<Key>(c + r * ARRAY_SIZE(cols));
                pressed++;
            }
        }

        DDR(*cols[c].port) &= ~_BV(cols[c].pin);
    }

    _delay_ms(KEYPAD_DEBOUNCE);

    bool is_new = pressed == 1 && keystroke != last;
    last = keystroke;
    return is_new ? keystroke : Key::NONE;
}

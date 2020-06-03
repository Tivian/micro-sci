#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "utility.hpp"
#include <avr/io.h>

#define KEYPAD_DEBOUNCE 50 // ms

#define KEYPAD_C1 { &PORTB, PB0 }
#define KEYPAD_C2 { &PORTB, PB1 }
#define KEYPAD_C3 { &PORTB, PB2 }
#define KEYPAD_C4 { &PORTC, PC0 }
#define KEYPAD_C5 { &PORTC, PC1 }

#define KEYPAD_R1 { &PORTD, PD7 }
#define KEYPAD_R2 { &PORTD, PD6 }
#define KEYPAD_R3 { &PORTB, PB7 }
#define KEYPAD_R4 { &PORTD, PD4 }
#define KEYPAD_R5 { &PORTD, PD3 }
#define KEYPAD_R6 { &PORTD, PD2 }
#define KEYPAD_R7 { &PORTD, PD1 }
#define KEYPAD_R8 { &PORTD, PD0 }

namespace Keypad {
constexpr static pin_t cols[] = {
    KEYPAD_C1, KEYPAD_C2, KEYPAD_C3,
    KEYPAD_C4, KEYPAD_C5
};

constexpr static pin_t rows[] = {
    KEYPAD_R1, KEYPAD_R2, KEYPAD_R3,
    KEYPAD_R4, KEYPAD_R5, KEYPAD_R6,
    KEYPAD_R7, KEYPAD_R8
};

enum class Key : uint8_t {
    A1, B1, C1, D1, E1,
    A2, B2, C2, D2, E2,
    A3, B3, C3, D3, E3,
    A4, B4, C4, D4, E4,
    A5, B5, C5, D5, E5,
    A6, B6, C6, D6, E6,
    A7, B7, C7, D7, E7,
    A8, B8, C8, D8, E8,
    NONE = 0xFF
};

void init();
Key scan();
}

#endif

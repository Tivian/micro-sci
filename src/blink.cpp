#include "blink.hpp"
#include "lcd.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>

namespace Blink {
namespace {
    volatile bool blink = false;
    volatile uint8_t timeout = 0;
    volatile uint8_t delay = 0;
}

void init(uint8_t delay) {
    speed(delay);

    OCR0A = 0xFF;
    TCCR0A |= _BV(WGM01);
    TCCR0B |= _BV(CS02) | _BV(CS00);
}

void start() {
    TIMSK0 |= _BV(OCIE0A);
    blink = true;
    timeout = 0;
}

void stop() {
    TIMSK0 &= ~_BV(OCIE0A);
}

void speed(uint8_t delay) {
    Blink::delay = delay;
}
}

ISR (TIMER0_COMPA_vect) {
    if (Blink::timeout++ == Blink::delay) {
        LCD::mode(true, Blink::blink = !Blink::blink);
        Blink::timeout = 0;
    }
}
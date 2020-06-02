#ifndef BLINK_HPP
#define BLINK_HPP

#include <stdint.h>

namespace Blink {
void init(uint8_t delay = 16);
void start();
void stop();
void speed(uint8_t delay);
}

#endif

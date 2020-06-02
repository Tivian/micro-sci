#ifndef RAND_HPP
#define RAND_HPP

#include <stdint.h>

namespace Random {
void init(uint8_t seed);
uint8_t next();
}

#endif
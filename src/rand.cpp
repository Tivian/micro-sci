#include "rand.hpp"

namespace {
    uint8_t a = 0x5a;
    uint8_t b = 0xb6;
    uint8_t c = 0x7c;
    uint8_t x = 0;
}

void Random::init(uint8_t seed) {
	a ^= seed ^ 0xAA;
	b ^= seed ^ 0x55;
	c ^= seed ^ 0xDB;
	next();
}

uint8_t Random::next() {
	x++;
	a = a ^ c ^ x;
	b = b + a;
	c = (c + (b >> 1)) ^ a;
	return c;
}
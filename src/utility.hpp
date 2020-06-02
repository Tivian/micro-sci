#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#ifndef DDR
#define DDR(port) (*(&(port) - 1))
#endif

#ifndef PIN
#define PIN(port) (*(&(port) - 2))
#endif

struct pin_t {
    volatile uint8_t* port;
    uint8_t pin;
};

#endif

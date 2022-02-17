#ifndef STACK_HPP
#define STACK_HPP

#include <stdint.h>

#define STACK_SIZE 64

namespace Stack {
void clear();
uint8_t size();
template <typename T> T peek();
template <typename T> T pop();
template <typename T> void push(T val);
}

#endif

#include "stack.hpp"

namespace {
    union {
        uint8_t ints[STACK_SIZE * sizeof(double)];
        double real[STACK_SIZE];
    } stack;

    uint8_t top = 0;
}

void Stack::clear() {
    top = 0;
}

uint16_t Stack::size() {
    return top;
}

template<>
uint8_t Stack::peek() {
    return stack.ints[top - 1];
}

template<>
double Stack::peek() {
    return stack.real[top - 1];
}

template<>
uint8_t Stack::pop() {
    return stack.ints[--top];
}

template<>
double Stack::pop() {
    return stack.real[--top];
}

template<>
void Stack::push(uint8_t val) {
    stack.ints[top++] = val;
}

template<>
void Stack::push(double val) {
    stack.real[top++] = val;
}

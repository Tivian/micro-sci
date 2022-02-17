#ifndef LOADER_HPP
#define LOADER_HPP

namespace Loader {
template <typename T>
void read(const T* src, T& dest) {
    memcpy_P(&dest, src, sizeof(T));
}

template <typename T>
T get(const T* src) {
    static T temp;
    memcpy_P(&temp, src, sizeof(T));
    return temp;
}
}

#endif
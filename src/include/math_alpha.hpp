//===----- math.hpp ----- Math abstraction definitions ----------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
///  Consists of mathematical abstractions for vectors, related operations etc.
///
//===----------------------------------------------------------------------===//
#ifndef math_alpha_hpp
#define math_alpha_hpp
#include <array>
#include <algorithm>
#include <stdexcept>
namespace alpha {

template <unsigned int size, typename T> class vec {
    std::array<T, size> values;

  public:
    vec() { std::fill(values.begin(), values.end(), 0); }
    vec(const T &xx) { std::fill(values.begin(), values.end(), xx); }
    vec(std::initializer_list<T> xs) {
        int id = 0;
        if (size < xs.size()) {
            throw std::length_error(
                "Number of the initializers exceeds the length of the vector");
        }
        for (auto elem : xs) {
            values[id++] = elem;
        }
    }
};
using vec3f = vec<3, float>;
}
#endif

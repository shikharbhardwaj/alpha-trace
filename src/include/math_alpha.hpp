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
#include <stdexcept>
#include <algorithm>
namespace alpha {
template <typename T> class vec3 {
  public:
    T x, y, z;
    vec3() = default;
    vec3(const T &xx) : x(xx), y(xx), z(xx) {}
    vec3(const T &xx, const T &yy, const T &zz) : x(xx), y(yy), z(zz) {}
    vec3(std::initializer_list<T> xs) {
        if (xs.size() > 3) {
            throw std::length_error(
                "Number of elements in initializer greater than 3");
        }
    }
    T mod() { return sqrt(x * x, y * y, z * z); }
    T dot(const vec3<T> &v) { return v.x * x + v.y * y + v.z * z; }
    void norm() {
        T mag = mod();
        if (mag != 0) {
            T inv_mag = 1.0 / mag;
            x *= inv_mag, y *= inv_mag, z *= inv_mag;
        }
    }
    vec3<T> cross(const vec3<T> &v) {
        return vec3<T>(y * v.z - z * v.y, x * v.z - z * v.x, x * v.y - y * v.x);
    }
    vec3<T> operator+(const vec3<T> &v) const {
        return vec3<T>(x + v.x, y + v.y, z + v.z);
    }
    vec3<T> operator-(const vec3<T> &v) const {
        return vec3<T>(x - v.x, y - v.y, z - v.z);
    }
    vec3<T> operator*(const T &v) const { return vec3<T>(x * v, y * v, z * v); }
};
}
#endif

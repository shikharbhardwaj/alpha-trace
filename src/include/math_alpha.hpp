//===----- math.hpp ----- Math abstraction definitions ----------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
///  Consists of definitions for vectors, matrices & related operations
///
//===----------------------------------------------------------------------===//
#ifndef math_alpha_hpp
#define math_alpha_hpp
#include <iostream>
namespace alpha {
template <typename T> class vec3 {
  public:
    T x, y, z;
    vec3() : x(0), y(0), z(0) {}
    vec3(const T &xx) : x(xx), y(xx), z(xx) {}
    vec3(const T &xx, const T &yy, const T &zz) : x(xx), y(yy), z(zz) {}
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
template <typename T> class mat44 {
    // Default initialize the matrix to a unit matrix
    T M[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

  public:
    mat44() = default;
    mat44(std::initializer_list<std::initializer_list<T>> xs) {
        uint8_t r = 0, c = 0;
        for (auto row : xs) {
            for (auto elem : row) {
                M[r][c++] = elem;
            }
            r++, c = 0;
        }
    }
    const T *operator[](uint8_t i) const { return M[i]; };
    T *operator[](uint8_t i) { return M[i]; };
    void dump() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << M[i][j] << " : ";
            }
            std::cout << "\n";
        }
    }
    mat44 operator*(const mat44 &rhs) const {
        mat44 res;
        for (uint8_t i = 0; i < 4; i++) {
            for (uint8_t j = 0; j < 4; j++) {
                res[i][j] = M[i][0] * rhs[0][j] + M[i][1] * rhs[1][j] +
                            M[i][2] * rhs[2][j] + M[i][3] * rhs[3][j];
            }
        }
        return res;
    }
    void mult_vec_mat(const vec3<T> &src, const vec3<T> &dst) {
        dst.x = src.x * M[0][0] + src.y * M[1][0] + src.z * M[2][0] + M[3][0];
        dst.y = src.x * M[0][1] + src.y * M[1][1] + src.z * M[2][0] + M[3][1];
        dst.z = src.x * M[0][2] + src.y * M[1][2] + src.z * M[2][0] + M[3][2];
        T w = src.x * M[0][3] + src.y * M[1][3] + src.z * M[2][0] + M[3][3];
        if (w != 0 && w != 1) {
            // Normalize if not homogenous
            dst.x /= w;
            dst.y /= w;
            dst.z /= w;
        }
    }
};
}
#endif

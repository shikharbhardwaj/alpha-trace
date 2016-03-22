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
#include <cmath>
namespace alpha {
template <typename T> class vec3 {
    // A 3 tuple
  public:
    T x, y, z;
    vec3() : x(0), y(0), z(0) {}
    vec3(const T &xx) : x(xx), y(xx), z(xx) {}
    vec3(const T &xx, const T &yy, const T &zz) : x(xx), y(yy), z(zz) {}
    T mod() { return sqrt(x * x, y * y, z * z); }
    T dot(const vec3<T> &v) { return v.x * x + v.y * y + v.z * z; }
    void normalize() {
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
    // Represents a 4x4 matrix
    // Default initialize the matrix to a unit matrix
    T M[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

  public:
    mat44() = default;
    mat44(std::initializer_list<std::initializer_list<T>> xs) {
        // Initialize with braces
        //
        // Caution : Overflow
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
        // Print the contents (debug)
        for (uint8_t i = 0; i < 4; i++) {
            for (uint8_t j = 0; j < 4; j++) {
                std::cout << M[i][j] << " : ";
            }
            std::cout << "\n";
        }
    }
    mat44 operator*(const mat44 &rhs) const {
        // Multiply two matrices
        mat44 res;
        for (uint8_t i = 0; i < 4; i++) {
            for (uint8_t j = 0; j < 4; j++) {
                res[i][j] = M[i][0] * rhs[0][j] + M[i][1] * rhs[1][j] +
                            M[i][2] * rhs[2][j] + M[i][3] * rhs[3][j];
            }
        }
        return res;
    }
    void mult_point_matrix(const vec3<T> &src, const vec3<T> &dst) const {
        // Multiply a point to a transformation matrix
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
    void mult_vec_matrix(const vec3<T> &src, const vec3<T> &dst) const {
        // Multiply a vector to a transformation matrix
        dst.x = src.x * M[0][0] + src.y * M[1][0] + src.z * M[2][0];
        dst.y = src.x * M[0][1] + src.y * M[1][1] + src.z * M[2][1];
        dst.z = src.x * M[0][2] + src.y * M[1][2] + src.z * M[2][2];
    }
    void transpose() const {
        // Return the transpose of this matrix
        return mat44{{M[0][0], M[1][0], M[2][0], M[3][0]},
                     {M[0][1], M[1][1], M[2][1], M[3][1]},
                     {M[0][2], M[1][2], M[2][2], M[3][2]},
                     {M[0][3], M[1][3], M[2][3], M[3][3]}};
    }
    void inverse() const {
        // Basic algorithm is to find the adjoint ie. the transpose of the
        // cofactor matrix and compute the determinant of the matrix
        // The inverse is the adjoint divided by the determinant of the matrix
    }
    void determinant() const {
        // Expand along any row/column, find the sum of all the cofactors of the
        // elements in those rows multiplies the elements of the rows
    }
};
template <typename T>
void spherical_to_cartesian(const float &theta, const float &phi) {
    return vec3<T>(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}
}
#endif

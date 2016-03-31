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
#include <array>
#include <cmath>
#include <algorithm>
#include <limits>
namespace alpha {
template <typename T> bool is_equal(T a, T b) {
    if (a > 1.0 && b > 1.0) {
        // Return true if the relative error is less than the system epsilon
        if (fabs(fabs(a) - fabs(b)) / fabs(a) <=
                std::numeric_limits<T>::epsilon() ||
            a == b) {
            return true;
        }
    } else {
        if (fabs(fabs(a) - fabs(b)) <= std::numeric_limits<T>::epsilon() ||
            a == b) {
            return true;
        }
    }
    return false;
}
template <typename T> class vec3 {
    // A 3 tuple
  public:
    T x, y, z;
    vec3() : x(0), y(0), z(0) {}
    vec3(const T &xx) : x(xx), y(xx), z(xx) {}
    vec3(const T &xx, const T &yy, const T &zz) : x(xx), y(yy), z(zz) {}
    vec3<T> operator+(const vec3<T> &v) const {
        return vec3<T>(x + v.x, y + v.y, z + v.z);
    }
    vec3<T> operator-(const vec3<T> &v) const {
        return vec3<T>(x - v.x, y - v.y, z - v.z);
    }
    vec3<T> operator*(T v) const { return vec3<T>(x * v, y * v, z * v); }
    T operator[](const size_t id) const {
        switch (id) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        }
        return int();
    }
    vec3<T> cross(const vec3<T> &v) {
        return vec3<T>(y * v.z - z * v.y, x * v.z - z * v.x, x * v.y - y * v.x);
    }
    T mod() { return sqrt(x * x + y * y + z * z); }
    T dot(const vec3<T> &v) { return v.x * x + v.y * y + v.z * z; }
    void normalize() {
        T mag = mod();
        if (mag != 0) {
            T inv_mag = 1.0 / mag;
            x *= inv_mag, y *= inv_mag, z *= inv_mag;
        }
    }
};
template <typename T> class mat44 {
    // Represents a 4x4 matrix
    // Default initialize the matrix to a unit matrix
    T M[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

  public:
    static const size_t rows = 4, cols = 4;
    mat44() = default;
    mat44(std::initializer_list<std::initializer_list<T>> xs) {
        // Initialize with braces
        //
        // Caution : Overflow
        size_t r = 0, c = 0;
        for (auto row : xs) {
            for (auto elem : row) {
                M[r][c++] = elem;
            }
            r++, c = 0;
        }
    }
    const T *operator[](size_t i) const { return M[i]; };
    T *operator[](size_t i) { return M[i]; };
    void dump() {
        // Print the contents (debug)
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
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
    inline bool operator==(const mat44 &rhs) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (!is_equal(M[i][j], rhs[i][j])) {
                    return false;
                }
            }
        }
        return true;
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
    mat44<T> transpose() const {
        // Return the transpose of this matrix
        return mat44{{M[0][0], M[1][0], M[2][0], M[3][0]},
                     {M[0][1], M[1][1], M[2][1], M[3][1]},
                     {M[0][2], M[1][2], M[2][2], M[3][2]},
                     {M[0][3], M[1][3], M[2][3], M[3][3]}};
    }
};
template <typename T>
void spherical_to_cartesian(const float &theta, const float &phi) {
    return vec3<T>(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}
template <typename T> mat44<T> gauss_elimination(const mat44<T> &in) {
    // Perform Gaussian elimination on this matrix and return a row echelon form
    mat44<T> operate = in;
    for (size_t k = 0; k < operate.cols; k++) {
        T i_max = k;
        // Partial pivoting
        for (size_t i = k + 1; i < operate.rows; i++) {
            if (fabs(operate[i][k]) > fabs(operate[i_max][k])) {
                i_max = i;
            }
        }
        if (is_equal(operate[i_max][k], T(0.0))) {
            // This is a singular matrix
            return operate;
        }
        if (i_max != k) {
            // We need a swap
            for (size_t i = 0; i < operate.cols; i++) {
                std::swap(operate[i_max][i], operate[k][i]);
            }
        }
        for (size_t i = k + 1; i < operate.rows; i++) {
            T val = operate[i][k] / operate[k][k];
            for (size_t j = k + 1; j < operate.cols; j++) {
                operate[i][j] -= (operate[k][j] * val);
            }
            operate[i][k] = 0;
        }
    }
    return operate;
}
template <typename T> T mat44_det(const mat44<T> &in) {
    auto row_echelon = gauss_elimination(in);
    return row_echelon[0][0] * row_echelon[1][1] * row_echelon[2][2] *
           row_echelon[3][3];
}
template <typename T> mat44<T> mat44_inv(const mat44<T> &in);
// End namespace alpha
}
#endif

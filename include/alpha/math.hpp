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
#ifndef MATH_ALPHA_HPP
#define MATH_ALPHA_HPP

#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <algorithm>

#ifndef M_PI
	#define M_PI 3.14159265358979323846264338327950288 
#endif

namespace alpha {
namespace math {

/**
* Find the minimum of 3 values
 * @return The minimum of the three arguments.
*/
template <typename T>
inline T min_3(T a, T b, T c) {
    return std::min(std::min(a, b), c);
}
/**
 * Find the maximum of 3 values.
 * @return The maximum of the three arguments.
 */
template <typename T>
inline T max_3(T a, T b, T c) {
    return std::max(std::max(a, b), c);
}

/**
 * Compare two floats for equality
 * @param a The first argument.
 * @param b The second argument.
 * @return Truth value of the equality comparision.
 */
template <typename T>
inline bool is_equal(T a, T b) {
    if (a > 1.0 && b > 1.0) {
        // Return true if the relative error is less than the system epsilon
        if ((fabs(fabs(a) - fabs(b))) <=
            fabs(a) * 2 * std::numeric_limits<T>::epsilon() ||
            a == b) {
            return true;
        }
    } else {
        if (fabs(fabs(a) - fabs(b)) <=
            2 * std::numeric_limits<T>::epsilon() ||
            a == b || (a == 0 && b == 0)) {
            return true;
        }
    }
    return false;
}

/**
 * A 3 component vector.
 * @tparam T The type of the co-ordinates.
 */
template<typename T>
class Vec3 {
public:
    Vec3() = default;

    Vec3(T xx) : x(xx), y(xx), z(xx) {}

    Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

    Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}

    friend void swap(Vec3& first, Vec3& second) {
        using std::swap;

        swap(first.x, second.x);
        swap(first.y, second.y);
        swap(first.z, second.z);
    }

    Vec3& operator=(Vec3 other) {
        swap(*this, other);

        return *this;
    }

    // Vector operations.
    Vec3& operator+=(const Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // Schur product, not dot product.
    Vec3& operator*=(const Vec3& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    // Scalar operations.
    Vec3& operator+=(T r) {
        x += r;
        y += r;
        z += r;
        return *this;
    }

    Vec3& operator-=(T r) {
        x -= r;
        y -= r;
        z -= r;
        return *this;
    }

    Vec3& operator*=(T r) {
        x *= r;
        y *= r;
        z *= r;
        return *this;
    }

    bool operator==(const Vec3& rhs) const {
        return x == rhs.x && y == rhs.y &&  z == rhs.z;
    }

    T dot_product(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3 cross_product(const Vec3& v) const {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    T norm() const { return x * x + y * y + z * z; }

    T length() const { return sqrt(norm()); }

    const T &operator[](uint8_t i) const { return (&x)[i]; }

    T &operator[](uint8_t i) { return (&x)[i]; }

    Vec3 &normalize() {
        T n = norm();
        if (n > 0) {
            T factor = 1 / sqrt(n);
            x *= factor, y *= factor, z *= factor;
        }

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &s, const Vec3<T> &v) {
        return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
    }

    T x, y, z;
};

// Operator overloads for Vec3.
template <typename T>
inline Vec3<T> operator+(Vec3<T> lhs, const Vec3<T>& rhs) {
    return lhs += rhs;
}

template <typename T>
inline Vec3<T> operator-(Vec3<T> lhs, const Vec3<T>& rhs) {
    return lhs -= rhs;
}

template <typename T>
inline Vec3<T> operator*(Vec3<T> lhs, const Vec3<T>& rhs) {
    return lhs *= rhs;
}

template <typename T>
inline Vec3<T> operator*(Vec3<T> lhs, T rhs) {
    return lhs *= rhs;
}

/**
 * A 2 component vector.
 * @tparam T The type of the compoenents.
 */
template<typename T>
class Vec2 {
public:
    template<typename U>
    friend void swap(Vec2&, Vec2&);

	Vec2() = default;

    Vec2(T xx) : x(xx), y(xx) {}

    Vec2(T xx, T yy) : x(xx), y(yy) {}

    Vec2(const Vec2& other) : x(other.x), y(other.y) {}

    friend void swap(Vec2 &first, Vec2 &second) {
        using std::swap;

        swap(first.x, second.x);
        swap(first.y, second.y);
    }

    Vec2& operator=(Vec2 other) {
        swap(*this, other);

        return *this;
    }

    // Vector operations.
    Vec2& operator+=(const Vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    // Schur product, not dot product.
    Vec2& operator*=(const Vec2& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    // Scalar operations.
    Vec2& operator+=(T r) {
        x += r;
        y += r;
        return *this;
    }

    Vec2& operator-=(T r) {
        x -= r;
        y -= r;
        return *this;
    }

    Vec2& operator*=(T r) {
        x *= r;
        y *= r;
        return *this;
    }

    bool operator==(const Vec2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    T dot_product(const Vec2<T> &v) const { return x * v.x + y * v.y; }

    T norm() const { return x * x + y * y; }

    T length() const { return sqrt(norm()); }

    const T &operator[](uint8_t i) const { return (&x)[i]; }

    T &operator[](uint8_t i) { return (&x)[i]; }

    Vec2 &normalize() {
        T n = norm();
        if (n > 0) {
            T factor = 1 / sqrt(n);
            x *= factor, y *= factor;
        }

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &s, const Vec2<T> &v) {
        return s << '(' << v.x << ' ' << v.y << ')';
    }

    T x, y;
};

// Operator overloads for Vec2.
template <typename T>
inline Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs) {
    return lhs += rhs;
}

template <typename T>
inline Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs) {
    return lhs -= rhs;
}

template <typename T>
inline Vec2<T> operator*(Vec2<T> lhs, const Vec2<T>& rhs) {
    return lhs *= rhs;
}

template <typename T>
inline Vec2<T> operator*(Vec2<T> lhs, T& rhs) {
    return lhs *= rhs;
}

// Some convenience typedefs.
typedef Vec3<float> Vec3f;
typedef Vec2<float> Vec2f;
typedef Vec3<int> Vec3i;
typedef Vec2<int> Vec2i;

/**
 * A 4x4 matrix.
 * @tparam T The type of the matrix elements.
 */
template<typename T>
class Matrix44 {
public:
    T x[4][4];

    Matrix44() {}

    // Initialize with braces
    Matrix44(std::initializer_list<T> xs) {
        assert(xs.size() == 16);

        auto it = xs.begin();
        for(size_t r = 0; r < 4; ++r) {
            for (size_t c = 0; c < 4; ++c) {
                x[r][c] = *it;
                ++it;
            }
        }
    }

    // Initialize with identity matrix.
    void eye() {
        memset(x, 0, sizeof(x));
        x[0][0] = x[1][1] = x[2][2] = x[3][3] = 1;
    }

    friend void swap(Matrix44 &first, Matrix44 &second) {
        using std::swap;

        swap(first.x, second.x);
    }

    Matrix44& operator=(Matrix44 other) {
        swap(*this, other);

        return *this;
    }

    const T *operator[](uint8_t i) const { return x[i]; }

    T *operator[](uint8_t i) { return x[i]; }

    // Multiply the current matrix with another matrix (rhs)
    Matrix44 operator*(const Matrix44 &v) const {
        Matrix44 tmp;
        multiply(*this, v, tmp);

        return tmp;
    }

    bool operator==(const Matrix44 &lhs) const {
        bool equal = true;

        for (uint8_t i = 0; i < 4 && equal; i++) {
            for (uint8_t j = 0; j < 4; j++) {
                if (!is_equal(lhs.x[i][j], x[i][j])) {
                    equal = false;
                    break;
                }
            }
        }
        return equal;
    }

    static void multiply(const Matrix44<T> &a, const Matrix44 &b, Matrix44 &c) {
#if 0
        for (uint8_t i = 0; i < 4; ++i) {
            for (uint8_t j = 0; j < 4; ++j) {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] +
                    a[i][2] * b[2][j] + a[i][3] * b[3][j];
            }
        }
#else
        // A restrict qualified pointer (or reference) is basically a promise
        // to the compiler that for the scope of the pointer, the target of the
        // pointer will only be accessed through that pointer (and pointers
        // copied from it.
        const T *__restrict ap = &a.x[0][0];
        const T *__restrict bp = &b.x[0][0];
        T *__restrict cp = &c.x[0][0];

        T a0, a1, a2, a3;

        a0 = ap[0];
        a1 = ap[1];
        a2 = ap[2];
        a3 = ap[3];

        cp[0] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[1] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[2] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[3] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[4];
        a1 = ap[5];
        a2 = ap[6];
        a3 = ap[7];

        cp[4] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[5] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[6] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[7] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[8];
        a1 = ap[9];
        a2 = ap[10];
        a3 = ap[11];

        cp[8] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[9] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[10] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[11] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[12];
        a1 = ap[13];
        a2 = ap[14];
        a3 = ap[15];

        cp[12] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[13] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[14] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[15] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];
#endif
    }

    // \brief return a transposed copy of the current matrix as a new matrix
    Matrix44 transposed() const {
#if 0
        Matrix44 t;
        for (uint8_t i = 0; i < 4; ++i) {
            for (uint8_t j = 0; j < 4; ++j) {
                t[i][j] = x[j][i];
            }
        }

        return t;
#else
        return Matrix44{{x[0][0], x[1][0], x[2][0], x[3][0]},
                        {x[0][1], x[1][1], x[2][1], x[3][1]},
                        {x[0][2], x[1][2], x[2][2], x[3][2]},
                        {x[0][3], x[1][3], x[2][3], x[3][3]}};
#endif
    }

    // \brief transpose itself
    Matrix44 &transpose() {
        Matrix44 tmp{x[0][0], x[1][0], x[2][0], x[3][0],
                     x[0][1], x[1][1], x[2][1], x[3][1],
                     x[0][2], x[1][2], x[2][2], x[3][2],
                     x[0][3], x[1][3], x[2][3], x[3][3]};
        *this = tmp;

        return *this;
    }

    template<typename S>
    void mult_vec_matrix(const Vec3<S> &src, Vec3<S> &dst) const {
        // TODO: Problem
        S a, b, c, w;

        a = src[0] * x[0][0] + src[1] * x[1][0] + src[2] * x[2][0] + x[3][0];
        b = src[0] * x[0][1] + src[1] * x[1][1] + src[2] * x[2][1] + x[3][1];
        c = src[0] * x[0][2] + src[1] * x[1][2] + src[2] * x[2][2] + x[3][2];
        w = src[0] * x[0][3] + src[1] * x[1][3] + src[2] * x[2][3] + x[3][3];

        dst.x = a / w;
        dst.y = b / w;
        dst.z = c / w;
    }

    template<typename S>
    void mult_dir_matrix(const Vec3<S> &src, Vec3<S> &dst) const {
        S a, b, c;

        a = src[0] * x[0][0] + src[1] * x[1][0] + src[2] * x[2][0];
        b = src[0] * x[0][1] + src[1] * x[1][1] + src[2] * x[2][1];
        c = src[0] * x[0][2] + src[1] * x[1][2] + src[2] * x[2][2];

        dst.x = a;
        dst.y = b;
        dst.z = c;
    }

    Matrix44 inverse() const {
        uint8_t i, j, k;
        Matrix44 s;
        s.eye();
        Matrix44 t(*this);

        // Forward elimination
        for (i = 0; i < 3; i++) {
            uint8_t pivot = i;

            T pivotsize = t[i][i];

            if (pivotsize < 0)
                pivotsize = -pivotsize;

            for (j = i + 1; j < 4; j++) {
                T tmp = t[j][i];

                if (tmp < 0)
                    tmp = -tmp;

                if (tmp > pivotsize) {
                    pivot = j;
                    pivotsize = tmp;
                }
            }

            if (pivotsize == 0) {
                // Cannot invert singular matrix
                return Matrix44();
            }

            if (pivot != i) {
                for (j = 0; j < 4; j++) {
                    T tmp;

                    tmp = t[i][j];
                    t[i][j] = t[pivot][j];
                    t[pivot][j] = tmp;

                    tmp = s[i][j];
                    s[i][j] = s[pivot][j];
                    s[pivot][j] = tmp;
                }
            }

            for (j = i + 1; j < 4; j++) {
                T f = t[j][i] / t[i][i];

                for (k = 0; k < 4; k++) {
                    t[j][k] -= f * t[i][k];
                    s[j][k] -= f * s[i][k];
                }
            }
        }

        // Backward substitution
        for (i = 4; i-- > 0;) {
            T f = t[i][i];

            if (f == 0) {
                // Cannot invert singular matrix
                return Matrix44();
            }

            for (j = 0; j < 4; j++) {
                t[i][j] /= f;
                s[i][j] /= f;
            }

            for (j = 0; j < i; j++) {
                f = t[j][i];

                for (k = 0; k < 4; k++) {
                    t[j][k] -= f * t[i][k];
                    s[j][k] -= f * s[i][k];
                }
            }
        }

        return s;
    }

    // \brief set current matrix to its inverse
    const Matrix44<T> &invert() {
        *this = inverse();
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &s, const Matrix44 &m) {
        std::ios_base::fmtflags oldFlags = s.flags();
        int cell = 12; // total with of the displayed number
        s.precision(5); // control the number of displayed decimals
        s.setf(std::ios_base::fixed);

        s << "(" << std::setw(cell) << m[0][0] << " " << std::setw(cell)
          << m[0][1] << " " << std::setw(cell) << m[0][2] << " "
          << std::setw(cell) << m[0][3] << "\n"
          <<

          " " << std::setw(cell) << m[1][0] << " " << std::setw(cell)
          << m[1][1] << " " << std::setw(cell) << m[1][2] << " "
          << std::setw(cell) << m[1][3] << "\n"
          <<

          " " << std::setw(cell) << m[2][0] << " " << std::setw(cell)
          << m[2][1] << " " << std::setw(cell) << m[2][2] << " "
          << std::setw(cell) << m[2][3] << "\n"
          <<

          " " << std::setw(cell) << m[3][0] << " " << std::setw(cell)
          << m[3][1] << " " << std::setw(cell) << m[3][2] << " "
          << std::setw(cell) << m[3][3] << ")\n";

        s.flags(oldFlags);
        return s;
    }
};

typedef Matrix44<float> Matrix44f;

// Compute the magnitude of (b - a) x (c - a)
inline float edge_function(const Vec3f &a, const Vec3f &b, const Vec3f &c) {
    return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]);
}

template <typename T>
std::pair<bool, math::Vec2<T>> solve_quadratic(T a, T b, T c) {
	T disc = b * b - 4 * a * c;
	Vec2<T> roots;

	if (disc < 0) return std::make_pair(false, roots);

	roots.x = (-b + sqrt(disc)) / 2 * a;
	roots.y = (-b - sqrt(disc)) / 2 * a;

	return std::make_pair(true, roots);
}

} // namespace math
} // namespace alpha

#endif

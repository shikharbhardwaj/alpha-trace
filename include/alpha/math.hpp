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

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

#include <gmtl/gmtl.h>

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

using Vec2f = gmtl::Vec2f;
using Vec3f = gmtl::Vec3f;
using Vec4f = gmtl::Vec4f;
using Matrix44f = gmtl::Matrix44f;

inline float edge_function(const Vec3f &a, const Vec3f &b, const Vec3f &c) {
    return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]);
}

} // namespace math
} // namespace alpha

#endif

//===---- utils ---------- General utilities --------------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// General shared utility functions
///
//===----------------------------------------------------------------------===//
#ifndef ALPHA_UTILS
#define ALPHA_UTILS

#include <fstream>
#include <vector>

#include <alpha/math.hpp>

namespace alpha {
    template <typename Exception>
    void exception_handler(const Exception& e) {
        std::cout << e.what() << std::endl;
    }
}
#endif

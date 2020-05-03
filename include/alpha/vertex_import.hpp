//===---- vertex_import ------ Vertex data import ---------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Import vertex data from disk to memory
///
//===----------------------------------------------------------------------===//
#ifndef ALPHA_VERTEX
#define ALPHA_VERTEX

#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "logging.hpp"
#include "math.hpp"

namespace alpha {
typedef struct mesh_data {
    uint32_t num_triangles;
    std::vector<alpha::math::Vec3f> vertices;

    mesh_data() = delete;

    mesh_data(const std::string &src_name, bool y_up = false,
              uint32_t n_tri = 0) {
        vertices.reserve(n_tri);
        std::ifstream handle(src_name);

        if (!handle.is_open()) {
            throw std::invalid_argument("Could not find mesh data file " + src_name);
        }

        std::istream_iterator<float> it(handle);
        std::istream_iterator<float> end;

        auto get_next = [&]() {
            return *(it++);
        };

        while (it != end) {
            float x = get_next(), y = get_next(), z = get_next();

            if(y_up) std::swap(y, z);

            vertices.emplace_back(x, y, z);
        }
        handle.close();

        spdlog::debug("First vertex: {}", vertices.front());
        spdlog::debug("Last vertex: {}", vertices.back());

        if(vertices.size() % 3) {
            spdlog::warn("Triangle vertex count {} is not a multiple of 3",
                    vertices.size());
        }

        num_triangles = (uint32_t) vertices.size() / 3;

        spdlog::info("Read {} triangles from file {}", num_triangles, src_name);
    }
} mesh_data;
}
#endif

//===--- trace_test.cpp ---- Tests for mesh renderer ------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Tests for the raytracing algorithm
///
//===----------------------------------------------------------------------===//


#include <openssl/md5.h>
#include <catch/catch.hpp>

#include <alpha/tracer.hpp>

using namespace std;
using namespace alpha;

TEST_CASE("Testing the ray tracer", "[tracer]") {
    SECTION("Testing basic primitives") {
        // Create a camera.
        auto cam_inst = make_shared<alpha::Camera>("camera_settings.cfg");

        // Make a scene
        // A red unit sphere
        auto sphere = make_shared<objects::Sphere>(0.0, 0.0,
                0.0, 1.0);

        sphere->set_color({255, 0, 0});

        Scene scene;
        scene.push_back(sphere);

        // Trace the scene
        alpha::Tracer tracer(cam_inst);
        tracer.trace(scene);

        // Check if some pixel was red.
        auto h = cam_inst->img_height, w = cam_inst->img_width;

        bool found = false;
        for (uint32_t i = 0; i < w && !found; ++i) {
            for (uint32_t j = 0; j < h && !found; ++j) {
                if(tracer.get(i, j).r > 0) {
                    found = true;
                }
            }
        }

        REQUIRE(found);
    }
}


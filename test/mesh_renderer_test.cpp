//=== mesh_renderer_test.cpp --- Tests for mesh renderer --------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Tests for the vertex mesh renderer
///
//===----------------------------------------------------------------------===//

#include <catch/catch.hpp>

#include <alpha/math.hpp>
#include <alpha/mesh_renderer.hpp>

using namespace alpha;
using namespace alpha::math;

TEST_CASE("Testing vertex mesh renderer", "[mesh_renderer]") {
    SECTION("Test rendering an axis") {
        REQUIRE_NOTHROW(
                MeshRenderer("axis.raw", "camera_settings.cfg", "test.svg",
                             false, false).render());
    }
    SECTION("Test rendering a cube") {
        REQUIRE_NOTHROW(
                MeshRenderer("cube.raw", "camera_settings.cfg", "test.svg",
                             false, false).render());
    }
    SECTION("Test rendering a detailed geometry") {
        REQUIRE_NOTHROW(
                MeshRenderer("cow_vert.raw", "camera_settings.cfg", "test.svg",
                             false, false).render());
    }
}

//===-- buffer_test.cpp -------- Tests for buffers ---------0----*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
///  Consists of tests for the imagebuffer
///
//===----------------------------------------------------------------------===//

#include <sstream>

#include <catch/catch.hpp>

#include <alpha/buffers.hpp>

using namespace std;
using namespace alpha::buffers;

TEST_CASE("Testing Imagebuffer", "[Imgbuffer]") {
    SECTION("Set and test pixels") {
        Imagebuffer testbuffer(1024, 512);
        const int maxcolor = 255;
        for(int x = 0; x < 1024; ++x) {
            for(int y = 0; y < 512; ++y) {
                uint8_t r = (x + y) % maxcolor;
                uint8_t g = (2 * x + y) % maxcolor;
                uint8_t b = (x + 2 * y) % maxcolor;
                testbuffer.set(x, y, r, g, b);
            }
        }

        for(int x = 0; x < 1024; ++x) {
            for(int y = 0; y < 512; ++y) {
                uint8_t r = (x + y) % maxcolor;
                uint8_t g = (2 * x + y) % maxcolor;
                uint8_t b = (x + 2 * y) % maxcolor;

                REQUIRE(testbuffer.get(x, y)[0] == r);
                REQUIRE(testbuffer.get(x, y)[1] == g);
                REQUIRE(testbuffer.get(x, y)[2] == b);
            }
        }
    }

    SECTION("Test imagebuffer serialization") {
        Imagebuffer testbuffer(1920, 1080);

        const int maxcolor = 255;
        for(int x = 0; x < 1920; ++x) {
            for(int y = 0; y < 1080; ++y) {
                uint8_t r = (x + y) % maxcolor;
                uint8_t g = (3 * x + y) % maxcolor;
                uint8_t b = (x + 2 * y) % maxcolor;
                testbuffer.set(x, y, r, g, b);
            }
        }

        stringstream out;
        testbuffer.dump_to_stream(out);

        // Read the stream.
        uint32_t h, w, color;
        string magic;

        out >> magic >> w >> h >> color;

        REQUIRE(magic == "P6");
        REQUIRE(w == 1920);
        REQUIRE(h == 1080);
        REQUIRE(color == 255);
        
        out.ignore();

        for(int y = 0; y < 1080; ++y) {
            for(int x = 0; x < 1920; ++x) {
                uint8_t r = (x + y) % maxcolor;
                uint8_t g = (3 * x + y) % maxcolor;
                uint8_t b = (x + 2 * y) % maxcolor;
                uint8_t byte;
                char c;
                out.read(&c, 1);
                byte = static_cast<uint8_t>(c);
                REQUIRE(byte == r);
                out.read(&c, 1);
                byte = static_cast<uint8_t>(c);
                REQUIRE(byte == g);
                out.read(&c, 1);
                byte = static_cast<uint8_t>(c);
                REQUIRE(byte == b);
            }
        }
    }
}

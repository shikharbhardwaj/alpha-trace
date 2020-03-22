//=== spdlog_test.cpp ---------- Tests for logging --------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Tests for the logging dependency
///
//===----------------------------------------------------------------------===//

#include <catch/catch.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

TEST_CASE("Testing the logging library", "[logging]") {
    CHECK_NOTHROW(spdlog::info("Hello, {}!", "World"));
}

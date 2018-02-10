//===-- math_test.cpp ---------- Tests for math -----------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
///  Consists of tests for vectors, matrices & related operations
///
//===----------------------------------------------------------------------===//

#include <iostream>
#include <sstream>

#include <catch/catch.hpp>

#include <alpha/math.hpp>

TEST_CASE("Testing Vec3", "[Vec3]") {
    alpha::math::Vec3f test_vec(1.0, 0, 1.0);
    alpha::math::Vec3f another_test_vec(0.0, 1.0, 1.0);

    SECTION("The constructor should work as expected.") {
        REQUIRE(test_vec.x == 1.0);
        REQUIRE(test_vec.y == 0.0);
        REQUIRE(test_vec.z == 1.0);
    }

    SECTION("Test operator +=") {
        test_vec += another_test_vec;

        REQUIRE(test_vec.x == 1.0);
        REQUIRE(test_vec.y == 1.0);
        REQUIRE(test_vec.z == 2.0);
    }

    SECTION("Test operator -=") {
        test_vec -= another_test_vec;

        REQUIRE(test_vec.x ==  1.0);
        REQUIRE(test_vec.y == -1.0);
        REQUIRE(test_vec.z ==  0.0);
    }

    SECTION("Test operator *= ") {
        test_vec *= another_test_vec;

        REQUIRE(test_vec.x == 0.0);
        REQUIRE(test_vec.y == 0.0);
        REQUIRE(test_vec.z == 1.0);
    }

    SECTION("Test scalar operator +=") {
        test_vec += 1.0;

        REQUIRE(test_vec.x == 2.0);
        REQUIRE(test_vec.y == 1.0);
        REQUIRE(test_vec.z == 2.0);
    }

    SECTION("Test scalar operator -=") {
        test_vec -= 1.0;

        REQUIRE(test_vec.x ==  0.0);
        REQUIRE(test_vec.y == -1.0);
        REQUIRE(test_vec.z ==  0.0);
    }

    SECTION("Test scalar operator *=") {
        test_vec *= 2;

        REQUIRE(test_vec.x == 2.0);
        REQUIRE(test_vec.y == 0.0);
        REQUIRE(test_vec.z == 2.0);
    }

    SECTION("Test vector norm calculation") {
        test_vec.normalize();
        REQUIRE(alpha::math::is_equal(test_vec.length(), 1.f));
    }

    SECTION("Test indexing") {
        REQUIRE(test_vec[0] == 1.f);
        REQUIRE(test_vec[1] == 0.f);
        REQUIRE(test_vec[2] == 1.f);
    }

    SECTION("Test dot_product product") {
        REQUIRE(test_vec.dot_product(another_test_vec) == 1.f);
    }


    SECTION("Test cross_product product") {
        alpha::math::Vec3f cross_product_result = test_vec.cross_product(another_test_vec);

        REQUIRE(cross_product_result.x == -1.f);
        REQUIRE(cross_product_result.y == -1.f);
        REQUIRE(cross_product_result.z ==  1.f);
    }

    SECTION("Test stream output operator") {
        std::stringstream test_stream;
        test_stream << std::fixed << std::setprecision(1) << test_vec;

        REQUIRE(test_stream.str() == "(1.0 0.0 1.0)");
    }

    SECTION("Test the arithmetic operator+") {
        auto some_vec = test_vec + another_test_vec;

        REQUIRE(some_vec.x == 1.f);
        REQUIRE(some_vec.y == 1.f);
        REQUIRE(some_vec.z == 2.f);
    }
}

TEST_CASE("Testing Vec2", "[Vec2]") {
    alpha::math::Vec2f test_vec(1.0, 0);
    alpha::math::Vec2f another_test_vec(0.0, 1.0);

    SECTION("The constructor should work as expected.") {
        REQUIRE(test_vec.x == 1.0);
        REQUIRE(test_vec.y == 0.0);
    }

    SECTION("Test operator +=") {
        test_vec += another_test_vec;

        REQUIRE(test_vec.x == 1.0);
        REQUIRE(test_vec.y == 1.0);
    }

    SECTION("Test operator -=") {
        test_vec -= another_test_vec;

        REQUIRE(test_vec.x ==  1.0);
        REQUIRE(test_vec.y == -1.0);
    }

    SECTION("Test operator *= ") {
        test_vec *= another_test_vec;

        REQUIRE(test_vec.x == 0.0);
        REQUIRE(test_vec.y == 0.0);
    }

    SECTION("Test scalar operator +=") {
        test_vec += 1.0;

        REQUIRE(test_vec.x == 2.0);
        REQUIRE(test_vec.y == 1.0);
    }

    SECTION("Test scalar operator -=") {
        test_vec -= 1.0;

        REQUIRE(test_vec.x ==  0.0);
        REQUIRE(test_vec.y == -1.0);
    }

    SECTION("Test scalar operator *=") {
        test_vec *= 2;

        REQUIRE(test_vec.x == 2.0);
        REQUIRE(test_vec.y == 0.0);
    }

    SECTION("Test vector norm calculation") {
        test_vec.normalize();
        REQUIRE(alpha::math::is_equal(test_vec.length(), 1.f));
    }

    SECTION("Test indexing") {
        REQUIRE(test_vec[0] == 1.f);
        REQUIRE(test_vec[1] == 0.f);
    }

    SECTION("Test dot_product product") {
        REQUIRE(test_vec.dot_product(another_test_vec) == 0.f);
    }

    SECTION("Test stream output operator") {
        std::stringstream test_stream;
        test_stream << std::fixed << std::setprecision(1) << test_vec;

        REQUIRE(test_stream.str() == "(1.0 0.0)");
    }

    SECTION("Test the arithmetic operator+") {
        auto some_vec = test_vec + another_test_vec;

        REQUIRE(some_vec.x == 1.f);
        REQUIRE(some_vec.y == 1.f);
    }
}

TEST_CASE("Testing Mat44", "[Mat44]") {
}

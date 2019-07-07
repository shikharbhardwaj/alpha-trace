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

using namespace alpha;
using namespace alpha::math;

TEST_CASE("Testing Vec3", "[Vec3]") {
    Vec3f test_vec(1.0, 0, 1.0);
    Vec3f another_test_vec(0.0, 1.0, 1.0);

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
        REQUIRE(is_equal(test_vec.length(), 1.f));
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
        Vec3f cross_product_result = test_vec.cross_product(another_test_vec);

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
    Vec2f test_vec(1.0, 0);
    Vec2f another_test_vec(0.0, 1.0);

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
        REQUIRE(is_equal(test_vec.length(), 1.f));
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
    const Matrix44f magic({2, 7, 6, 0, 9, 5, 1, 0, 4, 3, 8, 0, 0,
                                  0, 0, 0});
    const Matrix44f idx({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
                                 13, 14, 15});
    const Matrix44f I({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
                                 0, 0, 1});

    SECTION("Test sequence init") {
        Matrix44f test({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
                0, 0, 1});

        REQUIRE(test == I);
    }

    SECTION("Test eye()") {
        Matrix44f test;
        test.eye();

        REQUIRE(test == I);
    }

    SECTION("Test operator==") {
        Matrix44f test;

        REQUIRE(test == test);
    }

    SECTION("Test matrix multiplication") {
        Matrix44f res;
        Matrix44f::multiply(magic, I, res);

        REQUIRE(magic == res);
    }

    SECTION("Test matrix transpose") {
        auto test = idx;
        test.transpose();

        for(uint8_t i = 0; i < 4; ++i) {
            for(uint8_t j = 0; j < 4; ++j) {
                REQUIRE(test[i][j] == j * 4.f + i);
            }
        }
    }

    SECTION("Test matrix-point affine transformation") {
        // TODO: Better understand these transformations to
        // create a more meaningful test.
        Vec3f vec(1, 2, 3);
        Vec3f ans;

        I.mult_vec_matrix(vec, ans);

        REQUIRE(ans == vec);
    }

    SECTION("Test matrix-direction transformation") {
        Vec3f vec(1, 2, 3);
        Vec3f ans;

        I.mult_vec_matrix(vec, ans);

        REQUIRE(ans == vec);
    }

    SECTION("Test matrix-inverse") {
        REQUIRE(I.inverse() == I);
    }
}

TEST_CASE("Testing utility functions", "[Utility]") {
	Vec3f a(0, 0, 0);
	Vec3f b(0, 1, 0);
	Vec3f c(1, 1, 0);

	SECTION("Test edge function") {
		REQUIRE(edge_function(a, b, c) == 1);
	}

	SECTION("Test quadratic solver") {
		float a0 = 1.f, b0 = -2, c0 = 1;
		Vec2f s0 = { 1.f, 1.f };
		auto r0 = solve_quadratic(a0, b0, c0);
		REQUIRE(r0.first == true);
		REQUIRE(r0.second == s0);

		float a1 = 1.f, b1 = -5, c1 = 6;
		Vec2f s1 = { 3.f, 2.f };
		auto r1 = solve_quadratic(a1, b1, c1);
		REQUIRE(r1.first == true);
		REQUIRE(r1.second == s1);

		float a2 = 1.f, b2 = -14, c2 = 48;
		Vec2f s2 = { 8.f, 6.f };
		auto r2 = solve_quadratic(a2, b2, c2);
		REQUIRE(r2.first == true);
		REQUIRE(r2.second == s2);

		float a3 = 1.f, b3 = -8, c3 = 25;
		auto r3 = solve_quadratic(a3, b3, c3);
		REQUIRE(r3.first == false);
	}
}

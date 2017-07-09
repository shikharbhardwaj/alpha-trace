#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <alpha/colours.hpp>
#include <alpha/math.hpp>

TEST_CASE("Testing Vec3", "[Vec3]") {
    alpha::math::Vec3f test_vec(1.0, 0, 1.0);

    REQUIRE(test_vec.x == 1.0);
    REQUIRE(test_vec.y == 0.0);
    REQUIRE(test_vec.z == 1.0);

    // Test operators.
    alpha::math::Vec3f another_test_vec(0.0, 1.0, 1.0);

    test_vec += another_test_vec;

    REQUIRE(test_vec.x == 1.0);
    REQUIRE(test_vec.y == 1.0);
    REQUIRE(test_vec.z == 2.0);

    test_vec -= another_test_vec;

    REQUIRE(test_vec.x == 1.0);
    REQUIRE(test_vec.y == 0.0);
    REQUIRE(test_vec.z == 1.0);

    test_vec *= another_test_vec;

    REQUIRE(test_vec.x == 0.0);
    REQUIRE(test_vec.y == 0.0);
    REQUIRE(test_vec.z == 1.0);

    // Reset to original state.
    test_vec.x = 1.0;

    // Test scalar operators.
    test_vec += 1.0;

    REQUIRE(test_vec.x == 2.0);
    REQUIRE(test_vec.y == 1.0);
    REQUIRE(test_vec.z == 2.0);

    test_vec -= 1.0;

    REQUIRE(test_vec.x == 1.0);
    REQUIRE(test_vec.y == 0.0);
    REQUIRE(test_vec.z == 1.0);

    test_vec *= 2;

    REQUIRE(test_vec.x == 2.0);
    REQUIRE(test_vec.y == 0.0);
    REQUIRE(test_vec.z == 2.0);

    test_vec.normalize();

    REQUIRE(alpha::math::is_equal(test_vec.length(), 1.f));

    test_vec.x = 1.0;
    test_vec.y = 2.0;
    test_vec.z = 3.0;

    another_test_vec.x = 4.0;
    another_test_vec.y = 5.0;
    another_test_vec.z = 6.0;

    REQUIRE(test_vec.dot(another_test_vec) == 32.f);

    alpha::math::Vec3f cross_result = test_vec.cross(another_test_vec);

    REQUIRE(cross_result.x == -3.f);
    REQUIRE(cross_result.y == 6.f);
    REQUIRE(cross_result.z == -3.f);
}

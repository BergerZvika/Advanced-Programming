#include <catch2/catch_test_macros.hpp>
#include "math.h"

TEST_CASE("gcd - standard cases") {
    REQUIRE(Math::gcd(12, 8)  == 4);
    REQUIRE(Math::gcd(17, 5)  == 1);
    REQUIRE(Math::gcd(0, 7)   == 7);
    REQUIRE(Math::gcd(100, 75) == 25);
}

TEST_CASE("gcd - commutativity") {
    REQUIRE(Math::gcd(48, 18) == Math::gcd(18, 48));
    REQUIRE(Math::gcd(56, 98) == Math::gcd(98, 56));
}

TEST_CASE("lcm") {
    REQUIRE(Math::lcm(4, 6)  == 12);
    REQUIRE(Math::lcm(3, 5)  == 15);
    REQUIRE(Math::lcm(7, 7)  == 7);
}

TEST_CASE("lcm - lcm(a,b) * gcd(a,b) == a*b") {
    int a = 12, b = 18;
    REQUIRE(Math::lcm(a, b) * Math::gcd(a, b) == a * b);
}

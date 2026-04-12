#include <catch2/catch_test_macros.hpp>
#include "math.h"

TEST_CASE("factorial - normal cases") {
    REQUIRE(Math::factorial(0)  == 1);
    REQUIRE(Math::factorial(1)  == 1);
    REQUIRE(Math::factorial(5)  == 120);
    REQUIRE(Math::factorial(10) == 3628800);
}

TEST_CASE("factorial - negative input returns sentinel") {
    REQUIRE(Math::factorial(-1) == -1);
    REQUIRE(Math::factorial(-5) == -1);
}

TEST_CASE("is_prime - small primes") {
    REQUIRE_FALSE(Math::is_prime(0));
    REQUIRE_FALSE(Math::is_prime(1));
    REQUIRE(Math::is_prime(2));
    REQUIRE(Math::is_prime(3));
    REQUIRE(Math::is_prime(5));
    REQUIRE(Math::is_prime(7));
    REQUIRE(Math::is_prime(11));
    REQUIRE(Math::is_prime(97));
}

TEST_CASE("is_prime - composites") {
    REQUIRE_FALSE(Math::is_prime(4));
    REQUIRE_FALSE(Math::is_prime(9));
    REQUIRE_FALSE(Math::is_prime(100));
}

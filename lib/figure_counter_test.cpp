#include <doctest/doctest.h>

TEST_CASE("failing test in figure")
{
    REQUIRE(10 == 1);
}

TEST_CASE("passing test in figure")
{
    REQUIRE(13 != 33);
}

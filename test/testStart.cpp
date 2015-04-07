#include <catch.hpp>
#include "../source/Start.hpp"

TEST_CASE("We can create a Start","[start]")
{
    REQUIRE_NOTHROW(CSP::Start{});
}

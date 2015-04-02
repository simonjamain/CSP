#include <catch.hpp>
#include "../source/Timenode.hpp"

TEST_CASE("We can create a timenode","[timenode]")
{
    REQUIRE_NOTHROW(CSP::Timenode{});
}

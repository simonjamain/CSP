#include <catch.hpp>
#include "../source/FiniteDuration.hpp"

#define TEST_FINITE_VALUE1 145
#define TEST_FINITE_VALUE2 13448

TEST_CASE("A finite duration can be created","[duration]")
{
    SECTION("We can create it")
    {
        CSP::FiniteDuration fd(TEST_FINITE_VALUE1);
    }
}

TEST_CASE("We can access the length of a finite duration","[duration]")
{
    CSP::FiniteDuration fd(TEST_FINITE_VALUE1);

    SECTION("We can retrieve the length of an finite duration")
    {
        REQUIRE(fd.getLength() == TEST_FINITE_VALUE1);
    }
}

TEST_CASE("A finite duration can be modified","[duration]")
{
    REQUIRE(TEST_FINITE_VALUE1 != TEST_FINITE_VALUE2);
    CSP::FiniteDuration fd(TEST_FINITE_VALUE1);

    SECTION("We can modify it from finite to finite")
    {
        REQUIRE(fd.getLength() != TEST_FINITE_VALUE2);

        fd.setValue(TEST_FINITE_VALUE2);

        REQUIRE(fd.getLength() == TEST_FINITE_VALUE2);
    }

}

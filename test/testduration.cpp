#include <catch.hpp>
#include "../source/Duration.hpp"

#define TEST_FINITE_VALUE1 145
#define TEST_FINITE_VALUE2 12

TEST_CASE("A duration can be created","[duration]")
{
    SECTION("We can create it finite")
    {
        CSP::Duration d(TEST_FINITE_VALUE1);

        REQUIRE(d.isFinite());
    }
    SECTION("We can create it infinite")
    {
        CSP::Duration d((CSP::PositiveInfinity()));

        REQUIRE_FALSE(d.isFinite());
    }
}

TEST_CASE("We can access the length of a duration","[duration]")
{
    CSP::Duration d_infinite((CSP::PositiveInfinity()));
    CSP::Duration d_finite(TEST_FINITE_VALUE1);

    SECTION("We can't retrieve the length of an infinite duration")
    {
        REQUIRE_THROWS_AS( d_infinite.getLength(), CSP::IsInfiniteException);
    }

    SECTION("We can retrieve the length of an finite duration")
    {
        REQUIRE(d_finite.getLength() == TEST_FINITE_VALUE1);
    }
}

TEST_CASE("A duration can be modified","[duration]")
{
    REQUIRE(TEST_FINITE_VALUE1 != TEST_FINITE_VALUE2);

    CSP::Duration d_infinite((CSP::PositiveInfinity()));
    CSP::Duration d_finite(TEST_FINITE_VALUE1);

    SECTION("We can modify it from finite to finite")
    {
        REQUIRE(d_finite.isFinite());
        REQUIRE(d_finite.getLength() != TEST_FINITE_VALUE2);

        d_finite.setValue(TEST_FINITE_VALUE2);

        REQUIRE(d_finite.getLength() == TEST_FINITE_VALUE2);
    }

    SECTION("We can modify it from finite to infinite")
    {
        REQUIRE(d_finite.isFinite());

        d_finite.setValue((CSP::PositiveInfinity()));

        REQUIRE_FALSE(d_finite.isFinite());
    }

    SECTION("We can modifiy it from infinite to finite")
    {
        REQUIRE_FALSE(d_infinite.isFinite());

        d_infinite.setValue(TEST_FINITE_VALUE1);

        REQUIRE(d_infinite.isFinite());
    }
}

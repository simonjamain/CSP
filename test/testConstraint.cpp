#include <catch.hpp>
#include "../source/Constraint.hpp"
#include "../source/Timenode.hpp"

TEST_CASE("We can create a constraint","[constraint]")
{
    CSP::Timenode* timenode1 = new CSP::Timenode();
    CSP::Timenode* timenode2 = new CSP::Timenode();

    CSP::Constraint constraint(
                CSP::FiniteDuration{10},
                CSP::FiniteDuration{10},
                CSP::Duration{5},
                timenode1,
                timenode2);

    REQUIRE(constraint.getNextTimenode() == timenode2);
}
TEST_CASE("We can check is properties of a constraint are valid","[constraint]")
{
    CSP::Timenode* timenode1 = new CSP::Timenode();
    CSP::Timenode* timenode2 = new CSP::Timenode();

    SECTION("All lengths to 0 is valid")
    {
        CSP::Constraint constraint(
                    CSP::FiniteDuration{0},
                    CSP::FiniteDuration{0},
                    CSP::Duration{0},
                    timenode1,
                    timenode2);

        REQUIRE_NOTHROW(constraint.validateInternalProperties());
    }

    SECTION("An infinite flexAfter is valid")
    {
        CSP::Constraint constraint = CSP::Constraint(
                    CSP::FiniteDuration{0},
                    CSP::FiniteDuration{0},
                    CSP::Duration{CSP::PositiveInfinity{}},
                    timenode1,
                    timenode2);

        REQUIRE_NOTHROW(constraint.validateInternalProperties());
    }
    SECTION("A flexBefore > nominal is invalid")
    {
        CSP::Constraint constraint(
                    CSP::FiniteDuration{0},
                    CSP::FiniteDuration{6},
                    CSP::Duration{0},
                    timenode1,
                    timenode2);

        REQUIRE_THROWS_AS(constraint.validateInternalProperties(), CSP::InternalPropertiesNotValidException);
    }
}

TEST_CASE("We can retrieve the computed min and max if properties are valid","[constraint]")
{
    CSP::Timenode* timenode1 = new CSP::Timenode();
    CSP::Timenode* timenode2 = new CSP::Timenode();

    SECTION("And invalid constraint doesnt allow min and max retrieval")
    {
        CSP::Constraint constraint(
                    CSP::FiniteDuration{0},
                    CSP::FiniteDuration{6},
                    CSP::Duration{0},
                    timenode1,
                    timenode2);
        REQUIRE_THROWS_AS(constraint.getMin(), CSP::InternalPropertiesNotValidException);
        REQUIRE_THROWS_AS(constraint.getMax(), CSP::InternalPropertiesNotValidException);
    }

    CSP::Constraint constraint(
                CSP::FiniteDuration{10},
                CSP::FiniteDuration{5},
                CSP::Duration{0},
                timenode1,
                timenode2);

    REQUIRE(constraint.getMin().getLength() == 5);

    REQUIRE(constraint.getMax().isFinite());
    REQUIRE(constraint.getMax().getLength() == 10);

    CSP::Constraint constraintInf(
                CSP::FiniteDuration{10},
                CSP::FiniteDuration{5},
                CSP::Duration{CSP::PositiveInfinity{}},
                timenode1,
                timenode2);

    REQUIRE_FALSE(constraintInf.getMax().isFinite());
}

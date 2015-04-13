/**
  Pour la description des tests ci-dessous, se referrer
  au document scenariosTests.pdf
  */

#include <catch.hpp>
#include "../source/Scenario.hpp"
#include "../source/csp.hpp"
#include "../source/Duration.hpp"
#include "../source/Start.hpp"
#include "../source/Timenode.hpp"

#define CSP_TEST_LARGE_SCENARIO_SIZE 1000
#define CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH 10

TEST_CASE("Scenarios can be valid", "[csp]")
{
    CSP::Scenario scenario;

    SECTION("Scenario #a1 is valid")
    {
        scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{0},
                    CSP::Duration{0});

        REQUIRE(CSP::isValid(scenario));
    }

    SECTION("Scenario #a2 is valid")
    {
        scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{10},
                    CSP::Duration{CSP::PositiveInfinity{}});

        REQUIRE(CSP::isValid(scenario));
    }

    SECTION("Scenario #c1 is valid")
    {
        CSP::FiniteDuration nominal1(10);
        CSP::FiniteDuration flexBefore1(0);
        CSP::Duration flexAfter1(5);

        CSP::Constraint* firstConstraint = scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{0},
                    CSP::Duration{5});

        CSP::FiniteDuration nominal2(10);
        CSP::FiniteDuration flexBefore2(10);
        CSP::Duration flexAfter2(10);

        scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{10},
                    CSP::Duration{10},
                    CSP_START_NODE,
                    firstConstraint->getNextTimenode());

        REQUIRE(CSP::isValid(scenario));
    }
    SECTION("Scenario #c2 is valid")
    {
        CSP::Constraint* firstConstraint = scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{0},
                    CSP::Duration{5});

        scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{10},
                    CSP::Duration{CSP::PositiveInfinity{}});

        REQUIRE(CSP::isValid(scenario));
    }

    SECTION("Scenario #d1 is valid")
    {
        CSP::Constraint* firstConstraint = scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{5},
                    CSP::Duration{5});

        scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{5},
                    CSP::Duration{5},
                    firstConstraint->getNextTimenode());
    }

    SECTION("Scenario #d2 is valid")
    {
        CSP::Constraint* firstConstraint = scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{10},
                    CSP::Duration{5});

        scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{10},
                    CSP::Duration{CSP::PositiveInfinity{}},
                    firstConstraint->getNextTimenode());
    }
}

TEST_CASE("Scenarios can be not valid","[csp]")
{
    CSP::Scenario scenario;

    SECTION("Scenario #a1 is not valid")
    {
        scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{15},
                    CSP::Duration{0});

        REQUIRE_FALSE(CSP::isValid(scenario));
    }

    SECTION("Scenario #d1 is not valid")
    {
        CSP::Constraint* firstConstraint = scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{0},
                    CSP::Duration{5});

        CSP::Constraint* secondConstraint = scenario.addConstraint(
                    CSP::FiniteDuration{15},
                    CSP::FiniteDuration{0},
                    CSP::Duration{5},
                    firstConstraint->getNextTimenode());

        scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{10},
                    CSP::Duration{5},
                    CSP_START_NODE,
                    secondConstraint->getNextTimenode());

        REQUIRE_FALSE(CSP::isValid(scenario));
    }
}

TEST_CASE("We can work with large scenarios", "[csp]")
{
    CSP::Scenario scenario;
    CSP::Constraint* prevConstraint = scenario.addConstraint(
                CSP::FiniteDuration{CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH},
                CSP::FiniteDuration{CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH},
                CSP::Duration{CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH});
    CSP::Constraint* nextConstraint;
    SECTION("Long line of constraints")
    {
        for(int nbConstraint = 1; nbConstraint < CSP_TEST_LARGE_SCENARIO_SIZE; ++nbConstraint)
        {
            nextConstraint = scenario.addConstraint(
                        CSP::FiniteDuration{CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH},
                        CSP::FiniteDuration{CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH},
                        CSP::Duration{CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH},
                        prevConstraint->getNextTimenode());

            prevConstraint = nextConstraint;
        }

        REQUIRE(CSP::isValid(scenario));
    }
    SECTION("Long row of constraints")
    {
        for(int nbConstraint = 1; nbConstraint < CSP_TEST_LARGE_SCENARIO_SIZE; ++nbConstraint)
        {
            nextConstraint = scenario.addConstraint(
                        CSP::FiniteDuration{CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH},
                        CSP::FiniteDuration{CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH},
                        CSP::Duration{CSP_TEST_DEFAULT_CONSTRAINT_NOMINAL_LENGTH},
                        CSP_START_NODE,
                        prevConstraint->getNextTimenode());
        }

        REQUIRE(CSP::isValid(scenario));
    }

}

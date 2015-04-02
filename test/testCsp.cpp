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

#define TEST_INFINITE_VALUE (CSP::PositiveInfinity())

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
    //Invalid scenarios
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
#include <catch.hpp>
#include "../source/Scenario.hpp"
#include "../source/csp.hpp"
#include "../source/Duration.hpp"
#include "../source/Start.hpp"
#include "../source/Timenode.hpp"

#define TEST_INFINITE_VALUE (CSP::PositiveInfinity())

TEST_CASE("Scenarios can be valid", "[scenario]")
{
    CSP::Scenario scenario;

    SECTION("Scenario #a1 is valid")
    {
        CSP::FiniteDuration nominal(10);
        CSP::FiniteDuration flexBefore(0);
        CSP::Duration flexAfter(0);

        scenario.addConstraint(nominal, flexBefore, flexAfter);

        REQUIRE(CSP::isValid(scenario));
    }

    SECTION("Scenario #a2 is valid")
    {
        CSP::FiniteDuration nominal(10);
        CSP::FiniteDuration flexBefore(10);
        CSP::Duration flexAfter((CSP::PositiveInfinity()));

        scenario.addConstraint(nominal, flexBefore, flexAfter);

        REQUIRE(CSP::isValid(scenario));
    }

    SECTION("Scenario #c1 is valid")
    {
        CSP::FiniteDuration nominal1(10);
        CSP::FiniteDuration flexBefore1(0);
        CSP::Duration flexAfter1(5);

        CSP::Constraint* firstConstraint = scenario.addConstraint(nominal1, flexBefore1, flexAfter1);

        CSP::FiniteDuration nominal2(10);
        CSP::FiniteDuration flexBefore2(10);
        CSP::Duration flexAfter2(10);

        scenario.addConstraint(nominal2, flexBefore2, flexAfter2, firstConstraint->getNextTimenode());

        REQUIRE(CSP::isValid(scenario));
    }
    //Invalid scenarios

    SECTION("Scenario #a1 is not valid")
    {
        CSP::FiniteDuration nominal(10);
        CSP::FiniteDuration flexBefore(15);
        CSP::Duration flexAfter(0);

        scenario.addConstraint(nominal, flexBefore, flexAfter);

        REQUIRE_FALSE(CSP::isValid(scenario));
    }

}

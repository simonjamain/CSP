#include "gtest/gtest.h"
#include "../source/Constraint.hpp"
#include "../source/Node.hpp"
#include "../source/Timenode.hpp"
#include "../source/Duration.hpp"
#include "../source/FiniteDuration.hpp"
#include "../source/Scenario.hpp"
#include "../source/csp.hpp"

#define FDUR_0 CSP::FiniteDuration{0}
#define DUR_0 CSP::Duration{0}
#define FDUR_10 CSP::FiniteDuration{10}
#define DUR_10 CSP::Duration{10}

//TEST EXAMPLE
TEST(csp, validA1)
{
    CSP::Scenario scenario;

    scenario.addConstraint(
                FDUR_0,
                FDUR_0,
                DUR_0
                );

    ASSERT_TRUE(CSP::isValid(scenario));
}

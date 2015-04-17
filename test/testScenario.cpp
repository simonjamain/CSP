#include "gtest/gtest.h"
#include "../source/Constraint.hpp"
#include "../source/Node.hpp"
#include "../source/Timenode.hpp"
#include "../source/Duration.hpp"
#include "../source/FiniteDuration.hpp"
#include "../source/Scenario.hpp"
#include "../source/csp.hpp"

#include "testHelpers.hpp"

TEST(scenario, constraintRemoval)
{
    CSP::Scenario scenario;

    CSP::Constraint* c1 = scenario.addConstraint(
                FDUR_0,
                FDUR_0,
                DUR_0
                );

    CSP::Node* t1 = c1->getNextTimenode();

    ASSERT_EQ(scenario.getTimenodes().size(),2);
    ASSERT_EQ(scenario.getTimenodes()[0]->getNextConstraints().size(),1);

    scenario.removeConstraint(c1);

    ASSERT_EQ(scenario.getTimenodes().size(),2);
    ASSERT_TRUE(scenario.getTimenodes()[0]->getNextConstraints().empty());
}

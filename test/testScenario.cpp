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

TEST(scenario, timenodeRemoval)
{
    CSP::Scenario scenario;

    CSP::Constraint* c1 = scenario.addConstraint(
                FDUR_10,
                FDUR_5,
                DUR_5
                );

    CSP::Timenode* t1 = c1->getNextTimenode();

    CSP::Constraint* c2 = scenario.addConstraint(
                FDUR_10,
                FDUR_5,
                DUR_5,
                t1
                );

    CSP::Timenode* t2 = c2->getNextTimenode();

    CSP::Constraint* c3 = scenario.addConstraint(
                FDUR_10,
                FDUR_10,
                DUR_10,
                CSP::ConstraintAttachment::START,
                t2
                );

    CSP::Constraint* c4 = scenario.addConstraint(
                FDUR_10,
                FDUR_5,
                DUR_5,
                t2
                );

    CSP::Timenode* t3 =  c4->getNextTimenode();

    ASSERT_TRUE(CSP::isValid(scenario));

    scenario.removeTimenode(t2);

    CHECK_EQ(scenario.getTimenodes().size(),3);

    //CHECK_EQ(CSP::isValid(scenario), true);
    auto timenodes = scenario.getTimenodes();

    CHECK_EQ(std::find(timenodes.begin(),
                       timenodes.end(),
                       t2),
             timenodes.end());

    CHECK_NE(std::find(timenodes.begin(),
                       timenodes.end(),
                       t3),
             timenodes.end());

    auto afterStartConstraints = scenario.getStartNode()->getNextConstraints();

    CHECK_EQ(std::find(afterStartConstraints.begin(),
                       afterStartConstraints.end(),
                       c3),
             afterStartConstraints.end());

    CHECK_EQ(std::find(t1->getNextConstraints().begin(),
                       t1->getNextConstraints().end(),
                       c2),
             t1->getNextConstraints().end());
}

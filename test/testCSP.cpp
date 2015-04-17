#include "gtest/gtest.h"
#include "../source/Constraint.hpp"
#include "../source/Node.hpp"
#include "../source/Timenode.hpp"
#include "../source/Duration.hpp"
#include "../source/FiniteDuration.hpp"
#include "../source/Scenario.hpp"
#include "../source/csp.hpp"
#include "testHelpers.hpp"

TEST(csp, validA1)
{
    CSP::Scenario scenarioA1;

    scenarioA1.addConstraint(
                FDUR_0,
                FDUR_0,
                DUR_0
                );

    ASSERT_TRUE(CSP::isValid(scenarioA1));
}

TEST(csp, validA2)
{
    CSP::Scenario scenarioA2;

    scenarioA2.addConstraint(
                FDUR_10,
                FDUR_10,
                DUR_10
                );

    ASSERT_TRUE(CSP::isValid(scenarioA2));
}

TEST(csp, validA3)
{
    CSP::Scenario scenariA3;

    scenariA3.addConstraint(
                FDUR_10,
                FDUR_10,
                DUR_INF
                );

    ASSERT_TRUE(CSP::isValid(scenariA3));
}

TEST(csp, validC1)
{
    CSP::Scenario scenarioC1;

    CSP::Constraint* c1 = scenarioC1.addConstraint(
                FDUR_10,
                FDUR_0,
                DUR_5
                );

    scenarioC1.addConstraint(
                FDUR_10,
                FDUR_0,
                DUR_10,
                CSP::ConstraintAttachment::START,
                c1->getNextTimenode()
                );

    ASSERT_TRUE(CSP::isValid(scenarioC1));
}

TEST(csp, validC2)
{
    CSP::Scenario scenarioC2;

    CSP::Constraint* c1 = scenarioC2.addConstraint(
                FDUR_10,
                FDUR_0,
                DUR_5
                );

    scenarioC2.addConstraint(
                FDUR_10,
                FDUR_0,
                DUR_INF,
                CSP::ConstraintAttachment::START,
                c1->getNextTimenode()
                );

    ASSERT_TRUE(CSP::isValid(scenarioC2));
}

TEST(csp, validD1)
{
    CSP::Scenario scenarioD1;

    CSP::Constraint* c1 = scenarioD1.addConstraint(
                FDUR_10,
                FDUR_5,
                DUR_5
                );

    scenarioD1.addConstraint(
                FDUR_10,
                FDUR_10,
                DUR_5,
                c1->getNextTimenode()
                );

    ASSERT_TRUE(CSP::isValid(scenarioD1));
}

TEST(csp, validD2)
{
    CSP::Scenario scenarioD2;

    CSP::Constraint* c1 = scenarioD2.addConstraint(
                FDUR_10,
                FDUR_5,
                DUR_5
                );

    scenarioD2.addConstraint(
                FDUR_10,
                FDUR_10,
                DUR_INF,
                c1->getNextTimenode()
                );

    ASSERT_TRUE(CSP::isValid(scenarioD2));
}

TEST(csp, invalidA1)
{
    CSP::Scenario scenarioA1;

    CSP::Constraint* c1 = scenarioA1.addConstraint(
                FDUR_10,
                FDUR_15,
                DUR_0
                );

    ASSERT_FALSE(CSP::isValid(scenarioA1));
}

TEST(csp, invalidC1)
{
    CSP::Scenario scenarioC1;

    CSP::Constraint* c1 = scenarioC1.addConstraint(
                FDUR_5,
                FDUR_5,
                DUR_0
                );

    scenarioC1.addConstraint(
                FDUR_15,
                FDUR_5,
                DUR_10,
                CSP::ConstraintAttachment::START,
                c1->getNextTimenode()
                );


    ASSERT_FALSE(CSP::isValid(scenarioC1));
}

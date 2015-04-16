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

#define FDUR_5 CSP::FiniteDuration{5}
#define DUR_5 CSP::Duration{5}

#define FDUR_10 CSP::FiniteDuration{10}
#define DUR_10 CSP::Duration{10}

#define FDUR_15 CSP::FiniteDuration{15}
#define DUR_15 CSP::Duration{15}

#define DUR_INF CSP::Duration{CSP::PositiveInfinity{}}

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

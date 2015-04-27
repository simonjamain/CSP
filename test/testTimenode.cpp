#include "gtest/gtest.h"
#include "../source/Constraint.hpp"
#include "../source/Node.hpp"
#include "../source/Timenode.hpp"
#include "../source/Duration.hpp"
#include "../source/FiniteDuration.hpp"
#include "../source/Scenario.hpp"
#include "../source/csp.hpp"

#include "testHelpers.hpp"

TEST(timenode, dateRetrieval)
{
    CSP::Timenode T1;
    {
        std::shared_ptr<operations_research::Solver> solver = std::make_shared<operations_research::Solver>("i-score time constraint Solver");

        operations_research::IntVar* T1_1;
        ASSERT_NO_THROW(T1_1 = T1.getDate(solver));

        ASSERT_EQ(T1_1, T1.getDate(solver));

        ASSERT_EQ(T1_1, T1.getDate(solver));


        std::shared_ptr<operations_research::Solver> solver2 = std::make_shared<operations_research::Solver>("i-score time constraint Solver 2");

        ASSERT_THROW(T1.getDate(solver2), CSP::IncorrectSolverException);
    }

    std::shared_ptr<operations_research::Solver> solver3 = std::make_shared<operations_research::Solver>("i-score time constraint Solver 3");

    operations_research::IntVar* T1_2;
    ASSERT_NO_THROW(T1_2 = T1.getDate(solver3));

    {
        ASSERT_EQ(T1_2, T1.getDate(solver3));
    }

}

#include "csp.hpp"
#include <constraint_solver/constraint_solver.h>
#include "Constraint.hpp"
#include <iostream>

namespace CSP
{
bool
isValid(Scenario& scenario)
{
    bool valid = false;
    std::shared_ptr<operations_research::Solver> solver = std::make_shared<operations_research::Solver>("i-score time constraint Solver");

    const std::vector<Node*> timenodes = scenario.getTimenodes();
    std::vector<operations_research::IntVar*> dates;

    for(auto &node : timenodes)
    {
        dates.push_back( node->getDate(solver) );
        try
        {
            node->applyConstraints(solver);
        }catch(InternalPropertiesNotValidException e)
        {
            return false;
        }
    }

    operations_research::DecisionBuilder* const db = solver->MakePhase(
                dates,
                operations_research::Solver::CHOOSE_FIRST_UNBOUND,
                operations_research::Solver::ASSIGN_MIN_VALUE);

    solver->NewSearch(db);

    if(solver->NextSolution())
    {

#ifdef CSP_LOG_VALUES
        // print individual values
        std::cout << "-----------------------------------------\n";
        int i = 0;
        for(auto &timenode : timenodes)
        {
            std::cout << "T" << i << " : " << timenode->getDate(solver)->Value() << "\n";
            ++i;
        }
#endif

        valid = true;
    }

    solver->EndSearch();
    return valid;
}

void
generateTikzCode(Scenario& scenario, std::ostream& output)
{

}
}

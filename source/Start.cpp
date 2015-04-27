#include "Timenode.hpp"
#include "Start.hpp"
#include <constraint_solver/constraint_solver.h>
namespace CSP
{
operations_research::IntVar*
Start::_makeDate(operations_research::Solver* solver)
{
    return solver->MakeIntVar(0, 0);
}
}

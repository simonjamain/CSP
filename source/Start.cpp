#include "Timenode.hpp"
#include "Start.hpp"
#include <constraint_solver/constraint_solver.h>
namespace CSP
{
    operations_research::IntVar*
    Start::getDate(operations_research::Solver& solver)
    {
        if(_date == NULL)
        {
            _date = solver.MakeIntVar(0, 0);
        }
        return _date;
    }
}

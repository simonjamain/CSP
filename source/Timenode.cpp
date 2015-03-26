#include "Timenode.hpp"
#include <constraint_solver/constraint_solver.h>
namespace CSP
{
    operations_research::IntVar*
    Timenode::getDate(operations_research::Solver& solver)
    {
        if(_date == NULL)
        {
            _date = solver.MakeIntVar(0, LLONG_MAX);
        }
        return _date;
    }
}

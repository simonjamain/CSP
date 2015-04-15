#include <constraint_solver/constraint_solver.h>
#include "Node.hpp"
#include "Constraint.hpp"

namespace CSP
{

void
Node::applyConstraints(operations_research::Solver& solver)
{
    for(auto &constraint : _nextConstraints)
    {
        constraint->applyConstraints(this, solver);
    }
}

void
Node::addNextConstraint(Constraint* nextConstraint)
{
    _nextConstraints.push_back(nextConstraint);
}

std::vector<Constraint*>
Node::getNextConstraints()
{
    return _nextConstraints;
}

operations_research::IntVar*
Node::getDate(operations_research::Solver& solver)
{
    if(_date == NULL)
    {
        // on contraint le domaine de la variable
        _date = solver.MakeIntVar(0, LLONG_MAX);
    }
    return _date;
}

}

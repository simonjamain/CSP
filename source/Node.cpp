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

bool
Node::removeNextConstraint(Constraint* constraintToRemove)
{
    std::vector<Constraint*>::iterator constraintPosition = find (_nextConstraints.begin(), _nextConstraints.end(), constraintToRemove);
    if (constraintPosition != _nextConstraints.end())
    {
        _nextConstraints.erase(constraintPosition);
        return true;
    }else
    {
        return false;
    }

    delete constraintToRemove;
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

#include <constraint_solver/constraint_solver.h>
#include "Node.hpp"
#include "Constraint.hpp"

namespace CSP
{

void
Node::applyConstraints(std::shared_ptr<operations_research::Solver>solver)
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
        delete constraintToRemove;
        return true;
    }

    return false;
}

void
Node::removeAllNextConstraints()
{
    for(auto &constraint : _nextConstraints)
    {
        delete constraint;
    }
    _nextConstraints.clear();
}

void
Node::_removeConstraintsPointingTo(Timenode* timenode)
{
    std::vector<Constraint*> tmpConstraints = _nextConstraints;

    for(auto &constraint : tmpConstraints)
    {
        if(constraint->getNextTimenode() == timenode)
        {
            this->removeNextConstraint(constraint);
        }
    }
}

const std::vector<Constraint*>&
Node::getNextConstraints()
{
    return _nextConstraints;
}



operations_research::IntVar*
Node::_makeDate(operations_research::Solver* solver)
{
    return solver->MakeIntVar(0, LLONG_MAX);
}

operations_research::IntVar*
Node::getDate(std::shared_ptr<operations_research::Solver> solver)
{
    std::shared_ptr<operations_research::Solver> assignedSolver(_solver.lock());
    //if an active solver already using this node it have to be the one given
    if(assignedSolver)
    {
        //if not already assigned solver
        if(solver != assignedSolver)
        {
            throw IncorrectSolverException{};
        }else
        {
            return _date;
        }
    }
    else
    {
        _solver = solver;
        _date = _makeDate(solver.get());
        return _date;
    }

}

}

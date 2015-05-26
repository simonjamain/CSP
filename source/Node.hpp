#ifndef NODE_HPP_
#define NODE_HPP_

#include <constraint_solver/constraint_solver.h>

namespace CSP
{
class Constraint;

class Timenode;

class IncorrectSolverException
{
public:
    IncorrectSolverException(){};
};

class Node
{
private:
    std::vector<Constraint*> _nextConstraints;

    virtual
    operations_research::IntVar*
    _makeDate(operations_research::Solver* solver);

protected:
    operations_research::IntVar* _date;
    std::weak_ptr<operations_research::Solver> _solver;
public:
    Node(){}

    int64 date;

    void
    applyConstraints(std::shared_ptr<operations_research::Solver> solver);

    void
    addNextConstraint(Constraint* nextConstraint);

    bool
    removeNextConstraint(Constraint* constraintToRemove);

    void
    removeAllNextConstraints();

    void
    _removeConstraintsPointingTo(Timenode* timenode);

    const std::vector<Constraint*>&
    getNextConstraints();

    operations_research::IntVar*
    getDate(std::shared_ptr<operations_research::Solver> solver);

    virtual ~Node(){}
};

}
#endif /* NODE_HPP_ */

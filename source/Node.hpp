#ifndef NODE_HPP_
#define NODE_HPP_

#include <constraint_solver/constraint_solver.h>

namespace CSP
{
class TimeRelation;

class Timenode;

class IncorrectSolverException
{
public:
    IncorrectSolverException(){};
};

class Node
{
private:
    std::vector<TimeRelation*> _nextConstraints;

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
    addNextTimeRelation(TimeRelation* nextConstraint);

    bool
    removeNextTimeRelation(TimeRelation* constraintToRemove);

    void
    removeAllNextTimeRelations();

    void
    _removeTimeRelationsPointingTo(Timenode* timenode);

    const std::vector<TimeRelation*>&
    getNextTimeRelations();

    operations_research::IntVar*
    getDate(std::shared_ptr<operations_research::Solver> solver);

    virtual ~Node(){}
};

}
#endif /* NODE_HPP_ */

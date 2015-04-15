#ifndef NODE_HPP_
#define NODE_HPP_

#include <constraint_solver/constraint_solver.h>

namespace CSP
{
class Constraint;

class Node
{
private:
    std::vector<Constraint*> _nextConstraints;
protected:
    operations_research::IntVar* _date;
public:
    Node()
        :_date(NULL){}

    void
    applyConstraints(operations_research::Solver& solver);

    void
    addNextConstraint(Constraint* nextConstraint);

    std::vector<Constraint*>
    getNextConstraints();

    virtual operations_research::IntVar*
    getDate(operations_research::Solver& solver);

    virtual ~Node(){}
};

}
#endif /* NODE_HPP_ */

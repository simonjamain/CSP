#ifndef SCENARIO_HPP_
#define SCENARIO_HPP_

#include "../source/Constraint.hpp"
#include "../source/Timenode.hpp"
#include "../source/Start.hpp"
#include "../source/Node.hpp"
#include "../source/Duration.hpp"
#include "../source/FiniteDuration.hpp"

#define CSP_START_NODE 0

namespace CSP
{
enum ConstraintAttachment { START };

class Scenario
{
private:
    Start* _start;

    std::vector<Node*> _timenodes;

    Constraint*
    _addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Node* prevTimenode, Timenode* nextTimenode);

    void
    _removeConstraintsPointingTo(Timenode* timenode);

public:
    Scenario()
        :_start(new Start())
    {
        _timenodes.push_back(_start);
    }

    Timenode*
    addTimenode();

    Constraint*
    addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter);

    Constraint*
    addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode);

    Constraint*
    addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, ConstraintAttachment prevTimenode, Timenode* nextTimenode);

    Constraint*
    addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode, Timenode* nextTimenode);

    bool
    removeConstraint(Constraint* constraintToRemove);//TODO: throw ex if constraint not found?

    bool
    removeTimenode(Timenode* timenodeToRemove);//TODO: throw ex if timenode not found?

    std::vector<Node*>
    getTimenodes() const
    {
        return _timenodes;
    };

    Node*
    getStartNode()
    {
        return _start;
    }
};
}
#endif /* SCENARIO_HPP_ */

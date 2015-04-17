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

    void
    removeConstraint(Constraint* constraint);//TODO: throw ex if constraint not found?

    const std::vector<Node*>
    getTimenodes() const
    {
        return _timenodes;
    };
};
}
#endif /* SCENARIO_HPP_ */

#include "../source/Scenario.hpp"
#include "../source/Constraint.hpp"
#include "../source/Timenode.hpp"
#include "../source/Start.hpp"
#include "../source/Node.hpp"
#include "../source/Duration.hpp"
#include "../source/FiniteDuration.hpp"
namespace CSP
{
    Constraint*
    Scenario::_addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Node* prevTimenode, Timenode* nextTimenode)
    {
        Constraint* constraint = new Constraint(nominal, flexBefore, flexAfter, prevTimenode, nextTimenode);

        _constraints.push_back(constraint);

        return constraint;
    }

    Constraint*
    Scenario::addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode, Timenode* nextTimenode)
    {
        return _addConstraint(nominal, flexBefore, flexAfter, prevTimenode, nextTimenode);
    }

    Constraint*
    Scenario::addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* nextTimenode)
    {
        return _addConstraint(nominal, flexBefore, flexAfter, _start, nextTimenode);
    }

    Constraint*
    Scenario::addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter)
    {
        Timenode* nextTimenode = new Timenode();
        _timenodes.push_back(nextTimenode);
        return _addConstraint(nominal, flexBefore, flexAfter, _start, nextTimenode);
    }



}

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
        Constraint* constraint = new Constraint(nominal, flexBefore, flexAfter, nextTimenode);

        prevTimenode->addNextConstraint(constraint);

        return constraint;
    }

    Timenode*
    Scenario::_addTimenode()
    {
        Timenode* timenode = new Timenode();
        _timenodes.push_back(timenode);
        return timenode;
    }

    Constraint*
    Scenario::addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, ConstraintAttachment prevTimenode, Timenode* nextTimenode)
    {
        switch(prevTimenode)
        {
        default:
        case START:
            return _addConstraint(nominal, flexBefore, flexAfter, _start, nextTimenode);
            break;
        }
    }

    Constraint*
    Scenario::addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode, Timenode* nextTimenode)
    {
        return _addConstraint(nominal, flexBefore, flexAfter, prevTimenode, nextTimenode);
    }

    Constraint*
    Scenario::addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode)
    {
        Timenode* nextTimenode = _addTimenode();
        return _addConstraint(nominal, flexBefore, flexAfter, prevTimenode, nextTimenode);
    }

    Constraint*
    Scenario::addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter)
    {
        Timenode* nextTimenode = _addTimenode();
        return _addConstraint(nominal, flexBefore, flexAfter, _start, nextTimenode);
    }
}

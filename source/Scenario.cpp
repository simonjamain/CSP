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

void
Scenario::_removeConstraintsPointingTo(Timenode* timenode)
{
    for(auto &node : _timenodes)
    {
        node->_removeConstraintsPointingTo(timenode);
    }
}

Timenode*
Scenario::addTimenode()
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
    Timenode* nextTimenode = addTimenode();
    return _addConstraint(nominal, flexBefore, flexAfter, prevTimenode, nextTimenode);
}

Constraint*
Scenario::addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter)
{
    Timenode* nextTimenode = addTimenode();
    return _addConstraint(nominal, flexBefore, flexAfter, _start, nextTimenode);
}

bool
Scenario::removeConstraint(Constraint* constraintToRemove)
{
    for(auto &node : _timenodes)
    {
        if(node->removeNextConstraint(constraintToRemove))
        {
            return true;
        }
    }
    return false;
}

bool
Scenario::removeTimenode(Timenode* timenodeToRemove)
{
    // first remove all constraints related to it
    timenodeToRemove->removeAllNextConstraints();
    this->_removeConstraintsPointingTo(timenodeToRemove);

    // remove timenode from the vector and delete it
    std::vector<Node*>::iterator NodePosition = find (_timenodes.begin(), _timenodes.end(), timenodeToRemove);
    if (NodePosition != _timenodes.end())
    {
        _timenodes.erase(NodePosition);
        delete timenodeToRemove;

        return true;
    }

    return false;
}

}

#include "../source/Scenario.hpp"
#include "../source/Constraint.hpp"
#include "../source/Timenode.hpp"
#include "../source/Start.hpp"
#include "../source/Node.hpp"
#include "../source/Duration.hpp"
#include "../source/FiniteDuration.hpp"
namespace CSP
{
TimeRelation*
Scenario::_addTimeRelation(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Node* prevTimenode, Timenode* nextTimenode)
{
    TimeRelation* constraint = new TimeRelation(nominal, flexBefore, flexAfter, nextTimenode);

    prevTimenode->addNextTimeRelation(constraint);

    return constraint;
}

void
Scenario::_removeTimeRelationsPointingTo(Timenode* timenode)
{
    for(auto &node : _timenodes)
    {
        node->_removeTimeRelationsPointingTo(timenode);
    }
}

Timenode*
Scenario::addTimenode()
{
    Timenode* timenode = new Timenode();
    _timenodes.push_back(timenode);
    return timenode;
}

TimeRelation*
Scenario::addTimeRelation(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, ConstraintAttachment prevTimenode, Timenode* nextTimenode)
{
    switch(prevTimenode)
    {
    default:
    case START:
        return _addTimeRelation(nominal, flexBefore, flexAfter, _start, nextTimenode);
        break;
    }
}

TimeRelation*
Scenario::addTimeRelation(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode, Timenode* nextTimenode)
{
    return _addTimeRelation(nominal, flexBefore, flexAfter, prevTimenode, nextTimenode);
}

TimeRelation*
Scenario::addTimeRelation(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode)
{
    Timenode* nextTimenode = addTimenode();
    return _addTimeRelation(nominal, flexBefore, flexAfter, prevTimenode, nextTimenode);
}

TimeRelation*
Scenario::addTimeRelation(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter)
{
    Timenode* nextTimenode = addTimenode();
    return _addTimeRelation(nominal, flexBefore, flexAfter, _start, nextTimenode);
}

bool
Scenario::removeTimeRelation(TimeRelation* constraintToRemove)
{
    for(auto &node : _timenodes)
    {
        if(node->removeNextTimeRelation(constraintToRemove))
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
    timenodeToRemove->removeAllNextTimeRelations();
    this->_removeTimeRelationsPointingTo(timenodeToRemove);

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

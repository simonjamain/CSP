#ifndef SCENARIO_HPP_
#define SCENARIO_HPP_

#include "../source/Constraint.hpp"
#include "../source/Timenode.hpp"
#include "../source/Start.hpp"
#include "../source/Node.hpp"
#include "../source/Duration.hpp"
#include "../source/FiniteDuration.hpp"

namespace CSP
{
    class Scenario
    {
    private:
        Start* _start;
        std::vector<Constraint*> _constraints;
        std::vector<Node*> _timenodes;
        // this method allow to explicitely attach a constraint to the start node
        Constraint*
        _addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Node* prevTimenode, Timenode* nextTimenode);

    public:
        Scenario()
            :_start(new Start())
        {
            _timenodes.push_back(_start);
        }

        /**
          Add a constraint with a prevTimenode set as start and a new nextTimenode
          */
        Constraint*
        addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter);

        /**
          Add a constraint a a prevTimenode set as start and a already defined nextTimenode
          */
        Constraint*
        addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* nextTimenode);

        /**
          Add a constraint a a prevTimenode set as start and a already defined nextTimenode
          */
        Constraint*
        addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode, Timenode* nextTimenode);

        const std::vector<Constraint*>
        getConstraints() const
        {
            return _constraints;
        };

        const std::vector<Node*>
        getTimenodes() const
        {
            return _timenodes;
        };
    };
}
#endif /* SCENARIO_HPP_ */

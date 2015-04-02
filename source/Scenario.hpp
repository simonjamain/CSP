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
    class ArgumentInvalidException//TODO: message
    {
    public:
        ArgumentInvalidException(){}
        ~ArgumentInvalidException(){}
    };
    class Scenario
    {
    private:
        Start* _start;
        std::vector<Constraint*> _constraints;
        std::vector<Node*> _timenodes;
        // this method allow to explicitely attach a constraint to the start node
        Constraint*
        _addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Node* prevTimenode, Timenode* nextTimenode);
        // this create a new timenode and add it to the nodes pool
        Timenode*
        _addTimenode();
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
          Add a constraint with a given prevTimenode and a new nextTimenode
          */
        Constraint*
        addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode);

        /**
         * @brief Scenario::addConstraint Add a new Constraint with start as the prevTimenode and a given nextTimenode
         * @param nominal
         * @param flexBefore
         * @param flexAfter
         * @param prevTimenode
         * @param nextTimenode
         * @return
         */
        Constraint*
        addConstraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, int prevTimenode, Timenode* nextTimenode);

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

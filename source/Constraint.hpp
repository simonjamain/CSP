#ifndef CONSTRAINT_HPP_
#define CONSTRAINT_HPP_

#include "Duration.hpp"
#include "FiniteDuration.hpp"
#include "Timenode.hpp"
#include <constraint_solver/constraint_solver.h>
namespace CSP
{

    class InternalPropertiesNotValidException
    {
    public:
        InternalPropertiesNotValidException(){};
        ~InternalPropertiesNotValidException(){};
    };

    class Constraint
    {
    private:
        FiniteDuration _nominal;
        FiniteDuration _flexBefore;
        Duration _flexAfter;
        Timenode* _prevTimenode;
        Timenode* _nextTimenode;

    public:
        Constraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* prevTimenode, Timenode* nextTimenode)
            :_nominal(nominal),_flexBefore(flexBefore),_flexAfter(flexAfter),_prevTimenode(prevTimenode),_nextTimenode(nextTimenode){};

        void
        setNominal(FiniteDuration duration);

        void
        setFlexBefore(FiniteDuration duration);

        void
        setFlexAfter(Duration duration);

        FiniteDuration
        getMin() throw (InternalPropertiesNotValidException);

        Duration
        getMax() throw (InternalPropertiesNotValidException);

        void
        addConstraints(operations_research::Solver& solver) throw (InternalPropertiesNotValidException);

        void
        validateInternalProperties() throw (InternalPropertiesNotValidException);
    };

}
#endif /* CONSTRAINT_HPP_ */

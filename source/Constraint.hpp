#ifndef CONSTRAINT_HPP_
#define CONSTRAINT_HPP_

#include "Duration.hpp"
#include "FiniteDuration.hpp"
#include "Timenode.hpp"
#include <constraint_solver/constraint_solver.h>
namespace CSP
{
/**
     * @brief The InternalPropertiesNotValidException class Cette exception est destinée à être
     * levée quand les propriétés (durées) d'une contrainte sont incohérentes.
     */
class InternalPropertiesNotValidException
{
public:
    InternalPropertiesNotValidException(){}
    ~InternalPropertiesNotValidException(){}
};

class Constraint
{
private:
    FiniteDuration _nominal;
    FiniteDuration _flexBefore;
    Duration _flexAfter;
    Timenode* _nextTimenode;

public:
    Constraint(FiniteDuration nominal, FiniteDuration flexBefore, Duration flexAfter, Timenode* nextTimenode)
        :_nominal(nominal),_flexBefore(flexBefore),_flexAfter(flexAfter),_nextTimenode(nextTimenode){}

    void
    setNominal(FiniteDuration duration);

    void
    setFlexBefore(FiniteDuration duration);

    void
    setFlexAfter(Duration duration);

    FiniteDuration
    getMin() const throw (InternalPropertiesNotValidException);

    FiniteDuration
    getNominal() const throw (InternalPropertiesNotValidException);

    Duration
    getMax() const throw (InternalPropertiesNotValidException);

    Timenode*
    getNextTimenode();

    void
    applyConstraints(Node* prevTimenode, std::shared_ptr<operations_research::Solver> solver);
};
}
#endif /* CONSTRAINT_HPP_ */

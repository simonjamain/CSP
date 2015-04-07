#include "Constraint.hpp"
#include "Duration.hpp"
#include "FiniteDuration.hpp"

namespace CSP
{
    void
    Constraint::setNominal(FiniteDuration duration)
    {
        _nominal = duration;
    }

    void
    Constraint::setFlexBefore(FiniteDuration duration)
    {
        _flexBefore = duration;
    }

    void
    Constraint::setFlexAfter(Duration duration)
    {
        _flexAfter = duration;
    }

    FiniteDuration
    Constraint::getMin() const
    {
        validateInternalProperties();
        return FiniteDuration(_nominal.getLength() - _flexBefore.getLength());
    }

    Duration
    Constraint::getMax() const
    {
        validateInternalProperties();
        if(_flexAfter.isFinite())
        {
            return Duration{_nominal.getLength() + _flexAfter.getLength()};
        }else
        {
            return Duration{PositiveInfinity{}};
        }
    }

    Timenode*
    Constraint::getNextTimenode()
    {
        return _nextTimenode;
    }

    void
    Constraint::validateInternalProperties() const throw (InternalPropertiesNotValidException)
    {
        if(_flexBefore.getLength() > _nominal.getLength())
        {
            throw(InternalPropertiesNotValidException());
        }
    }

    void
    Constraint::addConstraints(operations_research::Solver& solver) const throw (InternalPropertiesNotValidException)
    {
        //some constraints can be checked internally
        validateInternalProperties() ;

        operations_research::IntExpr* distance = solver.MakeDifference (_nextTimenode->getDate(solver), _prevTimenode->getDate(solver));

        solver.AddConstraint(
                    solver.MakeGreaterOrEqual( distance, int64( getMin().getLength() ) )
                    );

        if(this->getMax().isFinite())
        {
            solver.AddConstraint(
                        solver.MakeLessOrEqual( distance, int64( getMax().getLength() ))
                        );
        }

    }
}


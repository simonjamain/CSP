#include "Constraint.hpp"
#include "Duration.hpp"
#include "FiniteDuration.hpp"
#include "Node.hpp"

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
        return FiniteDuration(_nominal.getLength() - _flexBefore.getLength());
    }

    Duration
    Constraint::getMax() const
    {
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
    Constraint::applyConstraints(Node* prevTimenode, operations_research::Solver& solver) const
    {

        solver.AddConstraint(
                    solver.MakeGreaterOrEqual( solver.MakeIntConst(int64(_nominal.getLength())) , int64(_flexBefore.getLength()) )
                    );

        operations_research::IntExpr* distance = solver.MakeDifference (_nextTimenode->getDate(solver), prevTimenode->getDate(solver));

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


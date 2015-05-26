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

FiniteDuration
Constraint::getNominal() const
{
    return FiniteDuration(_nominal.getLength());
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
Constraint::applyConstraints(Node* prevTimenode, std::shared_ptr<operations_research::Solver> solver)
{
    operations_research::IntVar* prevDate = prevTimenode->getDate(solver);
    operations_research::IntVar* nextDate = _nextTimenode->getDate(solver);

    /*
    solver->AddConstraint(
                solver->MakeGreaterOrEqual( solver->MakeIntConst(int64(_nominal.getLength())) , int64(_flexBefore.getLength()) )
                );
    */

    operations_research::IntExpr* distance = solver->MakeDifference ( nextDate , prevDate );

    //look only nominal duration
    auto cNom = solver->MakeEquality( distance, int64( getNominal().getLength() ) );
    solver->AddConstraint(cNom);


#ifdef CSP_DEBUG_MODEL
    std::cout << "prevDate : " << prevDate->DebugString() << "\n";
    std::cout << "nextDate : " << nextDate->DebugString() << "\n";
#endif
    auto c1 = solver->MakeGreaterOrEqual( distance, int64( getMin().getLength() ) );
    solver->AddConstraint(c1);
#ifdef CSP_DEBUG_MODEL
    std::cout << "C1 : " << c1->DebugString() << "\n";
#endif
    if(this->getMax().isFinite())
    {
        auto c2 = solver->MakeLessOrEqual( distance, int64( getMax().getLength() ));
        solver->AddConstraint(c2);
#ifdef CSP_DEBUG_MODEL
        std::cout << "C2 : " << c2->DebugString() << "\n---------------------------------\n";
#endif
    }


}
}


#include "Constraint.hpp"
#include "Duration.hpp"
#include "FiniteDuration.hpp"
#include "Node.hpp"

namespace CSP
{
void
TimeRelation::setNominal(FiniteDuration duration)
{
    _nominal = duration;
}

void
TimeRelation::setFlexBefore(FiniteDuration duration)
{
    _flexBefore = duration;
}

void
TimeRelation::setFlexAfter(Duration duration)
{
    _flexAfter = duration;
}

FiniteDuration
TimeRelation::getMin() const
{
    return FiniteDuration(_nominal.getLength() - _flexBefore.getLength());
}

FiniteDuration
TimeRelation::getNominal() const
{
    return FiniteDuration(_nominal.getLength());
}

Duration
TimeRelation::getMax() const
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
TimeRelation::getNextTimenode()
{
    return _nextTimenode;
}

void
TimeRelation::applyConstraints(Node* prevTimenode, std::shared_ptr<operations_research::Solver> solver)
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


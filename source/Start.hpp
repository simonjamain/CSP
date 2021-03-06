#ifndef START_HPP_
#define START_HPP_

#include <constraint_solver/constraint_solver.h>
#include "../source/Node.hpp"
#include "../source/Timenode.hpp"

namespace CSP
{
    class Start : public Node
    {
    private:
        virtual
        operations_research::IntVar*
        _makeDate(operations_research::Solver* solver) override;
    };
}
#endif /* START_HPP_ */

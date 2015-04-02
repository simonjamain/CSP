#ifndef NODE_HPP_
#define NODE_HPP_

#include <constraint_solver/constraint_solver.h>

namespace CSP
{
    class Node
    {
    public:
        virtual operations_research::IntVar*
        getDate(operations_research::Solver& solver) = 0;

        virtual ~Node(){}
    };
}
#endif /* NODE_HPP_ */

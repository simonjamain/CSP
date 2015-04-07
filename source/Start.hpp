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
        operations_research::IntVar* _date;
    public:
        Start()
            :_date(NULL)
        {}

        operations_research::IntVar*
        getDate(operations_research::Solver& solver);
    };
}
#endif /* START_HPP_ */

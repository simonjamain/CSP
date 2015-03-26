#ifndef TIMENODE_HPP_
#define TIMENODE_HPP_

#include <constraint_solver/constraint_solver.h>

namespace CSP
{
    class Timenode
    {
    private:
        operations_research::IntVar* _date;
    public:
        Timenode()
            :_date(NULL){};

        operations_research::IntVar*
        getDate(operations_research::Solver& solver);
    };
}
#endif /* TIMENODE_HPP_ */

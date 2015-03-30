#ifndef CSP_HPP_
#define CSP_HPP_

#include <constraint_solver/constraint_solver.h>
#include "Constraint.hpp"

namespace CSP
{
    bool
    isValid(std::vector<Constraint> constraints);
}
#endif /* CSP_HPP_ */

#ifndef CSP_HPP_
#define CSP_HPP_

#include <constraint_solver/constraint_solver.h>
#include "../source/Scenario.hpp"
#include <iostream>

namespace CSP
{
    /**
     * @brief isValid Détermine la faisabilité d'un scénario.
     * @param scenario Le scénario à contrôler.
     * @return True si valide, False si non valide.
     */
    bool
    isValid(Scenario& scenario);

    void
    generateTikzCode(Scenario& scenario, std::ostream& output);
}
#endif /* CSP_HPP_ */

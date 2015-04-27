
#include "../source/Scenario.hpp"
#include "../source/csp.hpp"
#include "../source/Duration.hpp"
#include "../source/Start.hpp"
#include "../source/Timenode.hpp"

int main( int argc, const char* argv[] )
{
    CSP::Timenode T1;
    std::shared_ptr<operations_research::Solver> solver = std::make_shared<operations_research::Solver>("i-score time constraint Solver");

    operations_research::IntVar* T1_1;
    T1_1 = T1.getDate(solver);

    std::cout << "eq : " << (T1_1 == T1.getDate(solver));
    return 0;
}

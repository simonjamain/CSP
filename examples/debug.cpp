#include "../source/Scenario.hpp"
#include "../source/csp.hpp"
#include "../source/Duration.hpp"
#include "../source/Start.hpp"
#include "../source/Timenode.hpp"

int main( int argc, const char* argv[] )
{
    CSP::Scenario scenario;

        scenario.addConstraint(
                    CSP::FiniteDuration{10},
                    CSP::FiniteDuration{0},
                    CSP::Duration{0});

        CSP::isValid(scenario);

        return 0;
}

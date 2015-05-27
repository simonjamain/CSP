
#include "../source/Scenario.hpp"
#include "../source/csp.hpp"
#include "../source/Duration.hpp"
#include "../source/Start.hpp"
#include "../source/Timenode.hpp"
#include "../test/testHelpers.hpp"
#include <fstream>

int main( int argc, const char* argv[] )
{
    CSP::Scenario scenario;

    CSP::Constraint* c1 = scenario.addConstraint(
                FDUR_10,
                FDUR_5,
                DUR_5
                );

    CSP::Timenode* t1 = c1->getNextTimenode();

    CSP::Constraint* c2 = scenario.addConstraint(
                FDUR_10,
                FDUR_5,
                DUR_5,
                t1
                );

    CSP::Timenode* t2 = c2->getNextTimenode();

    CSP::Constraint* c3 = scenario.addConstraint(
                FDUR_20,
                FDUR_10,
                DUR_0,
                CSP::ConstraintAttachment::START,
                t2
                );

    CSP::Constraint* c4 = scenario.addConstraint(
                FDUR_10,
                FDUR_5,
                DUR_5,
                t2
                );

    CSP::Timenode* t3 =  c4->getNextTimenode();


    generateTikzCode(scenario, std::cout, "Debug");
    //generateTikzCode(scenario, CSP::graphicsFile, "Debug");


    return 0;
}

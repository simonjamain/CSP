
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

    CSP::TimeRelation* c1 = scenario.addTimeRelation(
                FDUR_10,
                FDUR_0,
                DUR_0
                );

    CSP::Timenode* t1 = c1->getNextTimenode();

    CSP::TimeRelation* c2 = scenario.addTimeRelation(
                FDUR_10,
                FDUR_3,
                DUR_3,
                CSP::ConstraintAttachment::START,
                t1
                );

    CSP::TimeRelation* c3 = scenario.addTimeRelation(
                FDUR_10,
                FDUR_3,
                DUR_INF,
                CSP::ConstraintAttachment::START,
                t1
                );

    CSP::TimeRelation* c4 = scenario.addTimeRelation(
                FDUR_10,
                FDUR_10,
                DUR_3,
                CSP::ConstraintAttachment::START,
                t1
                );

    CSP::TimeRelation* c5 = scenario.addTimeRelation(
                FDUR_10,
                FDUR_10,
                DUR_INF,
                CSP::ConstraintAttachment::START,
                t1
                );


    generateTikzCode(scenario, std::cout, "Presentation");

    return 0;
}

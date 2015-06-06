#include "csp.hpp"
#include <constraint_solver/constraint_solver.h>
#include "Constraint.hpp"
#include <iostream>

namespace CSP
{
bool
isValid(Scenario& scenario)
{
    bool valid = false;
    std::shared_ptr<operations_research::Solver> solver = std::make_shared<operations_research::Solver>("i-score time constraint Solver");

    const std::vector<Node*> timenodes = scenario.getTimenodes();
    std::vector<operations_research::IntVar*> dates;

    for(auto &node : timenodes)
    {
        dates.push_back( node->getDate(solver) );
        try
        {
            node->applyConstraints(solver);
        }catch(InternalPropertiesNotValidException e)
        {
            return false;
        }
    }

    operations_research::DecisionBuilder* const db = solver->MakePhase(
                dates,
                operations_research::Solver::CHOOSE_FIRST_UNBOUND,
                operations_research::Solver::ASSIGN_MIN_VALUE);

    solver->NewSearch(db);

    if(solver->NextSolution())
    {

#ifdef CSP_LOG_VALUES
        // print individual values
        std::cout << "-----------------------------------------\n";
        int i = 0;
        for(auto &timenode : timenodes)
        {
            std::cout << "T" << i << " : " << timenode->getDate(solver)->Value() << "\n";
            ++i;

            timenode->date = timenode->getDate(solver)->Value();
        }
#endif

        valid = true;
    }

    solver->EndSearch();
    return valid;
}

void
generateTikzCode(Scenario& scenario, std::ostream& output, std::string figureName)
{
    if(isValid(scenario))
    {
        output << "\\def\\schemaScenario" << figureName << "{%\n";
        output << "\\begin{tikzpicture}[scale=0.1]%\n";


        const std::vector<Node*> timenodes = scenario.getTimenodes();

        int Tcounter = 0;
        int Ccounter = 1;
        int yPos = 0;
        std::string constraintName;
        std::string nodeName;
        int date;
        for(auto &node : timenodes)
        {
            date = (int) node->date;

            output << "\\def\\date{" << date << "};%\n";

            for(auto &constraint : node->getNextTimeRelations())
            {
                constraintName = "C"+std::to_string(Ccounter);

                yPos = -2*Ccounter;

                output << "\\def\\contraintName{" << constraintName << "};%\n";
                output << "\\def\\ypos{" << yPos << "};%\n";
                output << "\\def\\min{" << constraint->getMin().getLength() << "};%\n";
                output << "\\def\\nom{" << constraint->getNominal().getLength() << "};%\n";
                if(constraint->getMax().isFinite())
                {output << "\\def\\max{" << constraint->getMax().getLength() << "};%\n";}
                else
                {output << "\\def\\max{" << constraint->getNominal().getLength()+1 << "};%\n";}
                output << "\\fill (\\date,\\ypos) circle (0.3);%\n";
                output << "\\fill (\\date+\\nom,\\ypos) circle (0.3);%\n";
                output << "\\draw (\\date,\\ypos) -- ++(\\min,0) node[midway,above,scale=0.25] {\\contraintName};%\n";
                output << "\\draw (\\date+\\min,\\ypos+0.5) -- ++(0,-1);%\n";
                output << "\\draw[densely dotted] (\\date+\\min,\\ypos) -- (\\date+\\max,\\ypos);%\n";
                if(constraint->getMax().isFinite())
                {output << "\\draw (\\date+\\max,\\ypos+0.5) -- ++(0,-1);%\n%\n";}
                Ccounter++;
            }

            if(Tcounter == 0)
            {
                nodeName = "START";
            }else
            {
                nodeName = "\\Huge T"+std::to_string(Tcounter);
            }

            output << "\\def\\nodeName{" << nodeName << "};%\n";
            output << "\\def\\ypos{" << (yPos-2) << "};%\n";
            output << "\\draw (\\date,0) -- ++(-1,0.5) -- ++(0,2) -- ++(2,0) -- ++(0,-2) -- ++(-1,-0.5) -- (\\date, \\ypos);%\n";
            output << "\\draw (\\date,1.5) node[scale=0.17]{\\nodeName};%\n%\n";

            Tcounter++;
        }
        output << "\\end{tikzpicture}%\n";
        output << "}\n";
    }else
    {
        std::cout << "scenario " << figureName << " invalide\n";
    }
}
}

#include <rhea/simplex_solver.hpp>
#include <rhea/iostream.hpp>

using namespace rhea;

int main( int argc, const char* argv[] )
{
    variable left, mid, right;
    simplex_solver solver;

    solver.add_constraints(
    {
        mid == (left + right) / 2,
        right == left + 10,
        right <= 100,
        left >= 0
    });
    solver.suggest(mid, 2);

    std::cout << left << " " << mid << " " << right << std::endl;
    // Prints "0 5 10"

    return 0;
}


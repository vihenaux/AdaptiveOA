#include <iostream>
#include "algorithms/LocalSearch.hpp"
#include "functions/OneMax.hpp"
#include "neighborhoods/BitFlipNeighborhood.hpp"
#include "solutions/BitString.hpp"

using namespace AdaptiveOA;

int main()
{
    constexpr std::size_t bitstring_size = 100;

    // Initialize components
    BitString solution(bitstring_size);
    OneMax function;
    BitFlipNeighborhood neighborhood(bitstring_size);

    FirstImprovementHillClimber<BitString, OneMax, BitFlipNeighborhood> hc(std::move(neighborhood));
    hc.run(solution, function);

    // Output result
    std::cout << "Best solution:  " << hc.best_solution().to_string() << "\n";
    std::cout << "Best score:     " << hc.best_score().value() << "\n";
    std::cout << "Evaluations:    " << function.get_nb_evaluations() << "\n";

    return 0;
}

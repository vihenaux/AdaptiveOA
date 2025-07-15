#include <iostream>
#include "algorithms/LocalSearch.hpp"
#include "functions/OneMax.hpp"
#include "neighborhoods/BitFlipNeighborhood.hpp"
#include "solutions/BitString.hpp"
#include "utils/CLI.hpp"

#include "algorithms/local_search_specifics/pivot_rules/Tabu.hpp"
#include "algorithms/local_search_specifics/terminate_conditions/NoLimit.hpp"
#include "algorithms/local_search_specifics/terminate_conditions/IterationLimit.hpp"
#include "algorithms/local_search_specifics/terminate_conditions/FunctionCallLimit.hpp"
#include "algorithms/local_search_specifics/terminate_conditions/TimeLimit.hpp"

using namespace AdaptiveOA;

int main(int argc, char **argv)
{
    CLI::init(argc, argv);

    constexpr std::size_t bitstring_size = 100;
    // Initialize components
    BitString solution(bitstring_size);
    OneMax function;
    BitFlipNeighborhood neighborhood(bitstring_size);

    //FirstImprovementHillClimber<BitString, OneMax, BitFlipNeighborhood> hc(std::move(neighborhood));
    LocalSearch<BitString,OneMax,BitFlipNeighborhood,Tabu<BitFlipNeighborhood>,TimeLimit> hc(std::move(neighborhood));

    Score total_score = 0;
    for(unsigned int i(0); i < 1000000; ++i)
    {
        function.reset();
        solution.randomize();
        hc.run(solution, function);
        total_score += hc.best_score().value();
    }

    // Output result
    std::cout << "Best solution:  " << hc.best_solution().to_string() << "\n";
    std::cout << "Best score:     " << hc.best_score().value() << "\n";
    std::cout << "Evaluations:    " << function.get_nb_evaluations() << "\n";
    std::cout << "Mean score:     " << total_score/1000000 << "\n";

    return 0;
}

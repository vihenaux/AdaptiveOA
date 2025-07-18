#include <iostream>
#include "algorithms/LocalSearch.hpp"
#include "functions/OneMax.hpp"
#include "functions/NK.hpp"
#include "neighborhoods/BitFlipNeighborhood.hpp"
#include "solutions/BitString.hpp"
#include "utils/Random.hpp"
#include "utils/CLI.hpp"

#include "algorithms/local_search_specifics/pivot_rules/Tabu.hpp"
#include "algorithms/local_search_specifics/terminate_conditions/NoLimit.hpp"
#include "algorithms/local_search_specifics/terminate_conditions/IterationLimit.hpp"
#include "algorithms/local_search_specifics/terminate_conditions/FunctionCallLimit.hpp"
#include "algorithms/local_search_specifics/terminate_conditions/TimeLimit.hpp"

using namespace AdaptiveOA;

int main(int argc, char **argv)
{
    Random::init();
    CLI::init(argc, argv);

    constexpr std::size_t bitstring_size = 64;
    // Initialize components
    BitString solution(bitstring_size);
    OneMax function;
    NK nk_function("nk_64_1.0");
    BitFlipNeighborhood neighborhood(bitstring_size);

    FirstImprovementHillClimber<BitString, NK, BitFlipNeighborhood> hc(std::move(neighborhood));
    //LocalSearch<BitString,NK,BitFlipNeighborhood,SimulatedAnnealing,IterationLimit> hc(std::move(neighborhood));

    Score overall_best_score = 0;
    Score total_score = 0;
    for(unsigned int i(0); i < 10000; ++i)
    {
        nk_function.reset();
        solution.randomize();
        hc.run(solution, nk_function);
        total_score += hc.best_score().value();
        overall_best_score = (overall_best_score < hc.best_score().value()) ? hc.best_score().value() : overall_best_score;
    }

    // Output result
    std::cout << "Best solution:  " << hc.best_solution().to_string() << "\n";
    std::cout << "Best score:     " << overall_best_score << "\n";
    std::cout << "Evaluations:    " << nk_function.get_nb_evaluations() << "\n";
    std::cout << "Mean score:     " << total_score/10000 << "\n";

    return 0;
}

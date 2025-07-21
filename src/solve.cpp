#include "solve.hpp"
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

template<
    typename Solution,
    typename Function,
    typename Neighborhood,
    typename PivotRule,
    typename TerminateCondition
>
void run_algorithm(Solution&& sol, Function&& f, Neighborhood&& nh)
{
    LocalSearch<Solution, Function, Neighborhood, PivotRule, TerminateCondition> algo(std::forward<Neighborhood>(nh));
    algo.run(sol, f);

    std::cout << algo.best_score().value() << std::endl;
}

template<
    typename Solution,
    typename Function,
    typename Neighborhood,
    typename PivotRule
>
void dispatch_termination(Solution&& sol, Function&& f, Neighborhood&& nh)
{
    if(CLI::is_option_activated(CLI::Option::iteration_limit))
    {
        run_algorithm<Solution, Function, Neighborhood, PivotRule, IterationLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else if(CLI::is_option_activated(CLI::Option::function_call_limit))
    {
        run_algorithm<Solution, Function, Neighborhood, PivotRule, FunctionCallLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else if(CLI::is_option_activated(CLI::Option::time_limit))
    {
        run_algorithm<Solution, Function, Neighborhood, PivotRule, TimeLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else if(CLI::is_option_activated(CLI::Option::no_limit))
    {
        run_algorithm<Solution, Function, Neighborhood, PivotRule, NoLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else
    {
        std::cerr << "No termination condition selected.\n";
    }
}

template<typename Solution, typename Function, typename Neighborhood>
void dispatch_pivot(Solution&& sol, Function&& f, Neighborhood&& nh)
{
    if(CLI::is_option_activated(CLI::Option::first_improvement))
    {
        dispatch_termination<Solution, Function, Neighborhood, FirstImprovement>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else if(CLI::is_option_activated(CLI::Option::best_improvement))
    {
        dispatch_termination<Solution, Function, Neighborhood, BestImprovement>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else if(CLI::is_option_activated(CLI::Option::simulated_annealing))
    {
        dispatch_termination<Solution, Function, Neighborhood, SimulatedAnnealing>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else if(CLI::is_option_activated(CLI::Option::tabu))
    {
        dispatch_termination<Solution, Function, Neighborhood, Tabu<Neighborhood>>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else
    {
        std::cerr << "No pivot rule selected.\n";
    }
}

template<typename Solution, typename Function>
void dispatch_neighborhood(Solution&& sol, Function&& f)
{
    //if(CLI::is_option_activated(CLI::Option::bitflip_neighborhood))
    //{
        BitFlipNeighborhood nh(sol.size());
        dispatch_pivot(std::forward<Solution>(sol), std::forward<Function>(f), std::move(nh));
    //}
    //else
    //{
    //    std::cerr << "No neighborhood type selected.\n";
    //}
}

void localsearch_solve()
{
    if(CLI::is_option_activated(CLI::Option::nk))
    {
        NK objective_function(std::string(CLI::get_option_value(CLI::Option::nk)));
        BitString solution(objective_function.get_n());
        dispatch_neighborhood(std::move(solution), std::move(objective_function));
    }
    else if(CLI::is_option_activated(CLI::Option::onemax))
    {
        OneMax objective_function;
        BitString solution(static_cast<std::size_t>(std::stoi(std::string(get_option_value(CLI::Option::onemax)))));
        dispatch_neighborhood(std::move(solution), std::move(objective_function));
    }
    else
    {
        std::cerr << "No problem selected.\n";
    }
}

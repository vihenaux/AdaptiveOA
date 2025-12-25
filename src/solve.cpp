#include "solve.hpp"
#include <iostream>

#include "utils/CLI.hpp"
#include "algorithms/LocalSearch.hpp"
#include "algorithms/IteratedLocalSearch.hpp"

#include "functions/OneMax.hpp"
#include "functions/NK.hpp"
#include "functions/MaxSat.hpp"

#include "neighborhoods/BitFlipNeighborhood.hpp"
#include "solutions/BitString.hpp"

#include "algorithms/pivot_rules/impl/BestImprovement.hpp"
#include "algorithms/pivot_rules/impl/FirstImprovement.hpp"
#include "algorithms/pivot_rules/impl/SimulatedAnnealing.hpp"
#include "algorithms/pivot_rules/impl/Tabu.hpp"
#include "algorithms/pivot_rules/impl/WorstImprovement.hpp"
#include "algorithms/terminate_conditions/impl/NoLimit.hpp"
#include "algorithms/terminate_conditions/impl/IterationLimit.hpp"
#include "algorithms/terminate_conditions/impl/FunctionCallLimit.hpp"
#include "algorithms/terminate_conditions/impl/TimeLimit.hpp"

using namespace AdaptiveOA;

template<
    typename Solution,
    typename Function,
    typename Neighborhood,
    typename PivotRule,
    typename TerminateConditionLS,
    typename TerminateConditionILS
>
void run_ils(Solution&& sol, Function&& f, Neighborhood&& nh, TerminateConditionILS && terminate_condition_ils)
{
    std::size_t ils_nb_random_mutation = static_cast<std::size_t>(std::stoi(std::string(get_option_value(CLI::Option::ils_nb_random_mutation))));
    IteratedLocalSearch<Solution, Function, Neighborhood, PivotRule, TerminateConditionLS, TerminateConditionILS> algo(std::forward<Neighborhood>(nh), std::forward<TerminateConditionILS>(terminate_condition_ils), ils_nb_random_mutation);
    algo.run(sol, f);

    std::cout << algo.best_score().value() << std::endl;
}

template<
    typename Solution,
    typename Function,
    typename Neighborhood,
    typename PivotRule,
    typename TerminateConditionLS
>
void dispatch_ils(Solution&& sol, Function&& f, Neighborhood&& nh)
{
    if(CLI::is_option_activated(CLI::Option::ils_iteration_limit))
    {
        IterationLimit iteration_limit(static_cast<std::size_t>(std::stoi(std::string(get_option_value(CLI::Option::ils_iteration_limit)))));
        run_ils<Solution, Function, Neighborhood, PivotRule, TerminateConditionLS, IterationLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh), std::move(iteration_limit));
    }
    else if(CLI::is_option_activated(CLI::Option::ils_function_call_limit))
    {
        FunctionCallLimit function_call_limit(static_cast<std::size_t>(std::stoi(std::string(get_option_value(CLI::Option::ils_function_call_limit)))));
        run_ils<Solution, Function, Neighborhood, PivotRule, TerminateConditionLS, FunctionCallLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh), std::move(function_call_limit));
    }
    else if(CLI::is_option_activated(CLI::Option::ils_time_limit))
    {
        TimeLimit time_limit(static_cast<std::size_t>(std::stoi(std::string(get_option_value(CLI::Option::ils_time_limit)))));
        run_ils<Solution, Function, Neighborhood, PivotRule, TerminateConditionLS, TimeLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh), std::move(time_limit));
    }
    else if(CLI::is_option_activated(CLI::Option::ils_no_limit))
    {
        NoLimit no_limit;
        run_ils<Solution, Function, Neighborhood, PivotRule, TerminateConditionLS, NoLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh), std::move(no_limit));
    }
    else
    {
        std::cerr << "No termination condition selected.\n";
    }
}

template<
    typename Solution,
    typename Function,
    typename Neighborhood,
    typename PivotRule,
    typename TerminateCondition
>
void dispatch_algorithm(Solution&& sol, Function&& f, Neighborhood&& nh)
{
    if(CLI::is_option_activated(CLI::Option::localsearch))
    {
        LocalSearch<Solution, Function, Neighborhood, PivotRule, TerminateCondition> algo(std::forward<Neighborhood>(nh));
        algo.run(sol, f);

        std::cout << algo.best_score().value() << std::endl;
    }
    else if(CLI::is_option_activated(CLI::Option::iteratedlocalsearch))
    {
        dispatch_ils<Solution, Function, Neighborhood, PivotRule, IterationLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else
    {
        std::cerr << "No optimization algorithm selected.\n";
    }
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
        dispatch_algorithm<Solution, Function, Neighborhood, PivotRule, IterationLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else if(CLI::is_option_activated(CLI::Option::function_call_limit))
    {
        dispatch_algorithm<Solution, Function, Neighborhood, PivotRule, FunctionCallLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else if(CLI::is_option_activated(CLI::Option::time_limit))
    {
        dispatch_algorithm<Solution, Function, Neighborhood, PivotRule, TimeLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
    }
    else if(CLI::is_option_activated(CLI::Option::no_limit))
    {
        dispatch_algorithm<Solution, Function, Neighborhood, PivotRule, NoLimit>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
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
    else if(CLI::is_option_activated(CLI::Option::worst_improvement))
    {
        dispatch_termination<Solution, Function, Neighborhood, WorstImprovement>(std::forward<Solution>(sol), std::forward<Function>(f), std::forward<Neighborhood>(nh));
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
        OneMax objective_function(static_cast<std::size_t>(std::stoi(std::string(get_option_value(CLI::Option::onemax)))));
        BitString solution(static_cast<std::size_t>(std::stoi(std::string(get_option_value(CLI::Option::onemax)))));
        dispatch_neighborhood(std::move(solution), std::move(objective_function));
    }
    else if(CLI::is_option_activated(CLI::Option::maxsat))
    {
        MaxSat objective_function(std::string(CLI::get_option_value(CLI::Option::maxsat)));
        BitString solution(objective_function.get_nb_literals());
        dispatch_neighborhood(std::move(solution), std::move(objective_function));
    }
    else
    {
        std::cerr << "No problem selected.\n";
    }
}

#pragma once

#include "../core/AlgorithmBase.hpp"
#include "../core/SolutionBase.hpp"
#include "../core/FunctionBase.hpp"
#include "../core/NeighborhoodBase.hpp"
#include "local_search_specifics/PivotRuleBase.hpp"
#include "local_search_specifics/TerminateConditionBase.hpp"
#include "local_search_specifics/TerminateConditionFactory.hpp"
#include "local_search_specifics/PivotRuleFactory.hpp"
#include "local_search_specifics/pivot_rules/BestImprovement.hpp"
#include "local_search_specifics/pivot_rules/FirstImprovement.hpp"
#include "local_search_specifics/terminate_conditions/NoLimit.hpp"

namespace AdaptiveOA {

    template<
            SolutionLike Solution,
            typename Function,
            NeighborhoodLike Neighborhood,
            typename PivotRule,
            typename TerminateCondition
    >
    requires FunctionLike<Function, Solution> &&
            PivotRuleLike<PivotRule, Neighborhood, Solution, Function> &&
            TerminateConditionLike<TerminateCondition, Function, Solution>
    class LocalSearch : public AlgorithmBase<
            LocalSearch<Solution, Function, Neighborhood, PivotRule, TerminateCondition>,
            Solution,
            Function>
    {
        public:

        void do_run(Solution& solution, const Function& objective_function)
        {
            PivotRule& pivot_rule = PivotRuleFactory::create<PivotRule>();
            TerminateCondition& terminate_condition = TerminateConditionFactory::create<TerminateCondition, Function>();

            Score current_score = objective_function(solution);
            set_best_solution(solution, current_score);

            // TODO: Pass search space info to the neighborhood
            Neighborhood neighborhood;
            while(!terminate_condition.should_terminate())
            {
                auto chosen_mutation = pivot_rule.choose(neighborhood, solution, objective_function);
                if (!chosen_mutation)
                    break;
                solution.mutate(*chosen_mutation);

                if(solution.get_score() > this->best_score())
                    set_best_solution(solution, solution.get_score());

                terminate_condition.update(objective_function);
            }
        }
    };

    template<SolutionLike Solution, typename Function, NeighborhoodLike Neighborhood>
    requires FunctionLike<Function, Solution>
    using FirstImprovementHillClimber = LocalSearch<Solution, Function, Neighborhood, FirstImprovement, NoLimit>;

    template<SolutionLike Solution, typename Function, NeighborhoodLike Neighborhood>
    requires FunctionLike<Function, Solution>
    using BestImprovementHillClimber = LocalSearch<Solution, Function, Neighborhood, FirstImprovement, NoLimit>;

} // namespace AdaptiveOA

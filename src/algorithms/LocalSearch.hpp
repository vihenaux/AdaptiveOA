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
            FunctionLike Function,
            NeighborhoodLike Neighborhood,
            typename PivotRule,
            typename TerminateCondition
    >
    requires PivotRuleLike<PivotRule, Neighborhood, Solution, Function> &&
            TerminateConditionLike<TerminateCondition, Function>
    class LocalSearch : public AlgorithmBase<
            LocalSearch<Solution, Function, Neighborhood, PivotRule, TerminateCondition>,
            Solution,
            Function>
    {
        public:

        void do_run(Solution& solution, const Function& objective_function)
        {
            const PivotRule& pivot_rule = PivotRuleFactory::create<PivotRule, Neighborhood, Solution, Function>();
            TerminateCondition terminate_condition = TerminateConditionFactory::create<TerminateCondition, Function>();

            Score current_score = objective_function(solution);
            this->set_best_solution(solution, current_score);

            // TODO: Pass search space info to the neighborhood
            Neighborhood neighborhood(100);
            while(!terminate_condition.should_terminate())
            {
                auto chosen_mutation = pivot_rule.choose(neighborhood, solution, objective_function);
                if (!chosen_mutation)
                    break;
                solution.mutate(*chosen_mutation);

                if(solution.get_score() > this->best_score())
                    this->set_best_solution(solution, solution.get_score().value());

                terminate_condition.update(objective_function);
            }
        }
    };

    template<SolutionLike Solution, FunctionLike Function, NeighborhoodLike Neighborhood>
    using FirstImprovementHillClimber = LocalSearch<Solution, Function, Neighborhood, FirstImprovement, NoLimit>;

    template<SolutionLike Solution, FunctionLike Function, NeighborhoodLike Neighborhood>
    using BestImprovementHillClimber = LocalSearch<Solution, Function, Neighborhood, FirstImprovement, NoLimit>;

} // namespace AdaptiveOA

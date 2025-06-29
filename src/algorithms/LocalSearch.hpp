#pragma once

#include "../core/AlgorithmBase.hpp"
#include "../core/SolutionBase.hpp"
#include "../core/FunctionBase.hpp"
#include "../core/NeighborhoodBase.hpp"
#include "local_search_specifics/PivotRuleBase.hpp"
#include "local_search_specifics/TerminateConditionBase.hpp"
#include "local_search_specifics/TerminateConditionFactory.hpp"
#include "local_search_specifics/PivotRuleFactory.hpp"

namespace AdaptiveOA {

    template<
            SolutionLike SolutionT,
            FunctionLike FunctionT,
            NeighborhoodLike Neighborhood,
            typename PivotRule,
            typename TerminateCondition
    >
    requires PivotRuleLike<PivotRule, Neighborhood, SolutionT, FunctionT> &&
            TerminateConditionLike<TerminateCondition, FunctionT>
    class LocalSearch : public AlgorithmBase<
            LocalSearch<SolutionT, FunctionT, Neighborhood, PivotRule, TerminateCondition>,
            Solution,
            Function>
    {
        public:

        void do_run(Solution& solution, const Function& objective_function)
        {
            PivotRule& pivot_rule = PivotRuleFactory::create<PivotRule>();
            TerminateCondition& terminate_condition = TerminateConditionFactory::create<TerminateCondition, Function>();

            Fitness current_score = objective_function(solution);
            set_best_solution(solution, current_score);

            // TODO: Pass search space info to the neighborhood
            Neighborhood neighborhood;
            while(!terminate_condition.should_terminate())
            {
                auto chosen_mutation = pivot_rule.choose(neighborhood, solution, objective_function);
                if (!chosen_mutation)
                    break;
                solution.mutate(*chosen_mutation);

                if(solution.get_score() > best_score())
                    set_best_solution(solution, solution.get_score());

                terminate_condition.update(f);*
            }
        }
    };

} // namespace AdaptiveOA

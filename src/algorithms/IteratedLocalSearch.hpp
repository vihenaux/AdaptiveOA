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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

namespace AdaptiveOA
{

    template<
            SolutionLike Solution,
            FunctionLike Function,
            NeighborhoodLike Neighborhood,
            typename PivotRule,
            typename TerminateConditionLS,
            typename TerminateConditionILS
    >
    requires PivotRuleLike<PivotRule, Neighborhood, Solution, Function> &&
            TerminateConditionLike<TerminateConditionLS, Function> &&
            TerminateConditionLike<TerminateConditionILS, Function>
    class IteratedLocalSearch : public AlgorithmBase<
            IteratedLocalSearch<Solution, Function, Neighborhood, PivotRule, TerminateConditionLS, TerminateConditionILS>,
            Solution,
            Function>
    {
        public:

        IteratedLocalSearch(Neighborhood && neighborhood, TerminateConditionILS && terminate_condition, std::size_t nb_random_mutations) :
            m_neighborhood(neighborhood),
            m_localsearch(std::move(neighborhood)),
            m_nb_random_mutation(nb_random_mutations),
            m_terminate_condition(std::move(terminate_condition)) {}

        void do_run(Solution& solution, const Function& objective_function)
        {
            objective_function(solution);
            this->set_best_solution(solution);

            while(!m_terminate_condition.should_terminate())
            {
                m_localsearch.run(solution, objective_function);

                if(solution.get_score() > this->best_score())
                    this->set_best_solution(solution);

                for(unsigned int i(0); i < m_nb_random_mutation; ++i)
                {
                    m_neighborhood.reset();
                    auto random_mutation = m_neighborhood.next_mutation();
                    objective_function(solution, random_mutation);
                    solution.mutate(random_mutation);

                    if(solution.get_score() > this->best_score())
                        this->set_best_solution(solution);
                }

                m_terminate_condition.update(objective_function);
            }
        }

        private:

        Neighborhood m_neighborhood;
        LocalSearch<Solution, Function, Neighborhood, PivotRule, TerminateConditionLS> m_localsearch;
        std::size_t m_nb_random_mutation;
        TerminateConditionILS m_terminate_condition;
    };

#pragma clang diagnostic pop

} // namespace AdaptiveOA

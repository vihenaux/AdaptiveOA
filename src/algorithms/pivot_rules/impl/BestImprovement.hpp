#pragma once

#include <optional>
#include "../PivotRuleBase.hpp"
#include "../../../core/NeighborhoodBase.hpp"
#include "../../../core/MutationBase.hpp"
#include "../../../core/SolutionBase.hpp"
#include "../../../core/FunctionBase.hpp"

namespace AdaptiveOA
{

    struct BestImprovement
    {
        template<
                NeighborhoodLike Neighborhood,
                SolutionLike Solution,
                FunctionLike Function
        >
        std::optional<typename Neighborhood::Mutation> choose(Neighborhood& nh, Solution& sol, const Function& f) const
        {
            Score current_score = sol.get_score().value_or(f(sol));

            std::optional<typename Neighborhood::Mutation> best_mutation;

            while(nh.mutation_available())
            {
                auto mutation = nh.next_mutation();
                Score new_score = f(sol, mutation);

                if((best_mutation && best_mutation.value().get_score() < new_score) ||
                    new_score > current_score)
                {
                    best_mutation = std::move(mutation);
                }
            }

            return best_mutation;
        }
    };

} // namespace AdaptiveOA

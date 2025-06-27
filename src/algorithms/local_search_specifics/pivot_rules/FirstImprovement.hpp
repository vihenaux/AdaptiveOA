#pragma once

#include <optional>
#include "../PivotRuleBase.hpp"
#include "../../../core/NeighborhoodBase.hpp"
#include "../../../core/MutationBase.hpp"
#include "../../../core/SolutionBase.hpp"
#include "../../../core/FunctionBase.hpp"

namespace AdaptiveOA
{

    struct FirstImprovement
    {
        template<
                NeighborhoodLike Neighborhood,
                SolutionLike Solution,
                FunctionLike Function
        >
        std::optional<typename Neighborhood::Mutation> choose(Neighborhood& nh, Solution& sol, const Function& f) const
        {
            auto current_score = sol.get_score();
            if(!current_score)
            {
                current_score = f(sol);
            }

            while(nh.mutation_available())
            {
                auto mutation = nh.next_mutation();

                auto new_score = f(sol, mutation);

                if (new_score > current_score)
                {
                    return mutation;
                }
            }

            return std::nullopt;
        }
    };

} // namespace AdaptiveOA

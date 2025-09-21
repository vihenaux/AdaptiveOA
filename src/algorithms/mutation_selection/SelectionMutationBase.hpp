#pragma once

#include <concepts>
#include <vector>

namespace AdaptiveOA {

    template<
            typename Rule,
            typename Neighborhood,
            typename Solution,
            typename Function
    >
    concept MutationSelectionLike =
            NeighborhoodLike<Neighborhood> &&
            SolutionLike<Solution> &&
            FunctionLike<Function> &&
            requires(Rule rule, Neighborhood& nh, Solution& sol, const Function& f, int n)
    {
        typename Neighborhood::Mutation;
        requires MutationLike<typename Neighborhood::Mutation>;


        { rule.choose(nh, sol, f, n) } -> std::same_as<std::vector<typename Neighborhood::Mutation>>;
    };

} // namespace AdaptiveOA

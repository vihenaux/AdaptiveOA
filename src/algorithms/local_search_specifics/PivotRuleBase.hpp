#pragma once

#include <concepts>
#include <optional>

namespace AdaptiveOA {

    template<
            typename Rule,
            typename Neighborhood,
            typename Solution,
            typename Function
    >
    concept PivotRuleLike =
            NeighborhoodLike<Neighborhood> &&
            SolutionLike<Solution> &&
            FunctionLike<Function, Solution> &&
            requires(Rule rule, Neighborhood& nh, Solution& sol, const Function& f)
    {
        typename Neighborhood::Mutation;
        requires MutationLike<typename Neighborhood::Mutation>;

        { rule.choose(nh, sol, f) } -> std::same_as<std::optional<typename Neighborhood::Mutation>>;
    };

} // namespace AdaptiveOA

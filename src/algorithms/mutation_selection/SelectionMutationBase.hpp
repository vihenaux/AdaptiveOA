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


#pragma once

#include <concepts>
#include <vector>
#include "../../mutations/PopulationMutation.hpp"
#include "../../neighborhoods/PopulationNeighborhood.hpp"

namespace AdaptiveOA {

    template<
            typename Selection,
            typename Neighborhood,
            typename Solution,
            typename Function
    >
    concept MutationSelectionLike =
        SolutionLike<Solution> &&
        FunctionLike<Function> &&
        // Require the neighborhood itself to be a PopulationNeighborhood
        requires {
            typename Neighborhood::BaseNeighborhood;
            requires std::derived_from<Neighborhood, PopulationNeighborhood<typename Neighborhood::BaseNeighborhood>>;
        } &&
        requires(Selection selection, Neighborhood& nh, std::vector<Solution>& population, const Function& f, int n)
    {
        typename Neighborhood::Mutation;

        // Require the mutation to be a PopulationMutation
        requires std::derived_from<typename Neighborhood::Mutation,
                                   PopulationMutation<typename Neighborhood::Mutation::BaseMutation>>;

        // Require choose(...) to return a vector of PopulationMutations
        { selection.choose(nh, population, f, n) } -> std::same_as<std::vector<typename Neighborhood::Mutation>>;
    };

} // namespace AdaptiveOA


#pragma once

#include <concepts>
#include <vector>
#include "../../mutations/PopulationMutation.hpp"
#include "../../neighborhoods/PopulationNeighborhood.hpp"

namespace AdaptiveOA {

    template<typename T>
    struct is_population_neighborhood : std::false_type {};

    template<typename Inner>
    struct is_population_neighborhood<PopulationNeighborhood<Inner>> : std::bool_constant<NeighborhoodLike<Inner>> {};

    template<typename T>
    concept PopulationNeighborhoodLike = is_population_neighborhood<T>::value;

    template<
        typename Selection,
        typename Neighborhood,
        typename Solution,
        typename Function
    >
    concept MutationSelectionLike =
        SolutionLike<Solution> &&
        FunctionLike<Function> &&
        PopulationNeighborhoodLike<Neighborhood> &&
        requires(Selection selection, Neighborhood& nh, const std::vector<Solution>& population, const Function& f, int n)
    {
        typename Neighborhood::Mutation;
        typename Neighborhood::BaseMutation;

        requires std::derived_from<
            typename Neighborhood::Mutation,
            PopulationMutation<typename Neighborhood::BaseMutation>
        >;

        { selection.choose(nh, population, f, n) }
            -> std::same_as<std::vector<typename Neighborhood::Mutation>>;
    };

} // namespace AdaptiveOA

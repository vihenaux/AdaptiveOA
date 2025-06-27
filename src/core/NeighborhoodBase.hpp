#pragma once

#include <concepts>
#include <string>
#include "MutationBase.hpp"

namespace AdaptiveOA
{

    template<typename T>
    concept NeighborhoodLike = requires(T n)
    {
        typename T::Solution;
        typename T::Mutation;

        requires SolutionLike<typename T::Solution>
        requires MutationLike<typename T::Mutation>;

        { n.do_mutation_available() } -> std::same_as<bool>;
        { n.do_next_mutation() } -> std::same_as<typename T::Mutation>;
        { n.do_accept_mutation(std::declval<const typename T::Mutation&>()) } -> std::same_as<void>;
    };

    // ---------------------------
    // CRTP Neighborhood Base Class (CRTP)
    // ---------------------------
    template<typename Derived>
    class NeighborhoodBase
    {
        static_assert(NeighborhoodLike<Derived>,
            "Derived class does not satisfy NeighborhoodLike concept.");

        public:
        using Solution  = typename Derived::Solution;
        using Mutation  = typename Derived::Mutation;

        bool mutation_available() const
        {
            return static_cast<Derived*>(this)->do_mutation_available();
        }

        Mutation next_mutation()
        {
            return static_cast<Derived*>(this)->do_next_mutation();
        }

        void accept_mutation(const Mutation& mutation)
        {
            static_cast<Derived*>(this)->do_accept_mutation(mutation);
        }
    };

} // namespace AdaptiveOA

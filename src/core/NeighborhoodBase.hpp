#pragma once

#include <concepts>
#include <string>
#include "MutationBase.hpp"

namespace AdaptiveOA
{

    template<typename T>
    concept NeighborhoodLike = requires(T n)
    {
        typename T::Mutation;
        { n.mutation_available() } -> std::same_as<bool>;
        { n.next_mutation() } -> std::same_as<typename T::Mutation>;
        { n.accept_mutation(std::declval<const typename T::Mutation&>()) } -> std::same_as<void>;
    };

    // ---------------------------
    // CRTP Neighborhood Base Class (CRTP)
    // ---------------------------
    template<typename Derived, MutationLike MutationT>
    class NeighborhoodBase
    {
        public:

        using Mutation = MutationT;

        bool mutation_available() const
        {
            return static_cast<const Derived*>(this)->do_mutation_available();
        }

        Mutation next_mutation()
        {
            return static_cast<Derived*>(this)->do_next_mutation();
        }

        void accept_mutation(const Mutation& mutation)
        {
            static_cast<Derived*>(this)->do_accept_mutation(mutation);
        }

        void reset()
        {
            static_cast<Derived*>(this)->do_reset();
        }
    };

} // namespace AdaptiveOA

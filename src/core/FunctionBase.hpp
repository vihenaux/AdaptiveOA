#pragma once

#include <concepts>
#include <cstdint>
#include "SolutionBase.hpp"
#include "MutationBase.hpp"

namespace AdaptiveOA
{

    // ---------------------------
    // Score Type
    // ---------------------------
    using Score = uint64_t;

    template<typename F>
    concept FunctionLike = requires(const F f)
    {
        typename F::Solution;

        requires SolutionLike<typename F::Solution>;

        { f.evaluate(std::declval<const typename F::Solution&>()) } -> std::convertible_to<Score>;
    };

    // ---------------------------
    // CRTP Base Class : Function
    // ---------------------------
    template<typename Derived>
    class FunctionBase
    {
        public:
        using Solution = typename Derived::Solution;

        Score operator()(const Solution& sol) const
        {
            ++m_nb_evaluations;
            return static_cast<Derived*>(this)->evaluate(sol);
        }

        template<MutationLike Mutation>
        Score operator()(const Solution& sol, const Mutation& mutation) const
        {
            ++m_nb_evaluations;
            return static_cast<Derived*>(this)->evaluate(sol, mutation);
        }

        std::size_t get_nb_evaluations() const { return m_nb_evaluations; }

        protected:

        // Default incremental evaluation
        template<MutationLike Mutation>
        Score evaluate(const Solution& sol, const Mutation& mutation) const
        {
            sol.mutate(mutation);
            Score score = (*this)(sol);
            sol.reverse_last_mutation(mutation);
            return score;
        }

        private:

        mutable std::size_t m_nb_evaluations = 0;
    };

} // namespace AdaptiveOA

#pragma once

#include <concepts>
#include <cstdint>
#include "SolutionBase.hpp"
#include "MutationBase.hpp"

namespace AdaptiveOA {

    // ---------------------------
    // Score Type
    // ---------------------------
    using Score = uint64_t;

    template<typename F>
    concept FunctionLike = requires(F f, typename F::Solution& sol, const typename F::Solution& const_sol)
    {
        typename F::Solution;

        requires SolutionLike<typename F::Solution>;

        { f.evaluate(sol) } -> std::convertible_to<Score>;
    };

    // ---------------------------
    // CRTP Base Class : Function
    // ---------------------------

    template<typename Derived>
    class FunctionBase {
        public:
        using Solution = typename Derived::Solution;

        Score operator()(const Solution& sol)
        {
            ++m_nb_evaluations;
            return static_cast<Derived*>(this)->evaluate(sol);
        }

        template<MutationLike Mutation>
        Score operator()(const Solution& sol, const Mutation& mutation)
        {
            ++m_nb_evaluations;
            return static_cast<Derived*>(this)->evaluate(sol, mutation);
        }

        std::size_t get_nb_evaluations() const { return m_nb_evaluations; }

        private:

        // Default incremental evaluation
        template<MutationLike Mutation>
        Score evaluate(const Solution& sol, const Mutation& mutation)
        {
            sol.mutate(mutation);
            Score score = (*this)(sol);
            sol.reverse_last_mutation(mutation);
            return score;
        }

        std::size_t m_nb_evaluations = 0;
    };

} // namespace AdaptiveOA

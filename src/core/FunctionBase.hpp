#pragma once

#include <concepts>
#include <cstdint>
#include "Score.hpp"
#include "SolutionBase.hpp"
#include "MutationBase.hpp"

namespace AdaptiveOA
{

    template<typename F>
    concept FunctionLike = requires(const F f)
    {
        typename F::Solution;

        { f(std::declval<const typename F::Solution&>()) } -> std::convertible_to<Score>;
        { f.get_nb_evaluations() } -> std::same_as<std::size_t>;
    };

    // ---------------------------
    // CRTP Base Class : Function
    // ---------------------------
    template<typename Derived, SolutionLike SolutionT>
    class FunctionBase
    {
        public:

        using Solution = SolutionT;

        Score operator()(const Solution& sol) const
        {
            ++m_nb_evaluations;
            Score evaluation = static_cast<const Derived*>(this)->evaluate(sol);
            sol.set_score(evaluation);
            return evaluation;
        }

        template<MutationLike Mutation>
        Score operator()(const Solution& sol, const Mutation& mutation) const
        {
            ++m_nb_evaluations;
            Score evaluation = static_cast<const Derived*>(this)->evaluate(sol, mutation);
            mutation.set_score(evaluation);
            return evaluation;
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

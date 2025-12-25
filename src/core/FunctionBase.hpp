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
        { f.reset() } -> std::same_as<void>;
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
            // TODO: static assert for evaluate(sol,mut) in derived, if not print message asking for at least default implementation eg:
            // return FunctionBase<NK, BitString>::evaluate(sol, mutation);
            ++m_nb_evaluations;
            Score evaluation = static_cast<const Derived*>(this)->evaluate(sol, mutation);
            mutation.set_score(evaluation);
            return evaluation;
        }

        Solution create_random_solution() const
        {
            return static_cast<const Derived*>(this)->do_create_random_solution();
        }

        std::size_t get_nb_evaluations() const { return m_nb_evaluations; }
        void reset() const
        {
            m_nb_evaluations = 0;
        }

        protected:

        // Default incremental evaluation
        template<MutationLike Mutation>
        Score evaluate(const Solution& sol, const Mutation& mutation) const
        {
            const_cast<Solution&>(sol).mutate(mutation);
            Score score = (*this)(sol);
            const_cast<Solution&>(sol).reverse_last_mutation(mutation);
            return score;
        }

        private:

        mutable std::size_t m_nb_evaluations = 0;
    };

} // namespace AdaptiveOA

#pragma once

#include <concepts>
#include <cstdint>
#include "Score.hpp"
#include "SolutionBase.hpp"
#include "MutationBase.hpp"

namespace AdaptiveOA
{

    template<typename F, typename S>
    concept FunctionLike =
            SolutionLike<S> &&
            requires(const F f, const S& s)
    {
        { f.evaluate(s) } -> std::convertible_to<Score>;
    };

    // ---------------------------
    // CRTP Base Class : Function
    // ---------------------------
    template<typename Derived, SolutionLike Solution>
    class FunctionBase
    {
        public:

        FunctionBase()
        {
            static_assert(FunctionLike<Derived, Solution>,
                "Derived class does not satisfy FunctionLike concept.");
        }

        Score operator()(const Solution& sol) const
        {
            ++m_nb_evaluations;
            Score evaluation = static_cast<Derived*>(this)->evaluate(sol);
            sol.set_score(evaluation);
            return evaluation;
        }

        template<MutationLike Mutation>
        Score operator()(const Solution& sol, const Mutation& mutation) const
        {
            ++m_nb_evaluations;
            Score evaluation = static_cast<Derived*>(this)->evaluate(sol, mutation);
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

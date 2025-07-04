#pragma once

#include <optional>
#include <concepts>
#include "SolutionBase.hpp"
#include "FunctionBase.hpp"

namespace AdaptiveOA
{

    template<typename A>
    concept AlgorithmLike = requires(A algo)
    {
        // Not necessary to define these in CRTP derived class, the base class already defines them by default
        typename A::Solution;
        typename A::Function;

        { algo.do_run(std::declval<typename A::Solution&>(), std::declval<const typename A::Function&>()) } -> std::same_as<void>;
    };


    // ---------------------------
    // CRTP Base Class : Algorithm
    // ---------------------------
    template<
        typename Derived,
        SolutionLike SolutionT,
        typename FunctionT
    >
    requires FunctionLike<FunctionT, SolutionT>
    class AlgorithmBase
    {
        public:

        using Solution = SolutionT;
        using Function = FunctionT;

        AlgorithmBase()
        {
            static_assert(AlgorithmLike<Derived>,
                "Derived class does not satisfy AlgorithmLike concept.");
        }

        void run(Solution& start, const Function& fitness_function) {
            static_cast<Derived*>(this)->do_run(start, fitness_function);
        }

        const Solution& best_solution() const {
            return m_best_solution;
        }

        std::optional<Score> best_score() const {
            return m_best_score;
        }

        protected:

        void set_best_solution(const Solution& sol, Score score) {
            m_best_solution = sol;
            m_best_score = score;
        }

        void set_best_solution(Solution&& sol, Score score) {
            m_best_solution = std::move(sol);
            m_best_score = score;
        }

        private:

        std::optional<Score> m_best_score = 0;
        Solution m_best_solution;
    };

} // namespace AdaptiveOA

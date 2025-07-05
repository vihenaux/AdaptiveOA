#pragma once

#include <optional>
#include <concepts>
#include "SolutionBase.hpp"
#include "FunctionBase.hpp"

namespace AdaptiveOA
{

    template<typename A>
    concept AlgorithmLike = requires(A algo, const A& const_algo)
    {
        typename A::Solution;
        typename A::Function;

        { algo.run(std::declval<typename A::Solution&>(), std::declval<const typename A::Function&>()) } -> std::same_as<void>;
        { const_algo.best_solution() } -> std::convertible_to<typename A::Solution>;
        { const_algo.best_score() } -> std::same_as<std::optional<Score>>;
    };


    // ---------------------------
    // CRTP Base Class : Algorithm
    // ---------------------------
    template<
        typename Derived,
        SolutionLike SolutionT,
        FunctionLike FunctionT
    >
    class AlgorithmBase
    {
        public:

        using Solution = SolutionT;
        using Function = FunctionT;

        void run(Solution& start, const Function& fitness_function) {
            static_cast<Derived*>(this)->do_run(start, fitness_function);
        }

        const Solution& best_solution() const {
            return *m_best_solution;
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
        std::optional<Solution> m_best_solution;
    };

} // namespace AdaptiveOA

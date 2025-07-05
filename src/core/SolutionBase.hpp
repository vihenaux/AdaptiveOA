#pragma once

#include <string>
#include <concepts>
#include <optional>
#include "MutationBase.hpp"
#include "Score.hpp"

namespace AdaptiveOA
{

    template<typename S>
    concept SolutionLike = requires(S sol, const S const_sol, Score score)
    {
        { sol.randomize() } -> std::same_as<void>;
        { const_sol.to_string() } -> std::convertible_to<std::string>;
        { sol.set_score(score) } -> std::same_as<void>;
        { sol.get_score() } -> std::same_as<std::optional<Score>>;
        { sol.invalidate_score() } -> std::same_as<void>;
    };

    // ---------------------------
    // CRTP Base Class: Solution
    // ---------------------------
    template<typename Derived>
    class SolutionBase
    {
        public:

        void randomize()
        {
            invalidate_score();
            static_cast<Derived*>(this)->do_randomize();
        }

        template<MutationLike Mutation>
        void mutate(const Mutation& mutation)
        {
            m_score_save.swap(m_score);
            m_score = mutation.get_score();

            static_cast<Derived*>(this)->do_mutate(mutation);
        }

        template<MutationLike Mutation>
        void reverse_last_mutation(const Mutation& mutation)
        {
            m_score.swap(m_score_save);

            static_cast<Derived*>(this)->do_reverse_mutation(mutation);
        }

        void set_score(Score s) const { m_score = s; }
        std::optional<Score> get_score() const { return m_score; }
        void invalidate_score() const
        {
            m_score.reset();
            m_score_save.reset();
        }

        std::string to_string() const
        {
            return static_cast<const Derived*>(this)->do_to_string();
        }

        private:

        mutable std::optional<Score> m_score;
        mutable std::optional<Score> m_score_save;
    };

} // namespace AdaptiveOA

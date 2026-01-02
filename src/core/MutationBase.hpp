#pragma once

#include <optional>
#include <string>
#include <concepts>
#include "Score.hpp"

namespace AdaptiveOA
{

    template<typename Mutation>
    concept MutationLike = requires(Mutation m, Score score)
    {
        { m.to_string() } -> std::convertible_to<std::string>;
        { m.set_score(score) } -> std::same_as<void>;
        { m.get_score() } -> std::same_as<std::optional<Score>>;
    };


    // ---------------------------
    // CRTP Mutation Base Class (CRTP)
    // ---------------------------
    template<typename Derived>
    class MutationBase
    {
        public:

        MutationBase() = default;
        explicit MutationBase(bool neutral_mutation) : m_neutral_mutation(neutral_mutation) {}

        void set_score(Score s) const
        {
            m_score = s;
        }

        std::optional<Score> get_score() const
        {
            return m_score;
        }

        std::string to_string() const
        {
            return static_cast<const Derived*>(this)->do_to_string();
        }

        bool is_neutral() const
        {
            return m_neutral_mutation;
        }

        private:

        mutable std::optional<Score> m_score{std::nullopt};
        bool m_neutral_mutation{false};
        char padding[7];
    };

} // namespace AdaptiveOA

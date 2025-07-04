#pragma once

#include <optional>
#include <string>
#include <concepts>
#include "Score.hpp"

namespace AdaptiveOA
{

    template<typename Mutation>
    concept MutationLike = requires( Mutation m)
    {
        { m.do_to_string() } -> std::convertible_to<std::string>;
    };


    // ---------------------------
    // CRTP Mutation Base Class (CRTP)
    // ---------------------------
    template<typename Derived>
    class MutationBase
    {
        public:

        MutationBase()
        {
            static_assert(MutationLike<Derived>,
                "Derived class does not satisfy MutationLike concept.");
        }

        void set_score(Score s) { m_score = s; }
        std::optional<Score> get_score() const { return m_score; }

        std::string to_string() const
        {
            return static_cast<const Derived*>(this)->do_to_string();
        }

        private:

        std::optional<Score> m_score;
    };

} // namespace AdaptiveOA

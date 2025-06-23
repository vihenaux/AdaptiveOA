#pragma once

#include <string>
#include <concepts>

namespace AdaptiveOA {

    // ----------------------------------
    // Concept: Static interface contract
    // ----------------------------------
    template<typename T>
    concept SolutionLike = requires(const T& sol) {
        { sol.do_randomize() } -> std::same_as<void>;
        { sol.do_to_string() } -> std::convertible_to<std::string>;
    };

    // ---------------------------
    // CRTP Base Class: Solution
    // ---------------------------
    template<typename Derived>
    class SolutionBase
    {
        static_assert(SolutionLike<Derived>,
        "Solution type class does not satisfy SolutionLike concept. "
        "It must implement: do_randomize(), do_to_string(), "
        "and template methods do_mutate(Mutation), do_reverse_mutation(Mutation).");

        public:

        void randomize() {
            static_cast<Derived*>(this)->do_randomize();
        }

        template<typename Mutation>
        void mutate(const Mutation& mutation) {
            static_assert(requires(Derived& d) { d.do_mutate(mutation); },
            "Derived class does not implement do_mutate(Mutation).");
            static_cast<Derived*>(this)->do_mutate(mutation);
        }

        template<typename Mutation>
        void reverse_last_mutation(const Mutation& mutation) {
            static_assert(requires(Derived& d) { d.do_reverse_mutation(mutation); },
            "Derived class does not implement do_reverse_mutation(Mutation).");
            static_cast<Derived*>(this)->do_reverse_mutation(mutation);
        }

        std::string to_string() const {
            return static_cast<const Derived*>(this)->do_to_string();
        }
    };

} // namespace AdaptiveOA

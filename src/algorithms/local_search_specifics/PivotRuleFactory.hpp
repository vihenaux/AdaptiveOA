#pragma once

#include <type_traits>

namespace AdaptiveOA {

    class PivotRuleFactory
    {
        public:

        template<typename PivotRule>
        static PivotRule create() {
            static_assert(std::is_default_constructible_v<PivotRule>,
                          "This pivot rule requires a custom factory specialization.");
            return PivotRule{};
        }
    };

} // namespace AdaptiveOA

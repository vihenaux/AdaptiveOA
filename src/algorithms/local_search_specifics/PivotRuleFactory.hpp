#pragma once

#include <type_traits>
#include "PivotRuleBase.hpp"

namespace AdaptiveOA
{

    class PivotRuleFactory
    {
        public:

        template<typename PivotRule, typename Neighborhood, typename Solution, typename Function>
        requires PivotRuleLike<PivotRule, Neighborhood, Solution, Function>
        static PivotRule create()
        {
            static_assert(std::is_default_constructible_v<PivotRule>,
                          "This pivot rule requires a custom factory specialization.");
            return PivotRule{};
        }
    };

} // namespace AdaptiveOA

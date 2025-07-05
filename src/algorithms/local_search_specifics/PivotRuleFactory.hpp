#pragma once

#include "../../core/NeighborhoodBase.hpp"
#include "../../core/SolutionBase.hpp"
#include "../../core/FunctionBase.hpp"
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
            return PivotRule{};
        }
    };

} // namespace AdaptiveOA

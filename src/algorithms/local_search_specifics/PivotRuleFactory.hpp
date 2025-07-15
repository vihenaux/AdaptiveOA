#pragma once

#include "../../core/NeighborhoodBase.hpp"
#include "../../core/SolutionBase.hpp"
#include "../../core/FunctionBase.hpp"
#include "PivotRuleBase.hpp"
#include "../../utils/FastCLI.hpp"
#include "pivot_rules/Tabu.hpp"
#include <string>

namespace AdaptiveOA
{

    template<typename PivotRule, typename Neighborhood, typename Solution, typename Function>
    requires PivotRuleLike<PivotRule, Neighborhood, Solution, Function>
    class PivotRuleFactory
    {
        public:

        static PivotRule create()
        {
            return PivotRule{};
        }
    };

    template<typename Neighborhood, typename Solution, typename Function>
    requires PivotRuleLike<Tabu<Neighborhood>, Neighborhood, Solution, Function>
    class PivotRuleFactory<Tabu<Neighborhood>, Neighborhood, Solution, Function>
    {
        public:

        static Tabu<Neighborhood> create()
        {
            return Tabu<Neighborhood>(fast_cli().get_tabu_list_max_size());
        }

        private:
    };

} // namespace AdaptiveOA

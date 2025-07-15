#pragma once

#include "../../core/NeighborhoodBase.hpp"
#include "../../core/SolutionBase.hpp"
#include "../../core/FunctionBase.hpp"
#include "PivotRuleBase.hpp"
#include "../../utils/CLI.hpp"
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
            //if(!s_tabu_size)
            //    s_tabu_size = static_cast<unsigned int>(std::stoi(std::string(CLI::get_option_value(CLI::Option::tabu_size))));
            //return Tabu<Neighborhood>(*s_tabu_size);
            return Tabu<Neighborhood>(static_cast<unsigned int>(std::stoi(std::string(CLI::get_option_value(CLI::Option::tabu_size)))));
        }

        private:

        //static std::optional<unsigned int> s_tabu_size;
    };

} // namespace AdaptiveOA

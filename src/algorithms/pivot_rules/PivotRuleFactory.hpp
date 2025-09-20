#pragma once

#include "PivotRuleBase.hpp"
#include "../../utils/FastCLI.hpp"
#include "impl/Tabu.hpp"
#include "impl/SimulatedAnnealing.hpp"

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

    template<typename Neighborhood, typename Solution, typename Function>
    requires PivotRuleLike<SimulatedAnnealing, Neighborhood, Solution, Function>
    class PivotRuleFactory<SimulatedAnnealing, Neighborhood, Solution, Function>
    {
    public:

        static SimulatedAnnealing create()
        {
            return SimulatedAnnealing(fast_cli().get_simulated_annealing_starting_temperature(), fast_cli().get_simulated_annealing_decay(), fast_cli().get_mutation_limit());
        }

    private:
    };

} // namespace AdaptiveOA

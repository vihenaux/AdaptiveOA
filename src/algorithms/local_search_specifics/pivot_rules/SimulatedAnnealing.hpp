#pragma once

#include <cassert>
#include <optional>
#include <cmath>
#include "../PivotRuleBase.hpp"
#include "../../../core/NeighborhoodBase.hpp"
#include "../../../core/MutationBase.hpp"
#include "../../../core/SolutionBase.hpp"
#include "../../../core/FunctionBase.hpp"
#include "../../../utils/Random.hpp"

namespace AdaptiveOA
{

    class SimulatedAnnealing
    {
        public:

        SimulatedAnnealing() = delete;
        SimulatedAnnealing(double initial_temperature, double decay, std::size_t max_mutation_per_iteration) : m_temperature(initial_temperature), m_decay(decay), m_max_mutation_per_iteration(max_mutation_per_iteration)
        {
            assert((m_decay > 0. && m_decay < 1.) && "Decay should be between 0 and 1");
        }

        template<
                NeighborhoodLike Neighborhood,
                SolutionLike Solution,
                FunctionLike Function
        >
        std::optional<typename Neighborhood::Mutation> choose(Neighborhood& nh, Solution& sol, const Function& f)
        {
            Score current_score = sol.get_score().value_or(f(sol));

            std::size_t i = 0;
            while(nh.mutation_available() && (i++ < m_max_mutation_per_iteration))
            {
                auto mutation = nh.next_mutation();
                nh.reset();
                Score new_score = f(sol, mutation);

                if(new_score >= current_score)
                {
                    m_temperature *= m_decay;
                    return mutation;
                }

                double delta = static_cast<double>(current_score - new_score);
                double probability = std::exp(-delta / m_temperature);
                m_temperature *= m_decay;

                if(Random::get_bool(probability))
                    return mutation;
            }

            return std::nullopt;
        }

        private:

        double m_temperature;
        double m_decay;
        std::size_t m_max_mutation_per_iteration;
    };

} // namespace AdaptiveOA

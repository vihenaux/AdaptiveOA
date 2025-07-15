#pragma once

#include <optional>
#include <vector>
#include "../PivotRuleBase.hpp"
#include "../../../core/NeighborhoodBase.hpp"
#include "../../../core/MutationBase.hpp"
#include "../../../core/SolutionBase.hpp"
#include "../../../core/FunctionBase.hpp"

namespace AdaptiveOA
{

    template<NeighborhoodLike Neighborhood>
    class Tabu
    {
        public:

        Tabu() = delete;
        Tabu(unsigned int tabu_list_max_size) : m_tabu_list_max_size(tabu_list_max_size) {}

        template<SolutionLike Solution, FunctionLike Function>
        std::optional<typename Neighborhood::Mutation> choose(Neighborhood& nh, Solution& sol, const Function& f)
        {
            Score current_score = sol.get_score().value_or(f(sol));

            std::optional<typename Neighborhood::Mutation> best_mutation;

            unsigned int test1 = 0;
            unsigned int test3 = 0;
            unsigned int test4 = 0;
            while(nh.mutation_available())
            {
                test1++;
                auto mutation = nh.next_mutation();
                if(this->is_tabu(mutation))
                    continue;

                Score new_score = f(sol, mutation);

                if(new_score > current_score)
                {
                    this->add_tabu(mutation);
                    return mutation;
                }

                test3++;

                if((best_mutation && best_mutation.value().get_score() < new_score) || !best_mutation)
                {
                    test4++;
                    best_mutation = std::move(mutation);
                }
            }

            if(!best_mutation)
                std::cout << test1 << " " << test3 << " " << test4 << std::endl;

            this->add_tabu(*best_mutation);
            return best_mutation;
        }

        private:

        bool is_tabu(const typename Neighborhood::Mutation& mutation) const
        {
            for(unsigned int i(0); i < m_tabu.size(); ++i)
            {
                if(m_tabu[i] == mutation)
                {
                    return true;
                }
            }
            return false;
        }

        void add_tabu(const typename Neighborhood::Mutation& mutation)
        {
            if(m_tabu.size() < m_tabu_list_max_size)
            {
                m_tabu.push_back(mutation);
                m_vector_cursor++;
                return;
            }
            m_tabu[m_vector_cursor] = mutation;
            m_vector_cursor = (m_vector_cursor+1)%m_tabu_list_max_size;
        }

        unsigned int m_tabu_list_max_size;
        unsigned int m_vector_cursor{0};
        std::vector<typename Neighborhood::Mutation> m_tabu;
    };

} // namespace AdaptiveOA

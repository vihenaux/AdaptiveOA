#pragma once

#include "../core/MutationBase.hpp"

namespace AdaptiveOA
{

    template<MutationLike Mutation>
    class PopulationMutation : public Mutation
    {
        public:

        PopulationMutation() = delete;
        PopulationMutation(const Mutation& m) : Mutation(m) {}
        PopulationMutation(Mutation&& m) : Mutation(std::move(m)) {}

        void set_solution_id(std::size_t solution_id)
        {
            m_solution_id = solution_id;
        }

        std::size_t get_solution_id() const
        {
            return m_solution_id;
        }

        bool operator==(const PopulationMutation<Mutation>& mutation) const
        {
            return m_solution_id == mutation.m_solution_id && static_cast<const Mutation&>(*this) == static_cast<const Mutation&>(mutation);
        }

        private:

        std::size_t m_solution_id{0};
    };

}

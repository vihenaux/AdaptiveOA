#pragma once

#include <algorithm>
#include <vector>
#include "../core/NeighborhoodBase.hpp"
#include "../mutations/PopulationMutation.hpp"

namespace AdaptiveOA
{

    template<NeighborhoodLike Neighborhood>
    class PopulationMutationNeighborhood : public NeighborhoodBase<PopulationMutationNeighborhood<Neighborhood>, PopulationMutation<typename Neighborhood::Mutation>>
    {
        public:

        PopulationMutationNeighborhood() = delete;
        PopulationMutationNeighborhood(const Neighborhood& neighborhood) : m_neighborhood(neighborhood) {}
        PopulationMutationNeighborhood(Neighborhood&& neighborhood) : m_neighborhood(std::move(neighborhood)) {}

        friend NeighborhoodBase<PopulationMutationNeighborhood<Neighborhood>, PopulationMutation<typename Neighborhood::Mutation>>;

        private:

        Neighborhood m_neighborhood;

        bool do_mutation_available() const
        {
            return m_neighborhood.mutation_available();
        }

        PopulationMutation<typename Neighborhood::Mutation> do_next_mutation()
        {
            return PopulationMutation<typename Neighborhood::Mutation>{std::move(m_neighborhood.next_mutation())};
        }

        void do_accept_mutation(const PopulationMutation<typename Neighborhood::Mutation>& m)
        {
            m_neighborhood.accept_mutation(m);
        }

        void do_reset()
        {
            m_neighborhood.reset();
        }
    };


} // namespace AdaptiveOA

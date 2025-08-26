#pragma once

#include "../core/NeighborhoodBase.hpp"
#include "../mutations/SpecificSeedMutation.hpp"
#include "../utils/Random.hpp"

namespace AdaptiveOA
{

    class NKModel;

    template<typename T>
    class SpecificSeedNeighborhood : public NeighborhoodBase<SpecificSeedNeighborhood<T>, SpecificSeedMutation<T>>
    {
        public:

        friend NeighborhoodBase<SpecificSeedNeighborhood<T>, SpecificSeedMutation<T>>;

        private:

        bool do_mutation_available() const
        {
            return true;
        }

        SpecificSeedMutation<T> do_next_mutation()
        {
            return SpecificSeedMutation<T>{ Random::get_uint() };
        }

        void do_accept_mutation(const SpecificSeedMutation<T>&) const {}

        void do_reset() const {}
    };

    template<>
    class SpecificSeedNeighborhood<NKModel> : public NeighborhoodBase<SpecificSeedNeighborhood<NKModel>, SpecificSeedMutation<NKModel>>
    {
        public:

        friend NeighborhoodBase<SpecificSeedNeighborhood<NKModel>, SpecificSeedMutation<NKModel>>;

        private:

        bool do_mutation_available() const
        {
            return true;
        }

        SpecificSeedMutation<NKModel> do_next_mutation()
        {
            return SpecificSeedMutation<NKModel>{ Random::get_uint() , Random::get_fast_binomial_distribution(m_last_matrix_mutation) , Random::get_fast_binomial_distribution(m_last_links_mutation) };
        }

        void do_accept_mutation(const SpecificSeedMutation<NKModel>& m)
        {
            m_last_matrix_mutation = (m.get_nb_matrix_mutated() == 0) ? 1 : m.get_nb_matrix_mutated();
            m_last_links_mutation = (m.get_nb_links_mutated() == 0) ? 1 : m.get_nb_links_mutated();
        }

        void do_reset()
        {
            m_last_matrix_mutation = 1;
            m_last_links_mutation = 1;
        }

        unsigned int m_last_matrix_mutation{1};
        unsigned int m_last_links_mutation{1};
    };

} // namespace AdaptiveOA

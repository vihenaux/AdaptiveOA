#pragma once

#include "SeedMutation.hpp"

namespace AdaptiveOA
{

    class NKModel;

    template<typename T>
    class SpecificSeedMutation : public SeedMutation
    {
        public:

        SpecificSeedMutation() = delete;
        SpecificSeedMutation(unsigned int seed) : SeedMutation(seed) {}

        bool operator==(const SpecificSeedMutation<T>& mutation) const
        {
            return SeedMutation::operator==(mutation);
        }
    };

    template<>
    class SpecificSeedMutation<NKModel> : public SeedMutation
    {
        public:

        SpecificSeedMutation() = delete;
        SpecificSeedMutation(unsigned int seed, unsigned int nb_matrix_mutated, unsigned int nb_links_mutated) : SeedMutation(seed), m_nb_matrix_mutated(nb_matrix_mutated), m_nb_links_mutated(nb_links_mutated) {}

        unsigned int get_nb_matrix_mutated() const
        {
            return m_nb_matrix_mutated;
        }

        unsigned int get_nb_links_mutated() const
        {
            return m_nb_links_mutated;
        }

        bool operator==(const SpecificSeedMutation<NKModel>& mutation) const
        {
            return SeedMutation::operator==(mutation);
        }

        private:

        unsigned int m_nb_matrix_mutated;
        unsigned int m_nb_links_mutated;
    };

}

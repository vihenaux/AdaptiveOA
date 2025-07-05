#pragma once

#include <algorithm>
#include <vector>
#include "../core/NeighborhoodBase.hpp"
#include "../solutions/BitString.hpp"
#include "../mutations/BitFlip.hpp"

namespace AdaptiveOA
{

    class BitFlipNeighborhood : public NeighborhoodBase<BitFlipNeighborhood, BitFlip>
    {
        public:

        using Solution = BitString;
        using Mutation = BitFlip;

        BitFlipNeighborhood() = delete;
        BitFlipNeighborhood(std::size_t bit_string_size) : m_neighbors(bit_string_size)
        {
            for(std::size_t i(0); i < bit_string_size; ++i)
            {
                m_neighbors[i] = i;
            }
        }

        friend NeighborhoodBase<BitFlipNeighborhood, BitFlip>;

        private:

        std::size_t m_current_neighbor = 0;
        std::vector<std::size_t> m_neighbors;

        bool do_mutation_available() const
        {
            return m_current_neighbor < m_neighbors.size();
        }

        Mutation do_next_mutation()
        {
            std::size_t neighbor_index = Random::get_uint_range(m_current_neighbor, m_neighbors.size()-1);
            std::swap(m_neighbors[m_current_neighbor], m_neighbors[neighbor_index]);
            return BitFlip{ m_neighbors[m_current_neighbor++] };
        }

        void do_accept_mutation(const Mutation&)
        {
            m_current_neighbor = 0;
        }
    };


} // namespace AdaptiveOA

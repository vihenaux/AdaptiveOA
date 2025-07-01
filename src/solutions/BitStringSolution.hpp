#pragma once

#include <vector>
#include <string>
#include <random>
#include <sstream>
#include "SolutionBase.hpp"
#include "MutationBase.hpp"
#include "Random.hpp"

namespace AdaptiveOA
{

    class BitStringSolution : public SolutionBase<BitStringSolution>
    {
        public:

        BitStringSolution(std::size_t size) : m_bits(size)
        {
            randomize();
        }

        std::size_t size() const
        {
            return m_bits.size();
        }

        int operator[](std::size_t index) const
        {
            return m_bits[index];
        }

        friend SolutionBase<BitStringSolution>;

        private:

        std::vector<bool> m_bits;

        void do_randomize()
        {
            for (auto& bit : m_bits)
            {
                bit = Random::random_bool();
            }
        }

        std::string do_to_string() const
        {
            std::ostringstream oss;
            for (bool bit : m_bits)
            {
                oss << (bit ? '1' : '0');
            }
            return oss.str();
        }
    };

} // namespace AdaptiveOA

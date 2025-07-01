#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "../core/SolutionBase.hpp"
#include "../utils/Random.hpp"
#include "../mutations/BitFlip.hpp"

namespace AdaptiveOA
{

    class BitString : public SolutionBase<BitString>
    {
        public:

        BitString(std::size_t size) : m_bits(size)
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

        friend SolutionBase<BitString>;

        private:

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

        void do_mutate(const BitFlip& bitflip)
        {
            m_bits[bitflip.get_bit()] = !m_bits[bitflip.get_bit()];
        }

        void do_reverse_mutation(const BitFlip& bitflip)
        {
            m_bits[bitflip.get_bit()] = !m_bits[bitflip.get_bit()];
        }

        std::vector<bool> m_bits;
    };

} // namespace AdaptiveOA

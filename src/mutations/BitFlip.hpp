#pragma once

#include "../core/MutationBase.hpp"

namespace AdaptiveOA
{
    class BitFlip : public MutationBase<BitFlip>
    {
        public:

        BitFlip() = delete;
        BitFlip(std::size_t bit) : m_bit(bit) {}

        std::size_t get_bit() const
        {
            return m_bit;
        }

        private:

        std::string do_to_string() const
        {
            std::ostringstream oss;
            oss << m_bit;
            return oss.str();
        }

        std::size_t m_bit;
    };

}

#pragma once

#include <sstream>
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


        std::string do_to_string() const
        {
            std::ostringstream oss;
            oss << m_bit;
            return oss.str();
        }

        private:


        std::size_t m_bit;
    };

}

#pragma once

#include <sstream>
#include "../core/MutationBase.hpp"

namespace AdaptiveOA
{

    class SeedMutation : public MutationBase<SeedMutation>
    {
        public:

        SeedMutation() = delete;
        SeedMutation(std::size_t seed) : m_seed(seed) {}

        std::size_t get_seed() const
        {
            return m_seed;
        }

        std::string do_to_string() const
        {
            std::ostringstream oss;
            oss << m_seed;
            return oss.str();
        }

        bool operator==(const BitFlip& mutation) const
        {
            return m_seed == mutation.m_seed;
        }

        private:


        std::size_t m_seed;
    };

}

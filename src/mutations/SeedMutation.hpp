#pragma once

#include <sstream>
#include "../core/MutationBase.hpp"

namespace AdaptiveOA
{

    class SeedMutation : public MutationBase<SeedMutation>
    {
        public:

        SeedMutation() = delete;
        SeedMutation(unsigned int seed) : m_seed(seed) {}

        unsigned int get_seed() const
        {
            return m_seed;
        }

        std::string do_to_string() const
        {
            std::ostringstream oss;
            oss << m_seed;
            return oss.str();
        }

        bool operator==(const SeedMutation& mutation) const
        {
            return m_seed == mutation.m_seed;
        }

        private:

        unsigned int m_seed;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
        unsigned int padding{0};
#pragma clang diagnostic pop
    };

}

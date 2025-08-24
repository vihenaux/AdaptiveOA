#pragma once

#include "SeedMutation.hpp"

namespace AdaptiveOA
{

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

}

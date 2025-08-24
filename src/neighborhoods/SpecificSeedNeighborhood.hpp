#pragma once

#include "../core/NeighborhoodBase.hpp"
#include "../mutations/SeedMutation.hpp"
#include "../utils/Random.hpp"

namespace AdaptiveOA
{

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


} // namespace AdaptiveOA

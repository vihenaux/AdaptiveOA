#pragma once

#include "../core/NeighborhoodBase.hpp"
#include "../mutations/SeedMutation.hpp"
#include "../utils/Random.hpp"

namespace AdaptiveOA
{

    class SeedNeighborhood : public NeighborhoodBase<SeedNeighborhood, SeedMutation>
    {
        public:

        friend NeighborhoodBase<SeedNeighborhood, SeedMutation>;

        private:

        bool do_mutation_available() const
        {
            return true;
        }

        SeedMutation do_next_mutation()
        {
            return SeedMutation{ Random::get_uint() };
        }

        void do_accept_mutation(const SeedMutation&) const {}

        void do_reset() const {}
    };


} // namespace AdaptiveOA

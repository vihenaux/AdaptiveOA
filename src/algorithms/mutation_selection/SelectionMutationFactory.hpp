#pragma once

#include "MutationSelectionBase.hpp"

namespace AdaptiveOA
{

    template<typename MutationSelection, typename Neighborhood, typename Solution, typename Function>
    requires MutationSelectionLike<MutationSelection, Neighborhood, Solution, Function>
    class MutationSelectionFactory
    {
        public:

        static MutationSelection create()
        {
            return MutationSelection{};
        }
    };

} // namespace AdaptiveOA

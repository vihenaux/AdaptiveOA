#pragma once

#include "../TerminateConditionBase.hpp"
#include "../../../core/FunctionBase.hpp"
#include "../../../core/SolutionBase.hpp"

namespace AdaptiveOA
{

    class NoLimit
    {
        public:

        template<FunctionLike Function>
        void update(const Function&) { }

        bool should_terminate() const
        {
            return false;
        }
    };

} // namespace AdaptiveOA

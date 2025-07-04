#pragma once

#include "../TerminateConditionBase.hpp"
#include "../../../core/FunctionBase.hpp"
#include "../../../core/SolutionBase.hpp"

namespace AdaptiveOA
{

    class NoLimit
    {
        public:

        template<typename Function, SolutionLike Solution>
        requires FunctionLike<Function, Solution>
        void update(const Function&) { }

        bool should_terminate() const
        {
            return false;
        }
    };

} // namespace AdaptiveOA

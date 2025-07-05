#pragma once

#include <type_traits>
#include "../../core/FunctionBase.hpp"
#include "TerminateConditionBase.hpp"

namespace AdaptiveOA
{

    class TerminateConditionFactory
    {
        public:

        template<typename TerminateCondition, FunctionLike Function>
        requires TerminateConditionLike<TerminateCondition, Function>
        static TerminateCondition create()
        {
            return TerminateCondition{};
        }
    };

} // namespace AdaptiveOA

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
            static_assert(std::is_default_constructible_v<TerminateCondition>,
                          "This terminate condition requires a custom factory specialization.");
            return TerminateCondition{};
        }
    };

} // namespace AdaptiveOA

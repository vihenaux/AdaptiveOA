#pragma once

#include "../../core/FunctionBase.hpp"
#include "TerminateConditionBase.hpp"
#include "terminate_conditions/IterationLimit.hpp"
#include "terminate_conditions/FunctionCallLimit.hpp"
#include "../../utils/FastCLI.hpp"

namespace AdaptiveOA
{

    template<typename TerminateCondition, FunctionLike Function>
    requires TerminateConditionLike<TerminateCondition, Function>
    class TerminateConditionFactory
    {
        public:

        static TerminateCondition create()
        {
            return TerminateCondition{};
        }
    };

    template<FunctionLike Function>
    requires TerminateConditionLike<IterationLimit, Function>
    class TerminateConditionFactory<IterationLimit, Function>
    {
    public:

        static IterationLimit create()
        {
            return IterationLimit(fast_cli().get_iteration_limit());
        }
    };

    template<FunctionLike Function>
    requires TerminateConditionLike<FunctionCallLimit, Function>
    class TerminateConditionFactory<FunctionCallLimit, Function>
    {
    public:

        static FunctionCallLimit create()
        {
            return FunctionCallLimit(fast_cli().get_iteration_limit());
        }
    };

} // namespace AdaptiveOA

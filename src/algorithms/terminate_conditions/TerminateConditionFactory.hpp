#pragma once

#include "../../core/FunctionBase.hpp"
#include "TerminateConditionBase.hpp"
#include "impl/IterationLimit.hpp"
#include "impl/FunctionCallLimit.hpp"
#include "impl/TimeLimit.hpp"
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
            return FunctionCallLimit(fast_cli().get_function_call_limit());
        }
    };

    template<FunctionLike Function>
    requires TerminateConditionLike<TimeLimit, Function>
    class TerminateConditionFactory<TimeLimit, Function>
    {
    public:

        static TimeLimit create()
        {
            return TimeLimit(fast_cli().get_time_limit());
        }
    };

} // namespace AdaptiveOA

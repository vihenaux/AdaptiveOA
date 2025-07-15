#pragma once

#include "../../core/FunctionBase.hpp"
#include "TerminateConditionBase.hpp"
#include "terminate_conditions/IterationLimit.hpp"
#include "../../utils/CLI.hpp"

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
            return IterationLimit(static_cast<unsigned int>(std::stoi(std::string(CLI::get_option_value(CLI::Option::iteration_limit)))));
        }
    };

} // namespace AdaptiveOA

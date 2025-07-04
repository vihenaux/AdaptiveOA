#pragma once

#include <concepts>
#include "../../core/FunctionBase.hpp"
#include "../../core/SolutionBase.hpp"

namespace AdaptiveOA
{

    template<typename T, typename Function, typename Solution>
    concept TerminateConditionLike =
            SolutionLike<Solution> &&
            FunctionLike<Function, Solution> &&
            requires(T condition, const Function& f)
    {
        { condition.update(f) } -> std::same_as<void>;
        { condition.should_terminate() } -> std::same_as<bool>;
    };

} // namespace AdaptiveOA

#pragma once

#include <concepts>
#include "../../core/FunctionBase.hpp"

namespace AdaptiveOA
{

    template<typename T, FunctionLike Function>
    concept TerminateConditionLike = requires(T condition, const Function& f)
    {
        { condition.update(f) } -> std::same_as<void>;
        { condition.should_terminate() } -> std::same_as<bool>;
    };

} // namespace AdaptiveOA

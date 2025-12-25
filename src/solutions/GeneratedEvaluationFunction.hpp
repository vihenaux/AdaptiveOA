#pragma once

#include <concepts>
#include <type_traits>
#include "../core/SolutionBase.hpp"
#include "../core/FunctionBase.hpp"

namespace AdaptiveOA
{

    template <typename T>
    concept GeneratedEvaluationFunctionLike =
        std::derived_from<T, SolutionBase<T>> &&
        FunctionLike<T>;

} // namespace AdaptiveOA

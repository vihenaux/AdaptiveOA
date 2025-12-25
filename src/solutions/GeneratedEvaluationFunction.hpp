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

    template<FunctionLike FunctionType>
    class GeneratedEvaluationFunction : public SolutionBase<GeneratedEvaluationFunction<FunctionType>>, public FunctionType
    {
        public:

        template<typename>
        static constexpr bool template_dependant_false = false;

        GeneratedEvaluationFunction()
        {
            static_assert(template_dependant_false<FunctionType> && "This is the generic GeneratedEvaluationFunction class instenciation. You must specialize it in order to use it.");
        }
    };

} // namespace AdaptiveOA

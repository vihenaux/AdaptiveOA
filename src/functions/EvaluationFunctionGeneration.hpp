#pragma once

#include "../core/AlgorithmBase.hpp"
#include "../core/FunctionBase.hpp"
#include "../solutions/GeneratedEvaluationFunction.hpp"

namespace AdaptiveOA
{

    template<AlgorithmLike Algorithm, FunctionLike TargetFunctionType, GeneratedEvaluationFunctionLike GeneratedFunctionType>
    class EvaluationFunctionGeneration : public FunctionBase<EvaluationFunctionGeneration, GeneratedFunctionType>
    {
        public:

        EvaluationFunctionGeneration(const Algorithm& algorithm, const TargetFunctionType& objective_function) :
            _algorithm(algorithm),
            _objective_function(objective_function),
            _solution(objective_function.create_random_solution()) {}

        Score evaluate(const GeneratedFunctionType& generated_function) const
        {
            _solution.randomize();
            _algorithm.run(_solution, generated_function);
            return _objective_function(_solution);
        }

        private:

        Algorithm _algorithm;
        const TargetFunctionType& _objective_function;
        typename TargetFunctionType::Solution _solution;
    };

} // namespace AdaptiveOA

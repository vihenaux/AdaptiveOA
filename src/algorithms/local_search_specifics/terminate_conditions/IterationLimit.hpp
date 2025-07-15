#pragma once

#include "../../../core/FunctionBase.hpp"

namespace AdaptiveOA
{

    class IterationLimit
    {
        public:

        IterationLimit() = delete;
        IterationLimit(std::size_t iteration_limit) : m_iteration_limit(iteration_limit) {}

        template<FunctionLike Function>
        void update(const Function&)
        {
            ++m_iteration_count;
        }

        bool should_terminate() const
        {
            return m_iteration_count >= m_iteration_limit;
        }

        private:

        std::size_t m_iteration_limit;
        std::size_t m_iteration_count{0};
    };

} // namespace AdaptiveOA

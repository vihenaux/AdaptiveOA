#pragma once

#include "../../../core/FunctionBase.hpp"

namespace AdaptiveOA
{

    class FunctionCallLimit
    {
        public:

        FunctionCallLimit() = delete;
        FunctionCallLimit(std::size_t function_call_limit) : m_function_call_limit(function_call_limit) {}

        template<FunctionLike Function>
        void update(const Function& f)
        {
            m_function_call_count = f.get_nb_evaluations();
        }

        bool should_terminate() const
        {
            return m_function_call_count >= m_function_call_limit;
        }

        private:

        std::size_t m_function_call_limit;
        std::size_t m_function_call_count{0};
    };

} // namespace AdaptiveOA

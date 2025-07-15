#pragma once

#include <chrono>

namespace AdaptiveOA
{
    class TimeLimit
    {
        public:

        TimeLimit() = delete;
        TimeLimit(std::size_t micro_second_limit) : m_max_duration(std::chrono::microseconds(micro_second_limit)), m_start(std::chrono::high_resolution_clock::now()) {}

        template<FunctionLike Function>
        void update(const Function&) {}

        bool should_terminate() const
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_start) >= m_max_duration;
        }

        private:

        std::chrono::microseconds m_max_duration;
        std::chrono::high_resolution_clock::time_point m_start;
    };
}

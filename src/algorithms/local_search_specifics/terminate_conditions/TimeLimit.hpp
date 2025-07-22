#pragma once

#include <chrono>

namespace AdaptiveOA
{
    class TimeLimit
    {
        public:

        TimeLimit() = delete;
        TimeLimit(std::size_t micro_second_limit) : m_max_duration(std::chrono::microseconds(micro_second_limit)), m_start(std::chrono::steady_clock::now()) {}

        template<FunctionLike Function>
        void update(const Function&) {}

        bool should_terminate()
        {
            ++m_count;
            if(m_count >= 1000)
            {
                m_count = 0;
                return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - m_start) >= m_max_duration;
            }
            return false;
        }

        private:

        std::chrono::microseconds m_max_duration;
        std::chrono::steady_clock::time_point m_start;
        std::size_t m_count{0};
    };
}

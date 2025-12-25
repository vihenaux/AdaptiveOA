#pragma once

#include "../core/FunctionBase.hpp"
#include "../solutions/BitString.hpp"
#include "../mutations/BitFlip.hpp"

namespace AdaptiveOA
{

    class OneMax : public FunctionBase<OneMax, BitString>
    {
        public:

        OneMax() = delete;
        explicit OneMax(std::size_t size) : m_size(size) {}

        Score evaluate(const BitString& sol) const
        {
            Score count = 0;
            for (std::size_t i = 0; i < m_size; ++i)
            {
                count += static_cast<Score>(sol[i]);
            }
            return count;
        }

        Score evaluate(const BitString& sol, const BitFlip& mutation) const
        {
            Score score = *sol.get_score();
            return sol[mutation.get_bit()] ? score - 1 : score + 1;
        }

        BitString create_random_solution() const
        {
            return BitString{m_size};
        }

        private:

        std::size_t m_size;
    };

} // namespace AdaptiveOA

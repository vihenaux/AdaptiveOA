#pragma once

#include "../core/FunctionBase.hpp"
#include "../solutions/BitString.hpp"
#include "../mutations/BitFlip.hpp"

namespace AdaptiveOA
{

    class OneMax : public FunctionBase<OneMax, BitString>
    {
        public:

        Score evaluate(const BitString& sol) const
        {
            Score count = 0;
            for (std::size_t i = 0; i < sol.size(); ++i)
            {
                count += sol[i];
            }
            return count;
        }

        Score evaluate(const BitString& sol, const BitFlip& mutation) const
        {
            return sol.get_score() + ((sol[mutation.get_bit()]) ? -1 : 1);
        }
    };

} // namespace AdaptiveOA

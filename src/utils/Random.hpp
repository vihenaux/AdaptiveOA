#pragma once

#include <cstdlib>
#include <ctime>

namespace AdaptiveOA
{

    class Random
    {
        public:

        static void set_seed(unsigned int seed)
        {
            std::srand(seed);
        }

        static void init()
        {
            Random::set_seed(static_cast<unsigned int>(std::time(nullptr)));
        }

        static unsigned int get_uint()
        {
            return static_cast<unsigned int>(std::rand());
        }

        static unsigned int get_uint_range(unsigned int min, unsigned int max)
        {
            return min + (static_cast<unsigned int>(std::rand()) % (max - min + 1));
        }

        static unsigned long get_ulong_range(unsigned long min, unsigned long max)
        {
            return min + (((static_cast<unsigned long>(std::rand()) << 32ul) + static_cast<unsigned long>(std::rand())) % (max - min + 1));
        }

        static bool get_bool()
        {
            return std::rand() % 2;
        }

        static bool get_bool(double probability)
        {
            return static_cast<double>(std::rand()) / RAND_MAX < probability;
        }

        /* Generates an approximation of number of successes following a binomial distribution such as :
         * P : The probability of success
         * N : The number of draws
         * P = n/N
         * n is given as a parameter
         * The approximation is the same for every N
         */
        static unsigned int get_fast_binomial_distribution(unsigned int n)
        {
            ++n;
            unsigned int random_generated = static_cast<unsigned int>(std::rand());
            int tmp = 0;
            tmp += random_generated % (6+n);
            random_generated >>= 8;
            tmp += random_generated % (6+n);
            random_generated >>= 8;
            tmp += random_generated % (6+n);
            random_generated >>= 8;
            tmp += random_generated % (6+n);

            tmp = (n == 2) ? (tmp/4)-1 : ((tmp+1)/4)+static_cast<int>(n/2)-2;

            return (tmp <= 0) ? static_cast<unsigned int>(-tmp) : static_cast<unsigned int>(tmp-1);
        }
    };

} // namespace AdaptiveOA

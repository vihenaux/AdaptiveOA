#pragma once

#include <cstdlib>
#include <ctime>

namespace AdaptiveOA
{

    class Random
    {
        public:

        static void init()
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
        }

        static unsigned int get_uint_range(unsigned int min, unsigned int max)
        {
            return min + (static_cast<unsigned int>(std::rand()) % (max - min + 1));
        }

        static unsigned long get_uint_range(unsigned long min, unsigned long max)
        {
            return min + (((static_cast<unsigned long>(std::rand()) << 32ul) + static_cast<unsigned long>(std::rand())) % (max - min + 1));
        }

        static bool get_bool() {
            return std::rand() % 2;
        }
    };

} // namespace AdaptiveOA

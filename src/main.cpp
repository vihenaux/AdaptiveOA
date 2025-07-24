#include <iostream>
#include "solve.hpp"
#include "utils/Random.hpp"
#include "utils/CLI.hpp"

using namespace AdaptiveOA;

int main(int argc, char **argv)
{
    Random::init();
    CLI::init(argc, argv);

    localsearch_solve();

    return 0;
}

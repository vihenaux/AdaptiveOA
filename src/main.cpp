#include <iostream>
#include "develop.hpp"
#include "solve.hpp"
#include "utils/Random.hpp"
#include "utils/CLI.hpp"

using namespace AdaptiveOA;

int main(int argc, char **argv)
{
    Random::init();
    CLI::init(argc, argv);

    if(CLI::is_option_activated(CLI::Option::develop))
    {
        run_dev();
        return 0;
    }

    localsearch_solve();

    return 0;
}

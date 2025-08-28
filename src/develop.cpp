#include "develop.hpp"

#include <iostream>
#include "solutions/NKModel.hpp"
#include "neighborhoods/SpecificSeedNeighborhood.hpp"

void run_dev()
{
    // Only used for testing purposes.
    // Do not commit this file

    AdaptiveOA::NKModel model(32, 2);
    AdaptiveOA::SpecificSeedNeighborhood<AdaptiveOA::NKModel> neighborhood;

    std::string save = model.to_string();

    auto mutation = neighborhood.next_mutation();
    model.mutate(mutation);

    model.reverse_last_mutation(mutation);

    if(save == model.to_string())
        std::cout << "Reverse mutation successful" << std::endl;
    else
        std::cout << "Reverse mutation failed" << std::endl;
}

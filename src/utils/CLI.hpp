#pragma once

#include <vector>
#include <string>
#include <map>
#include <array>
#include <iostream>
#include "FastCLI.hpp"

namespace AdaptiveOA {

namespace CLI
{
    enum class Option
    {
        help,
        tabu_size,
        iteration_limit,
        function_call_limit,
        time_limit,
        no_limit,
        simulated_annealing_starting_temperature,
        simulated_annealing_decay,
        mutation_limit,
        nk,
        onemax,
        maxsat,
        localsearch,
        first_improvement,
        best_improvement,
        simulated_annealing,
        tabu,
        worst_improvement,
        iteratedlocalsearch,
        ils_iteration_limit,
        ils_function_call_limit,
        ils_time_limit,
        ils_no_limit,
        ils_nb_random_mutation,
        develop,
        // Add more options here
        count // Always keep this last to get the size of the enum
    };

    struct OptionInfo
    {
        std::string_view name;
        std::string_view default_value;
        std::string_view description;
    };

    constexpr std::array<OptionInfo, static_cast<std::size_t>(Option::count)> expected_options{{
        {"--help", "", "prints the options available"},
        {"--tabu-size", "5", "defines the size of the tabu list"},
        {"--iteration-limit", "100", "sets the limit of iterations for the search"},
        {"--function-call-limit", "10000", "sets the limit of function calls for the search"},
        {"--time-limit", "1000", "sets the time limit for the search (in micro seconds)"},
        {"--no-limit", "", "sets no limits for the search"},
        {"--simulated-annealing-starting-temperature", "100", "sets the initial temperature of the simulated annealing search"},
        {"--simulated-annealing-decay", "0.99", "sets the decay ratio of the simulated annealing temperature (must be in ]0;1[)"},
        {"--mutation-limit", "100", "sets the maximum mutation generated per iteration of the search"},
        {"--nk", "default_instance", "path of the NK file problem to solve"},
        {"--onemax", "100", "size of the onemax problem to solve"},
        {"--maxsat", "default_instance", "path of the MaxSat file problem to solve"},
        {"--localsearch", "", "sets the solving algorithm to localsearch"},
        {"--first-improvement", "", "sets the pivot rule to first improvement"},
        {"--best-improvement", "", "sets the pivot rule to best improvement"},
        {"--simulated-annealing", "", "sets the pivot rule to simulated annealing"},
        {"--tabu", "", "sets the pivot rule to tabu"},
        {"--worst-improvement", "", "sets the pivot rule to worst improvement"},
        {"--iteratedlocalsearch", "", "sets the solving algorithm to iterated localsearch"},
        {"--ils-iteration-limit", "100", "sets the limit of iterations for the ILS"},
        {"--ils-function-call-limit", "10000", "sets the limit of function calls for the ILS"},
        {"--ils-time-limit", "1000", "sets the time limit for the ILS (in micro seconds)"},
        {"--ils-no-limit", "", "sets no limits for the ILS"},
        {"--ils-nb-random-mutation", "10", "sets the number of random mutation to apply at each ILS cycle"},
        {"--dev", "", "Runs the develop.cpp file. Useful to quickly run tests"}
    }};

    static Option find_option(std::string_view option_name)
    {
        for(unsigned int i(0); i < static_cast<unsigned int>(Option::count); ++i)
        {
            if(expected_options[i].name == option_name)
            {
                return static_cast<Option>(i);
            }
        }
        return Option::count;
    }

    inline auto& arg_values()
    {
        static auto* values = new std::array<std::string, static_cast<std::size_t>(Option::count)>;
        return *values;
    }

    inline auto& arg_defined()
    {
        static auto* defined = new std::vector<bool>(static_cast<std::size_t>(Option::count), false);
        return *defined;
    }

    static void print_help()
    {
        std::cout << "Options available :\n";

        for(auto& x : expected_options)
        {
            std::cout << "\n\t" << x.name << " (" << x.default_value << ") : " << x.description << "\n";
        }

        std::cout << std::flush;
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"

    static bool is_option_activated(Option o)
    {
        return arg_defined()[static_cast<unsigned int>(o)];
    }

    static std::string_view get_option_value(Option o)
    {
        if(arg_defined()[static_cast<unsigned int>(o)])
        {
            return arg_values()[static_cast<unsigned int>(o)];
        }
        return expected_options[static_cast<unsigned int>(o)].default_value;
    }
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#pragma clang diagnostic ignored "-Wunused-function"
    static void init(int argc, char **argv)
    {
        std::string_view key;
        for(int i(1); i < argc; ++i)
        {
            key = argv[i];

            Option option = find_option(key);
            if(option == Option::count)
                continue;

            arg_defined()[static_cast<unsigned int>(option)] = true;

            if(!expected_options[static_cast<unsigned int>(option)].default_value.empty())
            {
                if(i + 1 >= argc)
                {
                    std::cerr << "Missing value for argument: " << key << "\n";
                    continue;
                }

                arg_values()[static_cast<unsigned int>(option)] = argv[i+1];
            }
        }
        std::cerr << std::flush;

        if(arg_defined()[static_cast<unsigned int>(Option::help)])
        {
            print_help();
        }

        fast_cli().set_iteration_limit(static_cast<std::size_t>(std::stoi(std::string(get_option_value(Option::iteration_limit)))));
        fast_cli().set_function_call_limit(static_cast<std::size_t>(std::stoi(std::string(get_option_value(Option::function_call_limit)))));
        fast_cli().set_time_limit(static_cast<std::size_t>(std::stoi(std::string(get_option_value(Option::time_limit)))));
        fast_cli().set_tabu_list_max_size(static_cast<unsigned int>(std::stoi(std::string(get_option_value(Option::tabu_size)))));
        fast_cli().set_simulated_annealing_starting_temperature(std::stod(std::string(get_option_value(Option::simulated_annealing_starting_temperature))));
        fast_cli().set_simulated_annealing_decay(std::stod(std::string(get_option_value(Option::simulated_annealing_decay))));
        fast_cli().set_mutation_limit(static_cast<std::size_t>(std::stoi(std::string(get_option_value(Option::mutation_limit)))));
    }
#pragma clang diagnostic pop

}
}

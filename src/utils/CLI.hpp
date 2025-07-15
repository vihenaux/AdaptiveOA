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
        {"--iteration-limit", "100", "sets the limit of iterations for the search"}
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

        fast_cli().set_iteration_limit(static_cast<unsigned int>(std::stoi(std::string(get_option_value(Option::iteration_limit)))));
        fast_cli().set_tabu_list_max_size(static_cast<unsigned int>(std::stoi(std::string(get_option_value(Option::tabu_size)))));
    }
#pragma clang diagnostic pop

}
}

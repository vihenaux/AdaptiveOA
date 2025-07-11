#pragma once

#include <string>
#include <map>
#include <array>
#include <iostream>

namespace AdaptiveOA {

namespace CLI
{
    enum class Option
    {
        Help,
        // Add more options here
        Count // Always keep this last to get the size of the enum
    };

    struct OptionInfo
    {
        std::string_view name;
        std::string_view default_value;
        std::string_view description;
    };

    constexpr std::array<OptionInfo, static_cast<std::size_t>(Option::Count)> expected_options{{
        {"--help", "", "prints the options available"}
    }};

    static Option find_option(std::string_view option_name)
    {
        for(unsigned int i(0); i < static_cast<unsigned int>(Option::Count); ++i)
        {
            if(expected_options[i].name == option_name)
            {
                return static_cast<Option>(i);
            }
        }
        return Option::Count;
    }

    inline auto& arg_values()
    {
        static auto* values = new std::array<std::string, static_cast<std::size_t>(Option::Count)>;
        return *values;
    }

    inline auto& arg_defined()
    {
        static auto* defined = new std::vector<bool>(static_cast<std::size_t>(Option::Count), false);
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
            if(option == Option::Count)
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

        if(arg_defined()[static_cast<unsigned int>(Option::Help)])
        {
            print_help();
        }
    }
#pragma clang diagnostic pop

}
}

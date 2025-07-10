#pragma once

#include <string>
#include <map>
#include <array>
#include <iostream>

namespace AdaptiveOA {

namespace CLI
{
    inline auto& expected_map()
    {
        static auto* map = new std::map<std::string, std::array<std::string, 2>>;
        return *map;
    }

    inline auto& args_map()
    {
        static auto* map = new std::map<std::string, std::string>;
        return *map;
    }

    static void add(const std::string& option_name, const std::string& default_value = "", const std::string& description = "")
    {
        expected_map().emplace(option_name, std::array<std::string, 2>{default_value, description});
    }

    static void print_help()
    {
        std::cout << "Options available :\n";

        for(auto& x : expected_map())
        {
            std::cout << "\n\t" << x.first << " (" << x.second[0] << ") : " << x.second[1] << "\n";
        }

        std::cout << std::flush;
    }

    static bool is_option_there(const std::string& option_name)
    {
        return args_map().find(option_name) != args_map().end();
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
    static std::string get_option_value(const std::string& option_name)
    {
        if(is_option_there(option_name))
        {
            return args_map()[option_name];
        }
        else if(expected_map().find(option_name) != expected_map().end())
        {
            return expected_map()[option_name][0];
        }

        std::cerr << "Option asked was not defined : " << option_name << std::endl;
        return "";
    }
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#pragma clang diagnostic ignored "-Wunused-function"
        static void init(int argc, char **argv)
        {
            add("--help", "", "prints the options available");

            std::string key;
            for(int i(1); i < argc; ++i)
            {
                key = argv[i];

                auto it = expected_map().find(key);
                if (it == expected_map().end())
                {
                    std::cerr << "Unexpected argument: " << key << "\n";
                    continue;
                }

                const std::string& default_value = it->second[0];

                if (!default_value.empty())
                {
                    if (i + 1 >= argc)
                    {
                        std::cerr << "Missing value for argument: " << key << "\n";
                        continue;
                    }

                    args_map()[key] = argv[i+1];
                }
                else
                {
                    args_map()[key] = "";
                }
            }
            std::cerr << std::flush;

            if(is_option_there("--help"))
            {
                print_help();
            }
        }
#pragma clang diagnostic pop

}
}

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "../core/SolutionBase.hpp"
#include "../utils/Random.hpp"
#include "../mutations/SeedMutation.hpp"
#include "../functions/NK.hpp"

namespace AdaptiveOA
{

    class NKModel : public NK, public SolutionBase<NKModel>
    {
        public:

        NKModel() = delete;
        NKModel(std::size_t n, std::size_t k) : NK(n, k) { do_randomize(); }
        NKModel(const std::string& file_path) : NK(file_path) {}

        friend SolutionBase<NKModel>;

        private:

        void do_randomize()
        {
            NK::set_random_instance();
        }

        std::string do_to_string() const
        {
            std::ostringstream oss;
            oss << NK::m_n << " " << NK::m_k << "\n";
            for(unsigned int link : NK::m_links)
            {
                oss << link << "\n";
            }
            for(unsigned int value : NK::m_matrix)
            {
                if(value == 1000000)
                    oss << "1.000000\n";
                else
                    oss << "0." << value << "\n";
            }
            return oss.str();
        }

        void do_mutate(const SeedMutation& seed)
        {
            Random::set_seed(seed.get_seed());

            unsigned int nb_cells_to_mutate = Random::get_fast_binomial_distribution(1);
            unsigned int nb_links_to_mutate = Random::get_fast_binomial_distribution(1);
            while(!nb_cells_to_mutate && !nb_links_to_mutate)
            {
                nb_cells_to_mutate = Random::get_fast_binomial_distribution(1);
                nb_links_to_mutate = Random::get_fast_binomial_distribution(1);
            }

            for(unsigned int i(0); i < nb_cells_to_mutate; ++i)
            {
                unsigned int index = Random::get_uint_range(0, static_cast<unsigned int>(NK::m_matrix.size()-1));
                unsigned int tmp = NK::m_matrix[index];
                tmp += Random::get_uint_range(1, 1000000);
                tmp %= 1000001;
                NK::m_matrix[index] = tmp;
            }

            for(unsigned int i(0); i < nb_links_to_mutate; ++i)
            {
                unsigned int index = Random::get_uint_range(0, static_cast<unsigned int>(NK::m_links.size()-1));
                unsigned int value_to_mutate = NK::m_links[index];
                unsigned int link_index = index/NK::m_k1;

                if(NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index] > 1)
                {
                    --NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index];
                }
                else
                {
                    NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index] = 0;
                    for(unsigned int j(0); j < NK::m_var_in_links_sizes[value_to_mutate]; ++j)
                    {
                        if(NK::m_var_in_links[value_to_mutate*NK::m_n+j] == link_index)
                        {
                            --NK::m_var_in_links_sizes[value_to_mutate];
                            NK::m_var_in_links[value_to_mutate*NK::m_n+j] = NK::m_var_in_links[value_to_mutate*NK::m_n+NK::m_var_in_links_sizes[value_to_mutate]];
                            break;
                        }
                    }
                }

                NK::m_links[index] += Random::get_uint_range(1,static_cast<unsigned int>(NK::m_n-1));
                NK::m_links[index] %= NK::m_n;

                ++NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index];
                if(NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index] == 1)
                {
                    ++NK::m_var_in_links_sizes[value_to_mutate];
                    NK::m_var_in_links[value_to_mutate*NK::m_n+NK::m_var_in_links_sizes[value_to_mutate]] = NK::m_links[index];
                }
            }
        }

        void do_reverse_mutation(const SeedMutation& seed)
        {
            Random::set_seed(seed.get_seed());

            unsigned int nb_cells_to_mutate = Random::get_fast_binomial_distribution(1);
            unsigned int nb_links_to_mutate = Random::get_fast_binomial_distribution(1);
            while(!nb_cells_to_mutate && !nb_links_to_mutate)
            {
                nb_cells_to_mutate = Random::get_fast_binomial_distribution(1);
                nb_links_to_mutate = Random::get_fast_binomial_distribution(1);
            }

            for(unsigned int i(0); i < nb_cells_to_mutate; ++i)
            {
                unsigned int index = Random::get_uint_range(0, static_cast<unsigned int>(NK::m_matrix.size()-1));
                unsigned int tmp = NK::m_matrix[index];
                tmp += 1000001-Random::get_uint_range(1, 1000000);
                tmp %= 1000001;
                NK::m_matrix[index] = tmp;
            }

            for(unsigned int i(0); i < nb_links_to_mutate; ++i)
            {
                unsigned int index = Random::get_uint_range(0, static_cast<unsigned int>(NK::m_links.size()-1));
                unsigned int value_to_mutate = NK::m_links[index];
                unsigned int link_index = index/NK::m_k1;

                if(NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index] > 1)
                {
                    --NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index];
                }
                else
                {
                    NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index] = 0;
                    for(unsigned int j(0); j < NK::m_var_in_links_sizes[value_to_mutate]; ++j)
                    {
                        if(NK::m_var_in_links[value_to_mutate*NK::m_n+j] == link_index)
                        {
                            --NK::m_var_in_links_sizes[value_to_mutate];
                            NK::m_var_in_links[value_to_mutate*NK::m_n+j] = NK::m_var_in_links[value_to_mutate*NK::m_n+NK::m_var_in_links_sizes[value_to_mutate]];
                            break;
                        }
                    }
                }

                NK::m_links[index] += NK::m_n-Random::get_uint_range(1,static_cast<unsigned int>(NK::m_n-1));
                NK::m_links[index] %= NK::m_n;

                ++NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index];
                if(NK::m_var_in_link_times[value_to_mutate*NK::m_n+link_index] == 1)
                {
                    ++NK::m_var_in_links_sizes[value_to_mutate];
                    NK::m_var_in_links[value_to_mutate*NK::m_n+NK::m_var_in_links_sizes[value_to_mutate]] = NK::m_links[index];
                }
            }
        }
    };

} // namespace AdaptiveOA

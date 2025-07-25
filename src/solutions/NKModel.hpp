#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "../core/SolutionBase.hpp"
#include "../utils/Random.hpp"
#include "../mutations/BitFlip.hpp"

namespace AdaptiveOA
{

    class NKModel : public NK, public SolutionBase<NKModel>
    {
        public:

        NKModel() = delete;
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
            for(unsigned int link : m_links)
            {
                oss << link << "\n";
            }
            for(unsigned int value : m_matrix)
            {
                if(value = 1000000)
                    oss << "1.000000\n";
                else
                    oss << "0." << value << "\n";
            }
            return oss.str();
        }

        void do_mutate(const BitFlip& bitflip)
        {
        }

        void do_reverse_mutation(const BitFlip& bitflip)
        {
        }
    };

} // namespace AdaptiveOA

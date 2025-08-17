#pragma once

#include<assert.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include "../core/FunctionBase.hpp"
#include "../solutions/BitString.hpp"
#include "../mutations/BitFlip.hpp"
#include "../utils/Random.hpp"

namespace AdaptiveOA
{

    class NK : public FunctionBase<NK, BitString>
    {
        public:

        NK() = delete;
        NK(std::size_t n, std::size_t k) : m_n(n), m_k(k), m_k1(k+1), m_2k1(1 << (k+1))
        {
            m_matrix.resize(m_n*m_2k1);
            m_links.resize(m_n*m_k1);
            m_var_in_links.resize(m_n*m_n);
            m_var_in_link_times.resize(m_n*m_n, 0);
            m_var_in_links_sizes.resize(m_n, 0);
        }

        NK(const std::string& file_path)
        {
            std::ifstream in(file_path);

            if(!in.is_open())
                std::cerr << "Cannot open file : " << file_path << std::endl;
            assert(in.is_open());

            in >> m_n >> m_k;
            m_k1 = m_k + 1;
            m_2k1 = 1 << m_k1; // 2 pow k+1

            m_matrix.resize(m_n*m_2k1);
            m_links.resize(m_n*m_k1);
            m_var_in_links.resize(m_n*m_n);
            m_var_in_link_times.resize(m_n*m_n, 0);
            m_var_in_links_sizes.resize(m_n, 0);

            for(unsigned int i(0); i < m_n; ++i)
            {
                for(unsigned int j(0); j < m_k1; ++j)
                {
                    unsigned int tmp;
                    in >> tmp;
                    m_links[m_k1*i+j] = tmp;

                    ++m_var_in_link_times[tmp*m_n+i];

                    if(m_var_in_link_times[tmp*m_n+i] == 1)
                    {
                        m_var_in_links[tmp*m_n+m_var_in_links_sizes[tmp]] = i;
                        ++m_var_in_links_sizes[tmp];
                    }
                }
            }

            for(unsigned int i(0); i < m_n*m_2k1; ++i)
            {
                char tmp;
                in.get(tmp);
                while(tmp != '0' && tmp != '1')
                    in.get(tmp);

                m_matrix[i] = 1000000u*static_cast<unsigned int>(tmp-'0');
                in.get(tmp);

                if(tmp == '.')
                {
                    in.get(tmp);
                    unsigned int j(0);

                    while(tmp >= '0' && tmp <= '9')
                    {
                        m_matrix[i] += static_cast<unsigned int>(std::pow(10u,5u-j))*static_cast<unsigned int>(tmp-'0');
                        ++j;
                        in.get(tmp);
                    }
                }
            }
        }

        Score evaluate(const BitString& sol) const
        {
            Score sum = 0;
            for(unsigned int i(0); i < m_n; ++i)
            {
                unsigned int tmp = 0;
                for(unsigned int j(0); j < m_k1; ++j)
                {
                    tmp += (static_cast<unsigned int>(sol[m_links[m_k1*i+j]]) << j);
                }
                sum += m_matrix[m_2k1*i+tmp];
            }
            return sum;
        }

        Score evaluate(const BitString& sol, const BitFlip& mutation) const
        {
            Score sum = *sol.get_score();
            for(unsigned int i(0); i < m_var_in_links_sizes[mutation.get_bit()]; ++i)
            {
                unsigned int mutated_link = m_var_in_links[mutation.get_bit()*m_n+i];
                std::size_t link_index = m_k1*mutated_link;
                std::size_t matrix_index = m_2k1*mutated_link;
                unsigned int matrix_offset = 0;
                unsigned int matrix_offset_mutated = 0;
                for(unsigned int j(0); j < m_k1; ++j)
                {
                    bool bit = sol[m_links[link_index+j]];
                    matrix_offset += (static_cast<unsigned int>(bit) << j);
                    matrix_offset_mutated += (m_links[link_index+j] == mutation.get_bit()) ? (static_cast<unsigned int>(!bit) << j) : (static_cast<unsigned int>(bit) << j);
                }
                sum -= m_matrix[matrix_index+matrix_offset];
                sum += m_matrix[matrix_index+matrix_offset_mutated];
            }
            return sum;
        }

        std::size_t get_n() const
        {
            return m_n;
        }

        std::size_t get_k() const
        {
            return m_k;
        }

        protected:

        void set_random_instance()
        {
            for(unsigned int i(0); i < m_var_in_link_times.size(); ++i)
            {
                m_var_in_link_times[i] = 0;
            }
            for(unsigned int i(0); i < m_var_in_links_sizes.size(); ++i)
            {
                m_var_in_links_sizes[i] = 0;
            }

            for(unsigned int i(0); i < m_n; ++i)
            {
                for(unsigned int j(0); j < m_k1; ++j)
                {
                    unsigned int tmp = Random::get_uint_range(0,static_cast<unsigned int>(m_n-1));
                    m_links[m_k1*i+j] = tmp;

                    ++m_var_in_link_times[tmp*m_n+i];

                    if(m_var_in_link_times[tmp*m_n+i] == 1)
                    {
                        m_var_in_links[tmp*m_n+m_var_in_links_sizes[tmp]] = i;
                        ++m_var_in_links_sizes[tmp];
                    }
                }
            }

            for(unsigned int i(0); i < m_matrix.size(); ++i)
            {
                m_matrix[i] = Random::get_uint_range(0u,1000000u);
            }
        }

        std::size_t m_n{0};
        std::size_t m_k{0};
        std::size_t m_k1{0};  // k+1
        std::size_t m_2k1{0}; // 2^(k+1)
        std::vector<unsigned int> m_matrix{0};
        std::vector<unsigned int> m_links{0};
        std::vector<unsigned int> m_var_in_links{0};
        std::vector<unsigned int> m_var_in_link_times{0};
        std::vector<unsigned int> m_var_in_links_sizes{0};
    };

} // namespace AdaptiveOA

#pragma once

#include <vector>
#include <fstream>
#include <string>
#include "../core/FunctionBase.hpp"
#include "../solutions/BitString.hpp"

namespace AdaptiveOA
{

    class MaxSat : public FunctionBase<MaxSat, BitString>
    {
        public:

        MaxSat() = delete;
        MaxSat(const std::string& file_path)
        {
            std::ifstream in(file_path);

            if(!in.is_open())
                std::cerr << "Cannot open file : " << file_path << std::endl;
            assert(in.is_open());

            std::string tmp_str;
            while(true)
            {
                in >> tmp_str;
                if(tmp_str == "c")
                {
                    char buffer[256];
                    in.getline(buffer,256);
                }
                else if(tmp_str == "p")
                {
                    in >> tmp_str >> m_nb_literals >> m_nb_clauses;
                    break;
                }
            }

            long savepoint = in.tellg();

            m_clause_length = 0;
            for(unsigned int i(0); i < m_nb_clauses; ++i)
            {
                int tmp_int(0);
                std::size_t clause_length = 0;
                do{
                    in >> tmp_int;
                    ++clause_length;
                } while(tmp_int != 0);
                --clause_length;

                m_clause_length = (clause_length > m_clause_length) ? clause_length : m_clause_length;
            }

            in.seekg(savepoint);

            m_clauses.resize(m_nb_clauses * m_clause_length);
            m_literal_in_clause.resize(m_nb_literals * m_nb_clauses);
            m_literal_in_clause_sizes.resize(m_nb_literals, 0);
            m_literal_in_clause_times.resize(m_nb_literals * m_nb_clauses, 0);

            for(unsigned int i(0); i < m_nb_clauses; ++i)
            {
                bool clause_end_reached = false;
                for(unsigned int j(0); j < m_clause_length; ++j)
                {
                    if(clause_end_reached)
                    {
                        m_clauses[i*m_clause_length+j] = 0;
                        continue;
                    }

                    int file_value;
                    in >> file_value;
                    if(file_value == 0)
                    {
                        clause_end_reached = true;
                        m_clauses[i*m_clause_length+j] = 0;
                        continue;
                    }

                    m_clauses[i*m_clause_length+j] = file_value;

                    unsigned int file_value_abs = static_cast<unsigned int>((file_value < 0) ? (-file_value) : file_value);
                    --file_value_abs;

                    ++m_literal_in_clause_times[file_value_abs*m_nb_clauses+i];
                    if(m_literal_in_clause_times[file_value_abs*m_nb_clauses+i] == 1)
                    {
                        m_literal_in_clause[file_value_abs*m_nb_clauses+m_literal_in_clause_sizes[file_value_abs]] = i;
                        ++m_literal_in_clause_sizes[file_value_abs];
                    }
                }
                in >> m_clauses[i];
            }
        }

        Score evaluate(const BitString& sol) const
        {
            Score sum = 0;
            for(unsigned int i(0); i < m_nb_clauses; ++i)
            {
                bool clause_satisfied = false;
                for(unsigned int j(0); j < m_clause_length; ++j)
                {
                    int literal = m_clauses[i*m_clause_length+j];
                    if(!literal)
                        break;
                    bool literal_satisfied = (literal < 0) ? (!sol[static_cast<std::size_t>(-literal-1)]) : sol[static_cast<std::size_t>(literal-1)];
                    clause_satisfied = clause_satisfied || literal_satisfied;
                }
                sum += clause_satisfied;
            }
            return sum;
        }

        Score evaluate(const BitString& sol, const BitFlip& mutation) const
        {
            Score sum = *sol.get_score();
            for(unsigned int i(0); i < m_literal_in_clause_sizes[mutation.get_bit()]; ++i)
            {
                unsigned int mutated_clause = m_literal_in_clause[mutation.get_bit()*m_nb_literals+i];

                bool clause_satisfied = false;
                bool clause_satisfied_mutated = false;
                for(unsigned int j(0); j < m_clause_length; ++j)
                {
                    int literal = m_clauses[mutated_clause*m_clause_length+j];
                    if(!literal)
                        break;
                    bool literal_satisfied = (literal < 0) ? (!sol[static_cast<std::size_t>(-literal-1)]) : sol[static_cast<std::size_t>(literal-1)];
                    clause_satisfied = clause_satisfied || literal_satisfied;

                    int literal_abs = (literal < 0) ? (-literal) : literal;
                    bool literal_satisfied_mutated = (static_cast<std::size_t>(literal_abs-1) == mutation.get_bit()) ? !literal_satisfied : literal_satisfied;
                    clause_satisfied_mutated = clause_satisfied_mutated || literal_satisfied_mutated;
                }

                sum -= clause_satisfied;
                sum += clause_satisfied_mutated;
            }
            return sum;
        }

        BitString create_random_solution() const
        {
            return BitString{m_nb_literals};
        }

        std::size_t get_nb_literals() const
        {
            return m_nb_literals;
        }

        std::size_t get_nb_clauses() const
        {
            return m_nb_clauses;
        }

        private:
    
        std::size_t m_nb_literals;
        std::size_t m_nb_clauses;
        std::size_t m_clause_length;
        std::vector<int> m_clauses;
        std::vector<unsigned int> m_literal_in_clause;
        std::vector<unsigned int> m_literal_in_clause_sizes;
        std::vector<unsigned int> m_literal_in_clause_times;
    };

} // namespace AdaptiveOA

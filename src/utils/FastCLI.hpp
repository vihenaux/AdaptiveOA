#pragma once

namespace AdaptiveOA
{

    class FastCLI
    {
        public:

        std::size_t get_iteration_limit() const
        {
            return m_iteration_limit;
        }

        std::size_t get_function_call_limit() const
        {
            return m_function_call_limit;
        }

        double get_simulated_annealing_starting_temperature() const
        {
            return m_simulated_annealing_starting_temperature;
        }

        double get_simulated_annealing_decay() const
        {
            return m_simulated_annealing_decay;
        }

        std::size_t get_mutation_limit() const
        {
            return m_mutation_limit;
        }

        std::size_t get_time_limit() const
        {
            return m_time_limit;
        }

        unsigned int get_tabu_list_max_size() const
        {
            return m_tabu_list_max_size;
        }

        void set_iteration_limit(std::size_t iteration_limit)
        {
            m_iteration_limit = iteration_limit;
        }

        void set_function_call_limit(std::size_t function_call_limit)
        {
            m_function_call_limit = function_call_limit;
        }

        void set_time_limit(std::size_t time_limit)
        {
            m_time_limit = time_limit;
        }

        void set_tabu_list_max_size(unsigned int tabu_list_max_size)
        {
            m_tabu_list_max_size = tabu_list_max_size;
        }

        void set_simulated_annealing_starting_temperature(double simulated_annealing_starting_temperature)
        {
            m_simulated_annealing_starting_temperature = simulated_annealing_starting_temperature;
        }

        void set_simulated_annealing_decay(double simulated_annealing_decay)
        {
            m_simulated_annealing_decay = simulated_annealing_decay;
        }

        void set_mutation_limit(std::size_t mutation_limit)
        {
            m_mutation_limit = mutation_limit;
        }

        private:

        std::size_t m_iteration_limit{0};
        std::size_t m_function_call_limit{0};
        std::size_t m_time_limit{0};
        double m_simulated_annealing_starting_temperature{0.};
        double m_simulated_annealing_decay{0.};
        std::size_t m_mutation_limit{0};
        unsigned int m_tabu_list_max_size{0};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
        unsigned int padding{0};
#pragma clang diagnostic pop
    };

    inline auto& fast_cli()
    {
        static auto* fast_cli = new FastCLI;
        return *fast_cli;
    }

}

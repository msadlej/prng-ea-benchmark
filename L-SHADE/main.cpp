/*
  L-SHADE implemented by C++ for Special Session & Competition on Real-Parameter
  Single Objective Optimization at CEC-2014 See the details of L-SHADE in the
  following paper:

  * Ryoji Tanabe and Alex Fukunaga: Improving the Search Performance of SHADE
  Using Linear Population Size Reduction,  Proc. IEEE Congress on Evolutionary
  Computation (CEC-2014), Beijing, July, 2014.

  Version: 1.0   Date: 16/Apr/2014
  Written by Ryoji Tanabe (rt.ryoji.tanabe [at] gmail.com)
*/

#include "de.h"

double *OShift, *M, *y, *z, *x_bound;
int ini_flag = 0, n_flag, func_flag, *SS;

int g_function_number;
int g_problem_size;
unsigned int g_max_num_evaluations;

int g_pop_size;
double g_arc_rate;
int g_memory_size;
double g_p_best_rate;

bool g_buffer_mode;
std::unique_ptr<
    RandomBuffer<std::uniform_real_distribution<>, std::minstd_rand>>
    random_buffer;

int main(int argc, char **argv) {
    size_t buffer_size;
    BufferCycleStrategy strategy;

    if (argc < 2) {
        g_buffer_mode = false;
    } else if (argc == 2) {
        g_buffer_mode = true;
        buffer_size = static_cast<size_t>(std::stoul(argv[1]));
        strategy = BufferCycleStrategy::RESTART;
    } else if (argc == 3) {
        g_buffer_mode = true;
        buffer_size = static_cast<size_t>(std::stoul(argv[1]));

        std::string action(argv[2]);
        if (action == "shuffle")
            strategy = BufferCycleStrategy::SHUFFLE;
        else if (action == "offset")
            strategy = BufferCycleStrategy::OFFSET;
        else
            strategy = BufferCycleStrategy::RESTART;
    } else {
        std::cerr << "Usage: " << argv[0]
                  << " [buffer size] [shuffle/offset/none]" << std::endl;
        return 1;
    }

    int num_runs = 51;
    int num_functions = 28;
    g_problem_size = 50;
    g_max_num_evaluations = g_problem_size * 10000;

    // L-SHADE parameters
    g_pop_size = (int)round(g_problem_size * 18);
    g_memory_size = 6;
    g_arc_rate = 2.6;
    g_p_best_rate = 0.11;

    std::cout << "Function,Dimension,Run,Error" << std::endl;
    for (int r = 0; r < num_runs; r++) {
        Fitness best_fitness = 0;
        if (g_buffer_mode) {
            auto seed = std::chrono::high_resolution_clock::now()
                            .time_since_epoch()
                            .count();
            std::minstd_rand gen(seed);
            std::uniform_real_distribution<> dis(0.0, 1.0);

            random_buffer.reset(
                new RandomBuffer<std::uniform_real_distribution<>,
                                 std::minstd_rand>(gen, dis, buffer_size,
                                                   strategy));
        }

        for (int f = 0; f < num_functions; f++) {
            g_function_number = f + 1;

            LSHADE *alg = new LSHADE();
            best_fitness = alg->run();
            std::cout << g_function_number << "," << g_problem_size << ","
                      << (r + 1) << "," << best_fitness << std::endl;

            delete alg;
        }
    }

    return 0;
}

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

RandomReader *random_reader;
bool g_file_mode;

int main(int argc, char **argv) {
    if (argc < 2) {
        g_file_mode = false;
    } else if (argc == 2) {
        g_file_mode = true;
        std::string file_path = argv[1];

        random_reader = new RandomReader(file_path, true);
    } else {
        std::cerr << "Usage: " << argv[0] << " [random number file path]"
                  << std::endl;
        return 1;
    }

    // number of runs
    int num_runs = 51;
    // dimension size. please select from 10, 30, 50, 100
    g_problem_size = 10;
    // available number of fitness evaluations
    g_max_num_evaluations = g_problem_size * 10000;

    // random seed is selected based on time according to competition rules
    srand((unsigned)time(NULL));

    // L-SHADE parameters
    g_pop_size = (int)round(g_problem_size * 18);
    g_memory_size = 6;
    g_arc_rate = 2.6;
    g_p_best_rate = 0.11;

    std::cout << "Function,Dimension,Run,ErrorValue" << std::endl;
    for (int i = 0; i < 10; i++) {
        g_function_number = i + 1;
        Fitness best_fitness = 0;

        for (int j = 0; j < num_runs; j++) {
            searchAlgorithm *alg = new LSHADE();
            best_fitness = alg->run();
            std::cout << g_function_number << "," << g_problem_size << ","
                      << (j + 1) << "," << best_fitness << std::endl;
        }
    }

    if (g_file_mode) {
        delete random_reader;
    }

    return 0;
}

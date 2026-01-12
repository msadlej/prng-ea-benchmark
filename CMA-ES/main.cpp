#include "Random-Reader/random_reader.h"
#include <iostream>
#include <libcmaes/cmaes.h>
#include <vector>

using namespace libcmaes;

void cec21_bias_shift_rot_func(double *x, double *f, int nx, int mx,
                               int func_num);

double *OShift = nullptr, *M = nullptr, *y = nullptr, *z = nullptr,
       *x_bound = nullptr;
int ini_flag = 0, n_flag, func_flag, *SS = nullptr;
int g_function_number = 1;
extern bool g_file_mode;
extern RandomReader *random_reader;

FitFunc fcec21_bias_shift_rot = [](const double *x, const int N) {
    double result;
    cec21_bias_shift_rot_func(const_cast<double *>(x), &result, N, 1,
                              g_function_number);
    return result;
};

inline double randDouble() {
    if (g_file_mode) {
        return random_reader->next();
    }

    return (double)rand() / (double)RAND_MAX;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        g_file_mode = false;
    } else if (argc == 2) {
        g_file_mode = true;
        std::string file_path = argv[1];

        random_reader = new RandomReader(file_path, true);
    } else if (argc == 3) {
        g_file_mode = true;
        std::string file_path = argv[1];
        size_t n_rows = static_cast<size_t>(std::stoul(argv[2]));

        random_reader = new RandomReader(file_path, n_rows, true);
    } else {
        std::cerr << "Usage: " << argv[0] << " [file path] [max numbers]"
                  << std::endl;
        return 1;
    }

    const int dim = 10;
    const int num_runs = 51;
    const int num_functions = 10;

    double lbounds[dim], ubounds[dim];
    for (int i = 0; i < dim; i++) {
        lbounds[i] = -100.0;
        ubounds[i] = 100.0;
    }

    std::cout << "Function,Dimension,Run,ErrorValue,Evals,Time" << std::endl;
    for (int i = 0; i < 10; i++) {
        g_function_number = i + 1;

        for (int run = 0; run < num_runs; run++) {
            ini_flag = 0;

            std::vector<double> x0(dim);
            for (int d = 0; d < dim; d++) {
                x0[d] = ((ubounds[d] - lbounds[d]) * randDouble()) + lbounds[d];
            }

            double sigma = 20.0;
            GenoPheno<pwqBoundStrategy> gp(lbounds, ubounds, dim);
            CMAParameters<GenoPheno<pwqBoundStrategy>> cmaparams(x0, sigma, -1,
                                                                 0, gp);

            CMASolutions cmasols = cmaes<GenoPheno<pwqBoundStrategy>>(
                fcec21_bias_shift_rot, cmaparams);
            double best_fitness =
                cmasols.get_best_seen_candidate().get_fvalue();

            std::cout << g_function_number << "," << dim << "," << (run + 1)
                      << "," << best_fitness << "," << cmasols.fevals() << ","
                      << cmasols.elapsed_time() / 1000.0 << std::endl;
        }
    }

    if (g_file_mode) {
        delete random_reader;
    }

    return 0;
}

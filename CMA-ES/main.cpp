#include "CEC-2013/cec2013_func.h"
#include "Random-Buffer/random_buffer.h"
#include <iostream>
#include <libcmaes/cmaes.h>
#include <vector>

using namespace libcmaes;

double *OShift = nullptr, *M = nullptr, *y = nullptr, *z = nullptr,
       *x_bound = nullptr;
int ini_flag = 0, n_flag, func_flag, *SS = nullptr;
int g_function_number = 0;

FitFunc fcec13_test_func = [](const double *x, const int N) {
    double result;
    test_func(const_cast<double *>(x), &result, N, 1, g_function_number);
    return result;
};

extern bool g_buffer_mode;
extern std::unique_ptr<
    RandomBuffer<std::normal_distribution<>, std::mt19937_64>>
    random_buffer;

int main(int argc, char *argv[]) {
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

    const int num_runs = 51;
    const int num_functions = 28;
    const int dim = 50;

    double lbounds[dim], ubounds[dim];
    for (int i = 0; i < dim; i++) {
        lbounds[i] = -100.0;
        ubounds[i] = 100.0;
    }

    std::cout << "Function,Dimension,Run,Error,Evals,Time" << std::endl;
    for (int r = 0; r < num_runs; r++) {
        if (g_buffer_mode) {
            auto seed = std::chrono::high_resolution_clock::now()
                            .time_since_epoch()
                            .count();
            std::mt19937_64 gen(seed);
            std::normal_distribution<> dis(0.0, 1.0);

            random_buffer.reset(
                new RandomBuffer<std::normal_distribution<>, std::mt19937_64>(
                    gen, dis, buffer_size, strategy));
        }

        for (int f = 0; f < num_functions; f++) {
            g_function_number = f + 1;
            ini_flag = 0;

            std::vector<double> x0(dim, 0.0);
            double sigma = 10.0;
            GenoPheno<pwqBoundStrategy> gp(lbounds, ubounds, dim);
            CMAParameters<GenoPheno<pwqBoundStrategy>> cmaparams(x0, sigma, -1,
                                                                 0, gp);
            cmaparams.set_max_fevals(dim * 10000);

            CMASolutions cmasols =
                cmaes<GenoPheno<pwqBoundStrategy>>(fcec13_test_func, cmaparams);
            double best_fitness =
                cmasols.get_best_seen_candidate().get_fvalue();

            std::cout << g_function_number << "," << dim << "," << (r + 1)
                      << "," << best_fitness << "," << cmasols.fevals() << ","
                      << cmasols.elapsed_time() / 1000.0 << std::endl;
        }
    }

    return 0;
}

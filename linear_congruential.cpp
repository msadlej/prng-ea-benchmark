#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

std::vector<long double> getDecimalFractions(unsigned long n_samples) {
    auto seed =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::minstd_rand gen(seed);
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::vector<long double> result(n_samples);

    for (unsigned long i = 0; i < n_samples; i++) {
        result[i] = dis(gen);
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./linear_congruential {n_samples}" << std::endl;
        return 1;
    }

    unsigned long n_samples = std::strtoul(argv[1], nullptr, 10);
    std::vector<long double> result = getDecimalFractions(n_samples);

    std::cout << std::fixed << std::setprecision(20);
    std::cout << "Linear Congruential Numbers" << std::endl;
    for (const auto &num : result) {
        std::cout << num << std::endl;
    }

    return 0;
}

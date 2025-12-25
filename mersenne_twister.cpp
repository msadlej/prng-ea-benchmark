#include <bits/stdc++.h>
#include <ctime>
#include <random>

std::vector<long double> getDecimalFractions(unsigned long n_samples) {
    std::mt19937_64 gen(time(nullptr));
    std::vector<long double> result(n_samples);

    for (unsigned long i = 0; i < n_samples; i++) {
        result[i] = gen() / (long double)gen.max();
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./mersenne_twister {n_samples}" << std::endl;
        return 1;
    }

    unsigned long n_samples = std::strtoul(argv[1], nullptr, 10);
    std::vector<long double> result = getDecimalFractions(n_samples);

    std::cout << std::fixed << std::setprecision(20);
    std::cout << "Mersenne-Twister Numbers" << std::endl;
    for (const auto &num : result) {
        std::cout << num << std::endl;
    }

    return 0;
}

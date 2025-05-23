#include <bits/stdc++.h>
#include <fstream>


std::vector<long double> getDecimalFractions(unsigned long n_samples) {
    std::vector<long double> result(n_samples);

    for (unsigned long i = 0; i < n_samples; i++) {
        result[i] = rand()/(long double)RAND_MAX;
    }

    return result;
}


std::vector<long double> getGaussianDistribution(unsigned long n_samples, long double mean = 0.0, long double std_dev = 1.0) {
    std::minstd_rand engine;
    std::normal_distribution<long double> dist(mean, std_dev);

    std::vector<long double> result(n_samples);
    for (unsigned long i = 0; i < n_samples; i++) {
        result[i] = dist(engine);
    }

    return result;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./linear_congruential {n_samples}" << std::endl;
        return 1;
    }

    unsigned long n_samples = std::strtoul(argv[1], nullptr, 10);
    std::vector<long double> result = getGaussianDistribution(n_samples);

    std::ofstream csv_file("data/gaussian/linear_congruential.csv");
    csv_file << std::setprecision(std::numeric_limits<long double>::digits10 + 1);

    csv_file << "Linear Congruential Numbers" << std::endl;
    for (const auto &num : result) {
        csv_file << num << std::endl;
    }

    csv_file.close();
    std::cout << "Numbers written to data/gaussian/linear_congruential.csv" << std::endl;

    return 0;
}

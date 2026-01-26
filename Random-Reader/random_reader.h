#pragma once

#include "rapidcsv.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

enum class ReaderCycleStrategy { SHUFFLE, OFFSET, RESTART };

class EmptyFileException : public std::runtime_error {
  public:
    EmptyFileException();
};

class RandomReader {
  private:
    std::minstd_rand gen;
    ReaderCycleStrategy strategy;
    std::vector<double> values;
    size_t current_row;

    void restart();

  public:
    RandomReader(const std::string &filename, ReaderCycleStrategy mode);
    ~RandomReader();

    double next();
};

inline EmptyFileException::EmptyFileException()
    : std::runtime_error("The file is empty!") {}

inline RandomReader::RandomReader(const std::string &filename,
                                  ReaderCycleStrategy mode)
    : strategy(mode) {
    auto seed =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    gen = std::minstd_rand(seed);
    rapidcsv::Document doc(filename);

    if (doc.GetRowCount() <= 0) {
        throw EmptyFileException();
    }

    values = doc.GetColumn<double>(0);
    current_row = 0;
}

inline RandomReader::~RandomReader() {}

inline double RandomReader::next() {
    if (current_row >= values.size()) {
        restart();
    }

    double result = values[current_row];
    current_row++;

    return result;
}

inline void RandomReader::restart() {
    current_row = 0;

    if (strategy == ReaderCycleStrategy::SHUFFLE) {
        std::shuffle(values.begin(), values.end(), gen);
    } else if (strategy == ReaderCycleStrategy::OFFSET) {
        size_t k = gen() % values.size();
        std::rotate(values.begin(), values.begin() + k, values.end());
    }
}

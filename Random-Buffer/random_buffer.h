#pragma once

#include <algorithm>
#include <random>
#include <vector>

enum class BufferCycleStrategy { SHUFFLE, OFFSET, RESTART };

template <typename Distribution, typename RNG> class RandomBuffer {
  private:
    std::vector<double> values;
    size_t buffer_size;
    BufferCycleStrategy strategy;
    RNG engine;
    Distribution dist;
    size_t current_row;

    void restart();

  public:
    RandomBuffer(RNG &engine, Distribution &dist, size_t buffer_size,
                 BufferCycleStrategy restart_strategy);
    ~RandomBuffer();

    double next();
};

template <typename Distribution, typename RNG>
RandomBuffer<Distribution, RNG>::RandomBuffer(RNG &engine, Distribution &dist,
                                              size_t buffer_size,
                                              BufferCycleStrategy strategy)
    : buffer_size(buffer_size), strategy(strategy), engine(engine), dist(dist),
      current_row(0) {
    for (size_t i = 0; i < buffer_size; ++i) {
        values.push_back(dist(engine));
    }
}

template <typename Distribution, typename RNG>
RandomBuffer<Distribution, RNG>::~RandomBuffer() {}

template <typename Distribution, typename RNG>
double RandomBuffer<Distribution, RNG>::next() {
    if (current_row >= buffer_size) {
        restart();
    }

    double result = values[current_row];
    current_row++;

    return result;
}

template <typename Distribution, typename RNG>
void RandomBuffer<Distribution, RNG>::restart() {
    current_row = 0;

    if (strategy == BufferCycleStrategy::SHUFFLE) {
        std::shuffle(values.begin(), values.end(), engine);
    } else if (strategy == BufferCycleStrategy::OFFSET) {
        size_t k = engine() % buffer_size;
        std::rotate(values.begin(), values.begin() + k, values.end());
    }
}

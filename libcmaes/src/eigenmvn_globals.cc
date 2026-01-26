/**
 * Global variables for eigenmvn random number generation
 */

#include "Random-Buffer/random_buffer.h"
#include <memory>

bool g_buffer_mode;
std::unique_ptr<RandomBuffer<std::normal_distribution<>, std::mt19937_64>>
    random_buffer;

#pragma once

#include "rapidcsv.h"
#include <stdexcept>
#include <string>

class EmptyFileException : public std::runtime_error {
  public:
    EmptyFileException();
};

class RandomReader {
  private:
    std::vector<double> values;
    size_t current_row;

  public:
    RandomReader(const std::string &filename, bool header = false);
    RandomReader(const std::string &filename, size_t n_rows,
                 bool header = false);

    double next();
    void reset();
};

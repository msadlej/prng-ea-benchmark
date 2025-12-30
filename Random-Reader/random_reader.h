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
    rapidcsv::Document doc;
    size_t current_row;
    bool header;

  public:
    RandomReader(const std::string &filename, bool header = false);

    double next();
    void reset();
};

#include "random_reader.h"
#include <algorithm>
#include <random>

EmptyFileException::EmptyFileException()
    : std::runtime_error("The file is empty!") {}

RandomReader::RandomReader(const std::string &filename, bool header) {
    rapidcsv::Document doc;

    if (header) {
        doc = rapidcsv::Document(filename);
    } else {
        doc = rapidcsv::Document(filename, rapidcsv::LabelParams(-1, -1));
    }

    if (doc.GetRowCount() <= 0) {
        throw EmptyFileException();
    }

    values = doc.GetColumn<double>(0);
    current_row = 0;
}

RandomReader::RandomReader(const std::string &filename, size_t n_rows,
                           bool header) {
    rapidcsv::Document doc;

    if (header) {
        doc = rapidcsv::Document(filename);
    } else {
        doc = rapidcsv::Document(filename, rapidcsv::LabelParams(-1, -1));
    }

    if (doc.GetRowCount() <= 0) {
        throw EmptyFileException();
    }

    values = doc.GetColumn<double>(0);
    if (n_rows < values.size()) {
        values.resize(n_rows);
    }

    current_row = 0;
}

double RandomReader::next() {
    if (current_row >= values.size()) {
        reset();
    }

    double result = values[current_row];
    current_row++;

    return result;
}

void RandomReader::reset() {
    current_row = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(values.begin(), values.end(), gen);
}

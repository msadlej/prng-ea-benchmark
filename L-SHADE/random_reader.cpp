#include "random_reader.h"

EmptyFileException::EmptyFileException()
    : std::runtime_error("The file is empty!") {}

RandomReader::RandomReader(const std::string &filename, bool header)
    : header(header) {
    current_row = header ? 1 : 0;

    if (header) {
        doc = rapidcsv::Document(filename);
    } else {
        doc = rapidcsv::Document(filename, rapidcsv::LabelParams(-1, -1));
    }

    if (doc.GetRowCount() <= current_row) {
        throw EmptyFileException();
    }
}

double RandomReader::next() {
    if (current_row >= doc.GetRowCount()) {
        reset();
    }

    double result = doc.GetCell<double>(0, current_row);
    current_row++;
    return result;
}

void RandomReader::reset() {
    size_t min_row = header ? 1 : 0;
    size_t max_row = doc.GetRowCount() - 1;
    size_t range = max_row - min_row + 1;

    current_row = min_row + (std::rand() % range);
}

#include "benchmark.h"

#include <algorithm>
#include <fstream>
#include <numeric>
#include <random>
#include <stdexcept>

namespace bench {

std::vector<int> make_shuffled(int n, unsigned seed) {
    std::vector<int> A(n);
    std::iota(A.begin(), A.end(), 1);
    std::mt19937 rng(seed);
    std::shuffle(A.begin(), A.end(), rng);
    return A;
}

void write_csv(const std::string& path,
               const std::vector<std::string>& header,
               const std::vector<std::vector<double>>& rows) {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("cannot open " + path);
    for (size_t i = 0; i < header.size(); ++i) {
        out << header[i];
        if (i + 1 < header.size()) out << ',';
    }
    out << '\n';
    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            out << row[i];
            if (i + 1 < row.size()) out << ',';
        }
        out << '\n';
    }
}

}  // namespace bench
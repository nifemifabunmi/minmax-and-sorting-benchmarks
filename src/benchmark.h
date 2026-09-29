#pragma once
#include <string>
#include <vector>

namespace bench {

std::vector<int> make_shuffled(int n, unsigned seed);

void write_csv(const std::string& path,
               const std::vector<std::string>& header,
               const std::vector<std::vector<double>>& rows);

}  // namespace bench
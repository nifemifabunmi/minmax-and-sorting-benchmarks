#pragma once
#include <utility>
#include <vector>

namespace algos {

struct MinMaxResult {
    long long comparisons;
    int min_value;
    int max_value;
};

MinMaxResult minmax_recursive(const std::vector<int>& A);
MinMaxResult minmax_iterative(const std::vector<int>& A);

}  // namespace algos
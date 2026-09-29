#pragma once
#include <vector>

namespace algos {

struct SelectResult {
    long long comparisons;
    int value;
};

SelectResult select_kth_smallest(std::vector<int> A, int k);

}  // namespace algos
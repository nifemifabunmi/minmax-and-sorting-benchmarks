#pragma once
#include <vector>

namespace algos {

struct SortResult {
    long long comparisons;
    bool      sorted_ok;
};

SortResult insertion_sort(std::vector<int> A);
SortResult selection_sort(std::vector<int> A);
SortResult merge_sort(std::vector<int> A);
SortResult quick_sort_fixed(std::vector<int> A);
SortResult quick_sort_median(std::vector<int> A);
SortResult heap_sort(std::vector<int> A);

}  // namespace algos
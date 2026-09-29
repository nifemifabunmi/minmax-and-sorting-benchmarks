#include "minmax.h"
#include "median.h"
#include "sorts.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

namespace {

std::vector<int> shuffled(int n, unsigned seed) {
    std::vector<int> A(n);
    std::iota(A.begin(), A.end(), 1);
    std::mt19937 rng(seed);
    std::shuffle(A.begin(), A.end(), rng);
    return A;
}

void test_minmax() {
    for (int n = 1; n <= 64; ++n) {
        auto A = shuffled(n, n);
        auto r1 = algos::minmax_recursive(A);
        auto r2 = algos::minmax_iterative(A);
        int lo = *std::min_element(A.begin(), A.end());
        int hi = *std::max_element(A.begin(), A.end());
        assert(r1.min_value == lo && r1.max_value == hi);
        assert(r2.min_value == lo && r2.max_value == hi);
    }
    std::cout << "[ok] minmax\n";
}

void test_sorts() {
    for (int n = 1; n <= 64; ++n) {
        auto A = shuffled(n, n * 7);
        auto check = [&](const char* name, algos::SortResult r) {
            if (!r.sorted_ok) {
                std::cerr << "FAIL " << name << " n=" << n << "\n";
                std::exit(1);
            }
        };
        check("insertion",    algos::insertion_sort(A));
        check("selection",    algos::selection_sort(A));
        check("merge",        algos::merge_sort(A));
        check("quick_fixed",  algos::quick_sort_fixed(A));
        check("quick_median", algos::quick_sort_median(A));
        check("heap",         algos::heap_sort(A));
    }
    std::cout << "[ok] sorts\n";
}

void test_median() {
    for (int n = 1; n <= 64; ++n) {
        auto A = shuffled(n, n * 13);
        auto sorted = A;
        std::sort(sorted.begin(), sorted.end());
        for (int k = 0; k < n; ++k) {
            auto r = algos::select_kth_smallest(A, k);
            if (r.value != sorted[k]) {
                std::cerr << "FAIL select n=" << n
                          << " k=" << k << "\n";
                std::exit(1);
            }
        }
    }
    std::cout << "[ok] median-select\n";
}

}  // namespace

int main() {
    test_minmax();
    test_sorts();
    test_median();
    std::cout << "All tests passed.\n";
    return 0;
}
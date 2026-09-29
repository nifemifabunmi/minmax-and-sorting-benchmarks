#include "benchmark.h"
#include "median.h"
#include "minmax.h"
#include "sorts.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace {

constexpr int TRIALS = 5;

double avg_minmax_rec(int n) {
    double total = 0;
    for (int t = 0; t < TRIALS; ++t) {
        auto A = bench::make_shuffled(n, 1000u + t);
        total += algos::minmax_recursive(A).comparisons;
    }
    return total / TRIALS;
}

double avg_minmax_iter(int n) {
    double total = 0;
    for (int t = 0; t < TRIALS; ++t) {
        auto A = bench::make_shuffled(n, 2000u + t);
        total += algos::minmax_iterative(A).comparisons;
    }
    return total / TRIALS;
}

template <typename Fn>
double avg_sort(int n, Fn fn) {
    double total = 0;
    for (int t = 0; t < TRIALS; ++t) {
        auto A = bench::make_shuffled(n, 3000u + t);
        auto r = fn(A);
        if (!r.sorted_ok) {
            std::cerr << "SORT FAILED at n=" << n << "\n";
            std::exit(1);
        }
        total += r.comparisons;
    }
    return total / TRIALS;
}

void run_minmax() {
    std::vector<std::vector<double>> rows;
    for (int n = 1; n <= 1000; ++n) {
        rows.push_back({
            double(n),
            avg_minmax_rec(n),
            avg_minmax_iter(n),
            1.5 * n - 2.0,
            2.0 * n - 3.0
        });
    }
    bench::write_csv("results/minmax_cost.csv",
        {"N", "recursive", "iterative", "1.5N-2", "2N-3"}, rows);
    std::cout << "[ok] results/minmax_cost.csv\n";
}

void run_sorts() {
    std::vector<std::vector<double>> rows;
    for (int n = 1; n <= 128; ++n) {
        rows.push_back({
            double(n),
            avg_sort(n, algos::insertion_sort),
            avg_sort(n, algos::selection_sort),
            avg_sort(n, algos::merge_sort),
            avg_sort(n, algos::quick_sort_fixed),
            avg_sort(n, algos::quick_sort_median),
            avg_sort(n, algos::heap_sort),
        });
    }
    bench::write_csv("results/sorts_cost.csv",
        {"N", "insertion", "selection", "merge",
         "quick_fixed", "quick_median", "heap"}, rows);
    std::cout << "[ok] results/sorts_cost.csv\n";
}

void run_median() {
    std::vector<std::vector<double>> rows;
    for (int n = 1; n <= 1000; ++n) {
        double total = 0;
        for (int t = 0; t < TRIALS; ++t) {
            auto A = bench::make_shuffled(n, 4000u + t);
            total += algos::select_kth_smallest(A, n / 2).comparisons;
        }
        rows.push_back({double(n), total / TRIALS, 10.0 * n});
    }
    bench::write_csv("results/median_cost.csv",
        {"N", "median_select", "10N"}, rows);
    std::cout << "[ok] results/median_cost.csv\n";
}

}  // namespace

int main() {
    std::cout << "Running benchmarks (" << TRIALS << " trials each)...\n";
    run_minmax();
    run_sorts();
    run_median();
    std::cout << "Done. Now run: python3 bench/plot.py\n";
    return 0;
}
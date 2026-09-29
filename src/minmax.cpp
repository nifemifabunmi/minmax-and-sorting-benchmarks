#include "minmax.h"

namespace algos {

namespace {

std::pair<int,int> rec(const std::vector<int>& A, int lo, int hi,
                       long long& cmps) {
    if (lo == hi) {
        return {A[lo], A[lo]};
    }
    if (hi == lo + 1) {
        ++cmps;
        if (A[lo] < A[hi]) return {A[lo], A[hi]};
        return {A[hi], A[lo]};
    }
    int mid = lo + (hi - lo) / 2;
    auto p1 = rec(A, lo, mid, cmps);
    auto p2 = rec(A, mid + 1, hi, cmps);
    int min1 = p1.first, max1 = p1.second;
    int min2 = p2.first, max2 = p2.second;
    ++cmps;
    int overall_min = (min1 < min2) ? min1 : min2;
    ++cmps;
    int overall_max = (max1 > max2) ? max1 : max2;
    return {overall_min, overall_max};
}

}  // namespace

MinMaxResult minmax_recursive(const std::vector<int>& A) {
    MinMaxResult r{0, 0, 0};
    if (A.empty()) return r;
    auto p = rec(A, 0, static_cast<int>(A.size()) - 1, r.comparisons);
    r.min_value = p.first;
    r.max_value = p.second;
    return r;
}

MinMaxResult minmax_iterative(const std::vector<int>& A) {
    MinMaxResult r{0, 0, 0};
    int n = static_cast<int>(A.size());
    if (n == 0) return r;
    if (n == 1) { r.min_value = r.max_value = A[0]; return r; }

    int mn, mx;
    ++r.comparisons;
    if (A[0] < A[1]) { mn = A[0]; mx = A[1]; }
    else             { mn = A[1]; mx = A[0]; }

    int i = 2;
    while (i + 1 < n) {
        ++r.comparisons;
        if (A[i] < A[i + 1]) {
            ++r.comparisons; if (A[i]     < mn) mn = A[i];
            ++r.comparisons; if (A[i + 1] > mx) mx = A[i + 1];
        } else {
            ++r.comparisons; if (A[i + 1] < mn) mn = A[i + 1];
            ++r.comparisons; if (A[i]     > mx) mx = A[i];
        }
        i += 2;
    }
    if (i < n) {
        ++r.comparisons; if (A[i] < mn) mn = A[i];
        ++r.comparisons; if (A[i] > mx) mx = A[i];
    }
    r.min_value = mn;
    r.max_value = mx;
    return r;
}

}  // namespace algos
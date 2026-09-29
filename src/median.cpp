#include "median.h"

#include <algorithm>

namespace algos {

namespace {

int select_impl(std::vector<int>& A, int lo, int hi, int k, long long& c);

int median_of_medians(std::vector<int>& A, int lo, int hi, long long& c) {
    int n = hi - lo + 1;
    if (n <= 5) {
        std::sort(A.begin() + lo, A.begin() + hi + 1);
        return A[lo + n / 2];
    }
    std::vector<int> meds;
    meds.reserve(n / 5 + 1);
    for (int i = lo; i <= hi; i += 5) {
        int r = std::min(i + 4, hi);
        std::sort(A.begin() + i, A.begin() + r + 1);
        meds.push_back(A[i + (r - i) / 2]);
    }
    return select_impl(meds, 0, (int)meds.size() - 1,
                       (int)meds.size() / 2, c);
}

int partition(std::vector<int>& A, int lo, int hi, int pivot, long long& c) {
    int pidx = lo;
    for (int i = lo; i <= hi; ++i)
        if (A[i] == pivot) { pidx = i; break; }
    std::swap(A[pidx], A[hi]);
    int i = lo - 1;
    for (int j = lo; j < hi; ++j)
        if (++c, A[j] <= pivot) std::swap(A[++i], A[j]);
    std::swap(A[i + 1], A[hi]);
    return i + 1;
}

int select_impl(std::vector<int>& A, int lo, int hi, int k, long long& c) {
    if (lo == hi) return A[lo];
    int med = median_of_medians(A, lo, hi, c);
    int p = partition(A, lo, hi, med, c);
    if (k == p) return A[p];
    if (k < p)  return select_impl(A, lo, p - 1, k, c);
    return select_impl(A, p + 1, hi, k, c);
}

}  // namespace

SelectResult select_kth_smallest(std::vector<int> A, int k) {
    SelectResult r{0, 0};
    if (A.empty() || k < 0 || k >= (int)A.size()) return r;
    r.value = select_impl(A, 0, (int)A.size() - 1, k, r.comparisons);
    return r;
}

}  // namespace algos
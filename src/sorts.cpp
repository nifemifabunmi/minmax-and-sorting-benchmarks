#include "sorts.h"

#include <algorithm>
#include <utility>

namespace algos {

namespace {

bool is_sorted(const std::vector<int>& A) {
    for (size_t i = 1; i < A.size(); ++i)
        if (A[i - 1] > A[i]) return false;
    return true;
}

void insertion(std::vector<int>& A, long long& c) {
    for (int i = 1; i < (int)A.size(); ++i) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && (++c, A[j] > key)) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}

void selection(std::vector<int>& A, long long& c) {
    int n = (int)A.size();
    for (int i = 0; i < n - 1; ++i) {
        int m = i;
        for (int j = i + 1; j < n; ++j)
            if (++c, A[j] < A[m]) m = j;
        std::swap(A[i], A[m]);
    }
}

void merge_(std::vector<int>& A, int lo, int mid, int hi,
            std::vector<int>& buf, long long& c) {
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        ++c;
        if (A[i] <= A[j]) buf[k++] = A[i++];
        else              buf[k++] = A[j++];
    }
    while (i <= mid) buf[k++] = A[i++];
    while (j <= hi)  buf[k++] = A[j++];
    for (int t = lo; t <= hi; ++t) A[t] = buf[t];
}
void merge_rec(std::vector<int>& A, int lo, int hi,
               std::vector<int>& buf, long long& c) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    merge_rec(A, lo, mid, buf, c);
    merge_rec(A, mid + 1, hi, buf, c);
    merge_(A, lo, mid, hi, buf, c);
}

int partition_last(std::vector<int>& A, int lo, int hi, long long& c) {
    int p = A[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; ++j)
        if (++c, A[j] <= p) std::swap(A[++i], A[j]);
    std::swap(A[i + 1], A[hi]);
    return i + 1;
}
void qs_fixed(std::vector<int>& A, int lo, int hi, long long& c) {
    if (lo >= hi) return;
    int p = partition_last(A, lo, hi, c);
    qs_fixed(A, lo, p - 1, c);
    qs_fixed(A, p + 1, hi, c);
}

int select_kth(std::vector<int>& A, int lo, int hi, int k, long long& c);

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
    return select_kth(meds, 0, (int)meds.size() - 1,
                      (int)meds.size() / 2, c);
}

int partition_pivot(std::vector<int>& A, int lo, int hi,
                    int pivot, long long& c) {
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

int select_kth(std::vector<int>& A, int lo, int hi, int k, long long& c) {
    if (lo == hi) return A[lo];
    int med = median_of_medians(A, lo, hi, c);
    int p = partition_pivot(A, lo, hi, med, c);
    if (k == p) return A[p];
    if (k < p)  return select_kth(A, lo, p - 1, k, c);
    return select_kth(A, p + 1, hi, k, c);
}

void qs_median(std::vector<int>& A, int lo, int hi, long long& c) {
    if (lo >= hi) return;
    int med = median_of_medians(A, lo, hi, c);
    int p = partition_pivot(A, lo, hi, med, c);
    qs_median(A, lo, p - 1, c);
    qs_median(A, p + 1, hi, c);
}

void sift_down(std::vector<int>& A, int n, int i, long long& c) {
    while (true) {
        int l = 2 * i + 1, r = 2 * i + 2, big = i;
        if (l < n && (++c, A[l] > A[big])) big = l;
        if (r < n && (++c, A[r] > A[big])) big = r;
        if (big == i) break;
        std::swap(A[i], A[big]);
        i = big;
    }
}
void heap_(std::vector<int>& A, long long& c) {
    int n = (int)A.size();
    for (int i = n / 2 - 1; i >= 0; --i) sift_down(A, n, i, c);
    for (int i = n - 1; i > 0; --i) {
        std::swap(A[0], A[i]);
        sift_down(A, i, 0, c);
    }
}

}  // namespace

SortResult insertion_sort(std::vector<int> A) {
    SortResult r{0, false};
    insertion(A, r.comparisons);
    r.sorted_ok = is_sorted(A);
    return r;
}
SortResult selection_sort(std::vector<int> A) {
    SortResult r{0, false};
    selection(A, r.comparisons);
    r.sorted_ok = is_sorted(A);
    return r;
}
SortResult merge_sort(std::vector<int> A) {
    SortResult r{0, false};
    std::vector<int> buf(A.size());
    if (!A.empty()) merge_rec(A, 0, (int)A.size() - 1, buf, r.comparisons);
    r.sorted_ok = is_sorted(A);
    return r;
}
SortResult quick_sort_fixed(std::vector<int> A) {
    SortResult r{0, false};
    if (!A.empty()) qs_fixed(A, 0, (int)A.size() - 1, r.comparisons);
    r.sorted_ok = is_sorted(A);
    return r;
}
SortResult quick_sort_median(std::vector<int> A) {
    SortResult r{0, false};
    if (!A.empty()) qs_median(A, 0, (int)A.size() - 1, r.comparisons);
    r.sorted_ok = is_sorted(A);
    return r;
}
SortResult heap_sort(std::vector<int> A) {
    SortResult r{0, false};
    heap_(A, r.comparisons);
    r.sorted_ok = is_sorted(A);
    return r;
}

}  // namespace algos
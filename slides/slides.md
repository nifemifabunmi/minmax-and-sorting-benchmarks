---
marp: true
theme: default
paginate: true
---

# MINMAX & Sorting Benchmarks

Comparison-based algorithm analysis in C++17

**Nifemi**

---

## The problem

- MINMAX: find min and max of N integers.
- Sorting: compare 6 classic algorithms.
- Count only element-vs-element comparisons.

---

## MINMAX: both forms hit the optimum

Recursive D&C: T(N) = 2T(N/2) + 2

Iterative paired scan: 1 + 3*(N/2)

Both reach 3N/2 - 2, the lower bound.

---

## Sorting results (N = 128)

| Rank | Algorithm         | Comparisons |
|------|-------------------|-------------|
| 1    | Merge sort        | ~700        |
| 2    | Quick (median)    | ~750        |
| 3    | Heap sort         | ~1400       |
| 4    | Quick (fixed)     | ~1250       |
| 5    | Insertion sort    | ~4100       |
| 6    | Selection sort    | ~8100       |

---

## Takeaways

1. D&C MINMAX is optimal but iteration matches it.
2. Fixed-pivot quicksort degrades to O(N^2) on sorted input.
3. Counting comparisons beats wall-clock timing for reproducibility.
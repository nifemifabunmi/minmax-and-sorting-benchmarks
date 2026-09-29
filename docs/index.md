---
layout: default
title: MINMAX & Sorting Benchmarks
---

# MINMAX & Sorting Benchmarks

**Comparison-based algorithm analysis in C++17** - divide-and-conquer vs.
iterative MINMAX, plus six sorting algorithms benchmarked by
element comparisons.

[**View on GitHub**](https://github.com/Nifemi/minmax-and-sorting-benchmarks)

## What is inside

- MINMAX in recursive D&C and iterative form, both hitting 3N/2 - 2.
- Six sorts from scratch: insertion, selection, merge, quicksort (fixed),
  quicksort (median pivot), heapsort.
- Median-of-medians SELECT implemented by hand.

## Build

    cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ./build/bench.exe
    python bench/plot.py

## License

MIT
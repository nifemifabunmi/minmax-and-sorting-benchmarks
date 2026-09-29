# MINMAX & Sorting Algorithm Benchmarks

Comparison-based algorithm analysis in C++17 - divide-and-conquer vs.
iterative MINMAX, plus six sorting algorithms benchmarked by
element comparisons (not wall-clock time).

## Highlights

- MINMAX in both recursive and iterative forms, both hitting the
  information-theoretic optimum 3N/2 - 2 comparisons.
- Six sorting algorithms from scratch: insertion, selection, merge,
  quicksort (fixed pivot), quicksort (median pivot), heapsort.
- Median-of-medians SELECT implemented by hand.
- Comparison counting rather than timing.

## Build & run

    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build -j
    ./build/bench
    python3 bench/plot.py

## License

MIT

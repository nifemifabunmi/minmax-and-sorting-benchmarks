#!/usr/bin/env python3
"""Generate all three result plots from the CSVs in results/."""
import os
import csv
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

RESULTS = os.path.join(os.path.dirname(__file__), "..", "results")

def read_csv(name):
    with open(os.path.join(RESULTS, name)) as f:
        r = csv.DictReader(f)
        cols = r.fieldnames
        data = {c: [] for c in cols}
        for row in r:
            for c in cols:
                data[c].append(float(row[c]))
    return data

def save(fig, name):
    for ext in ("png", "pdf"):
        fig.savefig(os.path.join(RESULTS, f"{name}.{ext}"),
                    bbox_inches="tight", dpi=150)
    plt.close(fig)
    print(f"[ok] results/{name}.png / .pdf")

def plot_minmax():
    d = read_csv("minmax_cost.csv")
    fig, ax = plt.subplots(figsize=(8, 5))
    ax.plot(d["N"], d["recursive"], label="recursive D&C", lw=1.5)
    ax.plot(d["N"], d["iterative"], label="iterative",     lw=1.5, ls="--")
    ax.plot(d["N"], d["1.5N-2"],    label="1.5N - 2",      lw=1,   ls=":")
    ax.plot(d["N"], d["2N-3"],      label="2N - 3",        lw=1,   ls="-.")
    ax.set_xlabel("Array size N")
    ax.set_ylabel("Element comparisons")
    ax.set_title("MINMAX: recursive vs. iterative vs. theoretical bounds")
    ax.legend()
    ax.grid(True, alpha=0.3)
    save(fig, "minmax_cost")

def plot_sorts():
    d = read_csv("sorts_cost.csv")
    fig, ax = plt.subplots(figsize=(9, 5.5))
    for col, label in [
        ("merge",        "Merge sort"),
        ("quick_median", "Quick sort (median pivot)"),
        ("heap",         "Heap sort"),
        ("quick_fixed",  "Quick sort (fixed pivot)"),
        ("insertion",    "Insertion sort"),
        ("selection",    "Selection sort"),
    ]:
        ax.plot(d["N"], d[col], label=label, lw=1.6)
    ax.set_xlabel("Array size N")
    ax.set_ylabel("Element comparisons")
    ax.set_title("Sorting algorithm comparison counts (random input)")
    ax.legend(fontsize=9)
    ax.grid(True, alpha=0.3)
    save(fig, "sorts_cost")

def plot_median():
    d = read_csv("median_cost.csv")
    fig, ax = plt.subplots(figsize=(8, 5))
    ax.plot(d["N"], d["median_select"], label="Median-of-medians SELECT", lw=1.6)
    ax.plot(d["N"], d["10N"],           label="10N", lw=1.2, ls="--")
    ax.set_xlabel("Array size N")
    ax.set_ylabel("Element comparisons")
    ax.set_title("Median-finding cost vs. 10N bound")
    ax.legend()
    ax.grid(True, alpha=0.3)
    save(fig, "median_cost")

if __name__ == "__main__":
    plot_minmax()
    plot_sorts()
    plot_median()
    print("All plots written to results/")
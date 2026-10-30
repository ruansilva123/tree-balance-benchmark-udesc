# Tree Balance Benchmark

A C benchmark that compares the performance of balanced trees on insertion and deletion, using the same set of random numbers for every structure.

The compared trees are AVL, B+, B*, Prefixed B+ and Red-Black.

## What is measured

For each tree, the program measures the time taken by:

- **Population:** inserting every element of the dataset.
- **Deletion:** removing the inserted elements.

Times are measured in milliseconds with `clock_gettime(CLOCK_MONOTONIC)`, which has nanosecond resolution and is not affected by adjustments to the system clock.

## Requirements

- GCC
- Make
- A POSIX-compatible system (Linux or macOS), because of `clock_gettime`

## How to build and run

To build:

```bash
make compilation
```

To build and run:

```bash
make run
```

On startup, the program asks whether to use the default dataset size (10,000 elements):

```
Do you want use default dataset size of 10000? (y/n):
```

Answer `y` to use the default or `n` to enter a different size. The value must be greater than zero.

## Project structure

```
.
├── makefile
└── src
    ├── main.c                 # Main benchmark flow
    ├── trees
    │   ├── avl/               # AVL tree
    │   ├── red_black/         # Red-Black tree
    │   └── btree/             # B-tree variants
    ├── utils/                 # Random dataset and time measurement
    └── validators/            # User input validation
```

## How it works

1. The user sets the dataset size.
2. The program generates an array of random numbers of that size.
3. For each tree, the same numbers are inserted and then removed, and the time of each step is measured separately.
4. At the end, the times for all trees are displayed for comparison.

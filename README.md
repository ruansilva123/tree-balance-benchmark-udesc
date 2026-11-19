# Tree Balance Benchmark

**English** | [Portuguese](README.pt-BR.md)

A C benchmark that compares the computational effort of balanced trees on insertion and deletion, including the balancing work, using the same random keys for every structure.

The compared trees are AVL, Red-Black and B-tree with orders 1, 5 and 10.

## What is measured

For every dataset size from 1 to 10,000 keys, the program measures the effort of:

- **Addition:** inserting every key of the dataset into an empty tree.
- **Removal:** removing every inserted key.

Each size is run with 10 different random datasets, and the result is the average of the 10 runs. All five trees receive the same dataset in each run.

### Computational effort

The effort is a counter (`effort`, in `src/utils/`) incremented by one at:

- every iteration of a loop inside an addition or removal (descending the tree, finding the successor or predecessor, walking up while balancing, shifting keys inside a B-tree node);
- every balancing operation (AVL and Red-Black rotations, B-tree split, merge and borrow, and each node visited by the B-tree recursion).

### Keys

Keys are generated with `rand() % (10 * n)`, where `n` is the dataset size. Repeated keys are ignored by every tree.

## Results

![Addition effort](public/addition_effort.png)

![Removal effort](public/removal_effort.png)

### Discussion

The table shows the average effort at the largest dataset size (10,000 keys) and the effort per key (total divided by 10,000):

| Tree | Addition | Per key | Removal | Per key |
|---|---|---|---|---|
| Red-Black | 135,012 | 13.5 | 124,727 | 12.5 |
| B-tree order 5 | 212,626 | 21.3 | 221,211 | 22.1 |
| B-tree order 10 | 236,045 | 23.6 | 256,772 | 25.7 |
| AVL | 241,491 | 24.1 | 221,105 | 22.1 |
| B-tree order 1 | 250,678 | 25.1 | 252,201 | 25.2 |

**Growth.** Every curve grows as `n log n`: the effort divided by `n log₂ n` stays almost constant between 1,000 and 10,000 keys (for example, 1.76 and 1.82 for AVL addition). This matches the expected `O(log n)` cost of a single addition or removal in a balanced tree, repeated `n` times. No structure degrades as the dataset grows; they differ by a constant factor.

**Red-Black is the cheapest in both operations**, with about 55% of the AVL effort. Both trees end with the same height (about 16 levels for 10,000 keys) and perform a similar number of rotations (AVL: 6,668 on addition; Red-Black: 5,550). The difference is in what happens after the change:

- The AVL implementation walks up from the changed node to the root on every operation, recomputing heights and balance factors: about 11 steps per addition and 10 per removal.
- The Red-Black fix-up loop only continues while there is a red-red conflict or a missing black node, which usually ends after 1 step: about 0.9 steps per addition and 0.7 per removal.

**AVL is more expensive on addition than on removal** (24.1 vs 22.1 per key). In both cases it walks up to the root, but addition performs almost twice as many rotations (6,668 vs 3,811).

**B-tree: the order trades height for work inside the node.**

- Order 1 (1 to 2 keys per node, a 2-3 tree) is the tallest, with 11 levels, and has the most splits (7,054) and underflow fixes (10,121). It spends its effort descending levels.
- Order 5 (5 to 10 keys per node) drops to 5 levels and is the cheapest B-tree in both operations.
- Order 10 (10 to 20 keys per node) only drops to 4 levels, but each addition or removal shifts twice as many keys inside the node, and each split, merge or borrow moves twice as many keys. This extra work outweighs the saved level, so order 10 ends above order 5, and in removal it is the most expensive of all trees.

The binary search inside the nodes costs about the same in all orders: fewer levels mean more comparisons per node, and the total stays close to `log₂ n` per key.

**Removal vs. addition in the B-tree.** Removal is slightly more expensive in every order, because an underflow requires borrowing from or merging with a sibling, and removing a key from an internal node requires finding its predecessor first.

**AVL vs. B-tree order 5 in removal.** Both reach almost the same effort at 10,000 keys (221,105 vs 221,211). The curves overlap in the removal chart, so neither is clearly better there.

### Notes on the results

- **The effort depends on the counting rule.** Counting only key comparisons, or every assignment, would change the curves. The rule used here is described in [Computational effort](#computational-effort).
- **The B-tree result is specific to memory.** Each node is already in memory, so shifting keys inside it has a real cost in this count. On disk, the dominant cost is reading each node, and moving keys inside a node already read is almost free. With that criterion, a higher order would win, because it has fewer levels.
- **AVL implementation.** This AVL always walks up to the root. An implementation that stops as soon as a node's height does not change would reduce its effort, especially on addition.
- **Repeated keys.** Keys come from `rand() % (10 * n)`, so about 5% of them repeat. Every tree ignores repeated keys, so all five process the same set.

## Requirements

- GCC
- Make
- Python 3 (only for the charts)

## How to build and run

To build:

```bash
make compilation
```

To build and run:

```bash
make run
```

The program runs without any input and prints its progress every 500 sizes. Each run creates a new file `src/results/results_<date>_<time>.csv` (ignored by git), with one line per dataset size:

```
dataset_size,avl_add,red_black_add,btree_1_add,btree_5_add,btree_10_add,avl_remove,red_black_remove,btree_1_remove,btree_5_remove,btree_10_remove
```

## Charts

To generate the charts from the most recent results file:

```bash
make plot
```

On the first run, the command creates a Python virtual environment (`.venv`) and installs `pandas` and `matplotlib` from `requirements.txt`. The script `scripts/plot_results.py` reads the latest `src/results/results_*.csv` and overwrites `public/addition_effort.png` and `public/removal_effort.png`, so the images in the Results section are always up to date.

## Project structure

```
.
├── makefile
├── requirements.txt           # Python dependencies for the charts
├── public/                    # Charts used in the README
├── scripts/
│   └── plot_results.py        # Generates the charts
└── src
    ├── results/               # Results (CSV)
    ├── main.c                 # Main benchmark flow
    ├── trees
    │   ├── avl/               # AVL tree
    │   ├── red_black/         # Red-Black tree
    │   └── btree/             # B-tree
    └── utils/                 # Random keys and effort counter
```

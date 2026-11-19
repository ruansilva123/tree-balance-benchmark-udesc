from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd


ROOT = Path(__file__).resolve().parent.parent
RESULTS_DIR = ROOT / "src" / "results"
PUBLIC_DIR = ROOT / "public"

TREES = [
    ("avl", "AVL", "#2a78d6"),
    ("red_black", "Red-Black", "#eb6834"),
    ("btree_1", "B-tree order 1", "#1baf7a"),
    ("btree_5", "B-tree order 5", "#eda100"),
    ("btree_10", "B-tree order 10", "#e87ba4"),
]

CHARTS = [
    ("add", "Addition", "addition_effort.png"),
    ("remove", "Removal", "removal_effort.png"),
]


def latest_results_file():
    files = sorted(RESULTS_DIR.glob("results_*.csv"))
    if not files:
        raise SystemExit(f"No results file found in {RESULTS_DIR}. Run 'make run' first.")
    return files[-1]


def plot(data, operation, title, file_name):
    fig, ax = plt.subplots(figsize=(10, 5.5))

    for column, label, color in TREES:
        ax.plot(data["dataset_size"], data[f"{column}_{operation}"], label=label, color=color, linewidth=2)

    ax.set_title(f"{title}: computational effort by dataset size", loc="left", fontsize=14, fontweight="bold")
    ax.set_xlabel("Dataset size (keys)")
    ax.set_ylabel("Average effort (10 samples)")
    ax.set_xlim(0, data["dataset_size"].max())
    ax.set_ylim(bottom=0)
    ax.yaxis.set_major_formatter(lambda value, _: f"{value:,.0f}")
    ax.xaxis.set_major_formatter(lambda value, _: f"{value:,.0f}")
    ax.grid(axis="y", color="#e8e7e3")
    ax.spines[["top", "right"]].set_visible(False)
    ax.legend(frameon=False)

    fig.tight_layout()
    fig.savefig(PUBLIC_DIR / file_name, dpi=150)
    plt.close(fig)


def main():
    results_file = latest_results_file()
    print(f"Reading {results_file.relative_to(ROOT)}")

    data = pd.read_csv(results_file)
    PUBLIC_DIR.mkdir(exist_ok=True)

    for operation, title, file_name in CHARTS:
        plot(data, operation, title, file_name)
        print(f"Saved public/{file_name}")


if __name__ == "__main__":
    main()

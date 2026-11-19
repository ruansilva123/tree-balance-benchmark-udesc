VENV = .venv
PYTHON = $(VENV)/bin/python

compilation:
	gcc -Wall -Wextra -O2 -I. \
		src/main.c \
		src/utils/utils.c \
		src/trees/avl/avl.c \
		src/trees/red_black/red_black.c \
		src/trees/btree/btree.c -o main

run: compilation
	./main

$(VENV): requirements.txt
	python3 -m venv $(VENV)
	$(PYTHON) -m pip install -r requirements.txt
	touch $(VENV)

plot: $(VENV)
	$(PYTHON) scripts/plot_results.py

compilation:
	gcc -Wall -Wextra -I. src/main.c src/utils/utils.c src/validators/validators.c src/trees/avl/avl.c src/trees/red_black/red_black.c -o main

run: compilation
	./main
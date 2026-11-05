compilation:
	gcc -Wall -Wextra -I. src/main.c src/utils/utils.c src/validators/validators.c src/trees/avl/avl.c -o main

run: compilation
	./main
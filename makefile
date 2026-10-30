compilation:
	gcc -Wall -Wextra -I. src/main.c src/utils/utils.c src/validators/validators.c -o main

run: compilation
	./main
// libs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// project
#include "./utils.h"


long long effort = 0;


void random_numbers_set(int* random_numbers, int dataset_size) {
    for (int i = 0; i < dataset_size; i++) {
        random_numbers[i] = rand() % (dataset_size * 10);
    }
}


FILE* create_results_file() {
    time_t now = time(NULL);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d_%H-%M-%S", localtime(&now));

    char file_path[256];
    snprintf(file_path, sizeof(file_path), "src/results/results_%s.csv", timestamp);

    FILE* file = fopen(file_path, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return NULL;
    }

    fprintf(file, "dataset_size,avl_add,red_black_add,btree_1_add,btree_5_add,btree_10_add,");
    fprintf(file, "avl_remove,red_black_remove,btree_1_remove,btree_5_remove,btree_10_remove\n");

    printf("Saving results in %s\n", file_path);
    return file;
}

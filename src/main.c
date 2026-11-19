// libs
#include <stdio.h>
#include <stdlib.h>
// project
#include "utils/utils.h"
#include "trees/avl/avl.h"
#include "trees/red_black/red_black.h"
#include "trees/btree/btree.h"


#define MAX_DATASET_SIZE 10000
#define SAMPLES 10


int main() {
    int* random_numbers = (int*)malloc(MAX_DATASET_SIZE * sizeof(int));

    FILE* file = create_results_file();
    if (file == NULL) {
        return 1;
    }

    for (int dataset_size = 1; dataset_size <= MAX_DATASET_SIZE; dataset_size++) {
        long long avl_add = 0, avl_remove = 0;
        long long red_black_add = 0, red_black_remove = 0;
        long long btree_1_add = 0, btree_1_remove = 0;
        long long btree_5_add = 0, btree_5_remove = 0;
        long long btree_10_add = 0, btree_10_remove = 0;

        for (int sample = 0; sample < SAMPLES; sample++) {
            random_numbers_set(random_numbers, dataset_size);

            // ==== AVL TREE ====
            AVLTree* avl_tree = avl_create_tree();
            effort = 0;
            avl_set_random_numbers(avl_tree, random_numbers, dataset_size);
            avl_add += effort;
            effort = 0;
            avl_remove_random_numbers(avl_tree, random_numbers, dataset_size);
            avl_remove += effort;
            free(avl_tree);

            // ==== RED-BLACK TREE ====
            RedBlackTree* red_black_tree = red_black_create_tree();
            effort = 0;
            red_black_set_random_numbers(red_black_tree, random_numbers, dataset_size);
            red_black_add += effort;
            effort = 0;
            red_black_remove_random_numbers(red_black_tree, random_numbers, dataset_size);
            red_black_remove += effort;
            free(red_black_tree);

            // ==== B-TREE ORDER 1 ====
            BTree* btree_1 = btree_create_tree(1);
            effort = 0;
            btree_set_random_numbers(btree_1, random_numbers, dataset_size);
            btree_1_add += effort;
            effort = 0;
            btree_remove_random_numbers(btree_1, random_numbers, dataset_size);
            btree_1_remove += effort;
            free(btree_1);

            // ==== B-TREE ORDER 5 ====
            BTree* btree_5 = btree_create_tree(5);
            effort = 0;
            btree_set_random_numbers(btree_5, random_numbers, dataset_size);
            btree_5_add += effort;
            effort = 0;
            btree_remove_random_numbers(btree_5, random_numbers, dataset_size);
            btree_5_remove += effort;
            free(btree_5);

            // ==== B-TREE ORDER 10 ====
            BTree* btree_10 = btree_create_tree(10);
            effort = 0;
            btree_set_random_numbers(btree_10, random_numbers, dataset_size);
            btree_10_add += effort;
            effort = 0;
            btree_remove_random_numbers(btree_10, random_numbers, dataset_size);
            btree_10_remove += effort;
            free(btree_10);
        }

        fprintf(file, "%d,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",
            dataset_size,
            (double)avl_add / SAMPLES, (double)red_black_add / SAMPLES,
            (double)btree_1_add / SAMPLES, (double)btree_5_add / SAMPLES, (double)btree_10_add / SAMPLES,
            (double)avl_remove / SAMPLES, (double)red_black_remove / SAMPLES,
            (double)btree_1_remove / SAMPLES, (double)btree_5_remove / SAMPLES, (double)btree_10_remove / SAMPLES
        );

        if (dataset_size % 500 == 0) {
            printf("Progress: %d/%d\n", dataset_size, MAX_DATASET_SIZE);
        }
    }

    fclose(file);
    free(random_numbers);
    return 0;
}

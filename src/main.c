// libs
#include <stdio.h>
// project
#include "utils/utils.h"
#include "trees/avl/avl.h"
#include "trees/red_black/red_black.h"


int dataset_size = 10000;
int *random_numbers = NULL;


int main() {
    set_dataset_size(&dataset_size);
    random_numbers_set(&random_numbers, dataset_size);

    // ==== AVL TREE ====
    AVLTree* avl_tree = avl_create_tree();
    TreeExecutionData avl_tree_data;
    start_execution_time(&avl_tree_data.population);
    avl_set_random_numbers(avl_tree, random_numbers, dataset_size);
    stop_execution_time(&avl_tree_data.population);
    start_execution_time(&avl_tree_data.deletion);
    avl_remove_random_numbers(avl_tree, random_numbers, dataset_size);
    stop_execution_time(&avl_tree_data.deletion);
    log_results("AVL TREE", &avl_tree_data);

    // ==== B-TREE VARIANTS ====
    // B+
    TreeExecutionData bplus_tree_data;
    start_execution_time(&bplus_tree_data.population);
    // add population here
    stop_execution_time(&bplus_tree_data.population);
    start_execution_time(&bplus_tree_data.deletion);
    // add deletion here
    stop_execution_time(&bplus_tree_data.deletion);

    // B*
    TreeExecutionData bstar_tree_data;
    start_execution_time(&bstar_tree_data.population);
    // add population here
    stop_execution_time(&bstar_tree_data.population);
    start_execution_time(&bstar_tree_data.deletion);
    // add deletion here
    stop_execution_time(&bstar_tree_data.deletion);

    // Prefixed B+
    TreeExecutionData prefixed_bplus_tree_data;
    start_execution_time(&prefixed_bplus_tree_data.population);
    // add population here
    stop_execution_time(&prefixed_bplus_tree_data.population);
    start_execution_time(&prefixed_bplus_tree_data.deletion);
    // add deletion here
    stop_execution_time(&prefixed_bplus_tree_data.deletion);

    // ==== RED-BLACK TREE ====
    RedBlackTree* red_black_tree = red_black_create_tree();
    TreeExecutionData red_black_tree_data;
    start_execution_time(&red_black_tree_data.population);
    red_black_set_random_numbers(red_black_tree, random_numbers, dataset_size);
    stop_execution_time(&red_black_tree_data.population);
    start_execution_time(&red_black_tree_data.deletion);
    red_black_remove_random_numbers(red_black_tree, random_numbers, dataset_size);
    stop_execution_time(&red_black_tree_data.deletion);
    log_results("RED BLACK TREE", &red_black_tree_data);

    return 0;
}
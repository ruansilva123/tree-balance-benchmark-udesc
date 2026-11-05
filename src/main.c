// libs
#include <stdio.h>
// project
#include "utils/utils.h"
#include "trees/avl/avl.h"


int dataset_size = 10000;
int *random_numbers = NULL;


int main() {
    set_dataset_size(&dataset_size);
    random_numbers_set(&random_numbers, dataset_size);

    // ==== AVL TREE ====
    AVLTree* avl_tree = create_avl_tree();
    TreeExecutionData avl_tree_data;
    start_execution_time(&avl_tree_data.population);
    set_random_numbers(avl_tree, random_numbers, dataset_size);
    stop_execution_time(&avl_tree_data.population);
    start_execution_time(&avl_tree_data.deletion);
    remove_random_numbers(avl_tree, random_numbers, dataset_size);
    stop_execution_time(&avl_tree_data.deletion);

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
    TreeExecutionData red_black_tree_data;
    start_execution_time(&red_black_tree_data.population);
    // add population here
    stop_execution_time(&red_black_tree_data.population);
    start_execution_time(&red_black_tree_data.deletion);
    // add deletion here
    stop_execution_time(&red_black_tree_data.deletion);

    return 0;
}
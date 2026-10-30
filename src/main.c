// libs
#include <stdio.h>
// project
#include "utils/utils.h"


int dataset_size = 10000;
int *random_numbers = NULL;


int main() {
    set_dataset_size(&dataset_size);
    random_numbers_set(&random_numbers, dataset_size);

    // ==== AVL TREE ====
    TreeExecutionData avl_tree;
    start_execution_time(&avl_tree.population);
    // add population here
    stop_execution_time(&avl_tree.population);
    start_execution_time(&avl_tree.deletion);
    // add deletion here
    stop_execution_time(&avl_tree.deletion);

    // ==== B-TREE VARIANTS ====
    // B+
    TreeExecutionData bplus_tree;
    start_execution_time(&bplus_tree.population);
    // add population here
    stop_execution_time(&bplus_tree.population);
    start_execution_time(&bplus_tree.deletion);
    // add deletion here
    stop_execution_time(&bplus_tree.deletion);

    // B*
    TreeExecutionData bstar_tree;
    start_execution_time(&bstar_tree.population);
    // add population here
    stop_execution_time(&bstar_tree.population);
    start_execution_time(&bstar_tree.deletion);
    // add deletion here
    stop_execution_time(&bstar_tree.deletion);

    // Prefixed B+
    TreeExecutionData prefixed_bplus_tree;
    start_execution_time(&prefixed_bplus_tree.population);
    // add population here
    stop_execution_time(&prefixed_bplus_tree.population);
    start_execution_time(&prefixed_bplus_tree.deletion);
    // add deletion here
    stop_execution_time(&prefixed_bplus_tree.deletion);

    // ==== RED-BLACK TREE ====
    TreeExecutionData red_black_tree;
    start_execution_time(&red_black_tree.population);
    // add population here
    stop_execution_time(&red_black_tree.population);
    start_execution_time(&red_black_tree.deletion);
    // add deletion here
    stop_execution_time(&red_black_tree.deletion);

    return 0;
}
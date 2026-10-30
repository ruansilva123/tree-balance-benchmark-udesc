//libs
#include <stdlib.h>
// project
#include "./avl.h"


AVLTree* create_avl_tree() {
    AVLTree *tree = (AVLTree*)malloc(sizeof(AVLTree));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    return tree;
}
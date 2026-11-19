//libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// project
#include "../../utils/utils.h"
#include "./red_black.h"


RedBlackTree* red_black_create_tree() {
    RedBlackTree *tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    return tree;
}


void red_black_add_node(RedBlackTree* tree, int value) {
    RedBlackNode* node = tree->root;

    while (node != NULL) {
        effort++;
        if (value > node->value) {
            if (node->right != NULL) {
                node = node->right;
            } else {
                break;
            }
        } else if (value < node->value) {
            if (node->left != NULL) {
                node = node->left;
            } else {
                break;
            }
        } else {
            return;
        }
    }

    RedBlackNode* new_node = (RedBlackNode*)malloc(sizeof(RedBlackNode));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed for new node.\n");
        return;
    }
    new_node->value = value;
    new_node->father = node;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->color = RED;

    if (node == NULL) {
        tree->root = new_node;
    } else {
        if (value > node->value) {
            node->right = new_node;
        } else {
            node->left = new_node;
        }
    }

    red_black_add_balance(tree, new_node);
}


void red_black_remove_node(RedBlackTree* tree, int value) {
    RedBlackNode* node = tree->root;

    while (node != NULL && node->value != value) {
        effort++;
        if (value > node->value) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (node == NULL) {
        return;
    }

    if (node->left != NULL && node->right != NULL) {
        RedBlackNode* successor = node->right;
        while (successor->left != NULL) {
            effort++;
            successor = successor->left;
        }
        node->value = successor->value;
        node = successor;
    }

    RedBlackNode* child = node->left != NULL ? node->left : node->right;
    RedBlackNode* father = node->father;

    if (child != NULL) {
        child->father = father;
    }

    if (father == NULL) {
        tree->root = child;
    } else {
        if (father->left == node) {
            father->left = child;
        } else {
            father->right = child;
        }
    }

    if (node->color == BLACK) {
        red_black_remove_balance(tree, child, father);
    }

    free(node);
}


void red_black_add_balance(RedBlackTree* tree, RedBlackNode* node) {
    while (node != tree->root && node->father->color == RED) {
        effort++;
        RedBlackNode* father = node->father;
        RedBlackNode* grandfather = father->father;

        if (father == grandfather->left) {
            RedBlackNode* uncle = grandfather->right;

            if (!red_black_is_black(uncle)) {
                father->color = BLACK;
                uncle->color = BLACK;
                grandfather->color = RED;
                node = grandfather;
            } else {
                if (node == father->right) {
                    node = father;
                    red_black_left_rotation(tree, node);
                }
                node->father->color = BLACK;
                grandfather->color = RED;
                red_black_right_rotation(tree, grandfather);
            }
        } else {
            RedBlackNode* uncle = grandfather->left;

            if (!red_black_is_black(uncle)) {
                father->color = BLACK;
                uncle->color = BLACK;
                grandfather->color = RED;
                node = grandfather;
            } else {
                if (node == father->left) {
                    node = father;
                    red_black_right_rotation(tree, node);
                }
                node->father->color = BLACK;
                grandfather->color = RED;
                red_black_left_rotation(tree, grandfather);
            }
        }
    }
    tree->root->color = BLACK;
}


void red_black_remove_balance(RedBlackTree* tree, RedBlackNode* node, RedBlackNode* father) {
    while (node != tree->root && red_black_is_black(node)) {
        effort++;
        if (node == father->left) {
            RedBlackNode* sibling = father->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                father->color = RED;
                red_black_left_rotation(tree, father);
                sibling = father->right;
            }

            if (red_black_is_black(sibling->left) && red_black_is_black(sibling->right)) {
                sibling->color = RED;
                node = father;
                father = node->father;
            } else {
                if (red_black_is_black(sibling->right)) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    red_black_right_rotation(tree, sibling);
                    sibling = father->right;
                }
                sibling->color = father->color;
                father->color = BLACK;
                if (sibling->right != NULL) {
                    sibling->right->color = BLACK;
                }
                red_black_left_rotation(tree, father);
                node = tree->root;
            }
        } else {
            RedBlackNode* sibling = father->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                father->color = RED;
                red_black_right_rotation(tree, father);
                sibling = father->left;
            }

            if (red_black_is_black(sibling->left) && red_black_is_black(sibling->right)) {
                sibling->color = RED;
                node = father;
                father = node->father;
            } else {
                if (red_black_is_black(sibling->left)) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    red_black_left_rotation(tree, sibling);
                    sibling = father->left;
                }
                sibling->color = father->color;
                father->color = BLACK;
                if (sibling->left != NULL) {
                    sibling->left->color = BLACK;
                }
                red_black_right_rotation(tree, father);
                node = tree->root;
            }
        }
    }

    if (node != NULL) {
        node->color = BLACK;
    }
}


bool red_black_is_black(RedBlackNode* node) {
    return node == NULL || node->color == BLACK;
}


void red_black_left_rotation(RedBlackTree* tree, RedBlackNode* node) {
    effort++;
    RedBlackNode* father = node->father;
    RedBlackNode* right = node->right;

    if (right->left != NULL) {
        right->left->father = node;
    }

    node->right = right->left;
    node->father = right;

    right->left = node;
    right->father = father;

    if (father == NULL) {
        tree->root = right;
    } else {
        if (father->left == node) {
            father->left = right;
        } else {
            father->right = right;
        }
    }
}


void red_black_right_rotation(RedBlackTree* tree, RedBlackNode* node) {
    effort++;
    RedBlackNode* father = node->father;
    RedBlackNode* left = node->left;

    if (left->right != NULL) {
        left->right->father = node;
    }

    node->left = left->right;
    node->father = left;

    left->right = node;
    left->father = father;

    if (father == NULL) {
        tree->root = left;
    } else {
        if (father->left == node) {
            father->left = left;
        } else {
            father->right = left;
        }
    }
}


void red_black_set_random_numbers(RedBlackTree* tree, int* random_numbers, int dataset_size) {
    for (int i = 0; i < dataset_size; i++) {
        red_black_add_node(tree, random_numbers[i]);
    }
}


void red_black_remove_random_numbers(RedBlackTree* tree, int* random_numbers, int dataset_size) {
    for (int i = 0; i < dataset_size; i++) {
        red_black_remove_node(tree, random_numbers[i]);
    }
}

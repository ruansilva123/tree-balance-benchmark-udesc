//libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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


bool empty_tree(AVLTree *tree) {
    return tree->root == NULL;
}


void add_node(AVLTree* tree, int value) {
    Node* node = tree->root;

    while (node != NULL) {
        if (value > node->value) {
            if (node->right != NULL) {
                node = node->right;
            } else {
                break;
            }
        } else {
            if (node->left != NULL) {
                node = node->left;
            } else {
                break;
            }
        }
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed for new node.\n");
        return;
    }
    new_node->value = value;
    new_node->father = node;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;

    if (node == NULL) {
        tree->root = new_node;
    } else {
        if (value > node->value) {
            node->right = new_node;
        } else {
            node->left = new_node;
        }

        balance(tree, node);
    }
}


void remove_node(AVLTree* tree, int value) {
    Node* node = tree->root;

    while (node != NULL && node->value != value) {
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
        Node* successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        node->value = successor->value;
        node = successor;
    }

    Node* child = node->left != NULL ? node->left : node->right;
    Node* father = node->father;

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

    free(node);
    balance(tree, father);
}


void balance(AVLTree* tree, Node* node) {
    while (node != NULL) {
        int left_height = get_height(node->left);
        int right_height = get_height(node->right);
        node->height = 1 + (left_height > right_height ? left_height : right_height);

        int factor = balance_factor(node);

        if (factor > 1) {
            if (balance_factor(node->left) >= 0) {
                node = simple_right_rotation(node, tree);
            } else {
                node = double_right_rotation(node, tree);
            }
        } else if (factor < -1) {
            if (balance_factor(node->right) <= 0) {
                node = simple_left_rotation(node, tree);
            } else {
                node = double_left_rotation(node, tree);
            }
        }

        node = node->father;
    }
}


int get_height(Node* node) {
    return node == NULL ? 0 : node->height;
}


int balance_factor(Node* node) {
    int left = 0, right = 0;
    if (node->left != NULL) {
        left = node->left->height;
    }
    if (node->right != NULL) {
        right = node->right->height;
    }
    return left - right;
}


Node* simple_left_rotation(Node* node, AVLTree* tree) {
    Node* father = node->father;
    Node* right = node->right;

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

    node->height = 1 + (get_height(node->left) > get_height(node->right) ? get_height(node->left) : get_height(node->right));
    right->height = 1 + (get_height(right->left) > get_height(right->right) ? get_height(right->left) : get_height(right->right));
    return right;
}


Node* simple_right_rotation(Node* node, AVLTree* tree) {
    Node* father = node->father;
    Node* left = node->left;

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

    node->height = 1 + (get_height(node->left) > get_height(node->right) ? get_height(node->left) : get_height(node->right));
    left->height = 1 + (get_height(left->left) > get_height(left->right) ? get_height(left->left) : get_height(left->right));
    return left;
}


Node* double_left_rotation(Node* node, AVLTree* tree) {
    node->right = simple_right_rotation(node->right, tree);
    return simple_left_rotation(node, tree);
}


Node* double_right_rotation(Node* node, AVLTree* tree) {
    node->left = simple_left_rotation(node->left, tree);
    return simple_right_rotation(node, tree);
}


void set_random_numbers(AVLTree* tree, int* random_numbers, int dataset_size) {
    for (int i = 0; i < dataset_size; i++) {
        add_node(tree, random_numbers[i]);
    }
}


void remove_random_numbers(AVLTree* tree, int* random_numbers, int dataset_size) {
    for (int i = 0; i < dataset_size; i++) {
        remove_node(tree, random_numbers[i]);
    }
}
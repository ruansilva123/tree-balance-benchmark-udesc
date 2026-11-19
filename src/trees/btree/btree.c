//libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// project
#include "../../utils/utils.h"
#include "./btree.h"


BTree* btree_create_tree(int order) {
    BTree *tree = (BTree*)malloc(sizeof(BTree));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    tree->order = order;
    return tree;
}


BTreeNode* btree_create_node(int order, bool leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    if (node == NULL) {
        printf("Error: Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    node->keys = (int*)malloc((2 * order + 1) * sizeof(int));
    node->children = leaf ? NULL : (BTreeNode**)malloc((2 * order + 2) * sizeof(BTreeNode*));
    node->total = 0;
    node->leaf = leaf;
    return node;
}


void btree_free_node(BTreeNode* node) {
    free(node->keys);
    free(node->children);
    free(node);
}


int btree_binary_search(BTreeNode* node, int value) {
    int start = 0, end = node->total;

    while (start < end) {
        effort++;
        int middle = (start + end) / 2;
        if (node->keys[middle] <= value) {
            start = middle + 1;
        } else {
            end = middle;
        }
    }
    return start;
}


void btree_add_node(BTree* tree, int value) {
    if (tree->root == NULL) {
        tree->root = btree_create_node(tree->order, true);
    }

    int promoted;
    BTreeNode* right = btree_add_recursive(tree, tree->root, value, &promoted);

    if (right != NULL) {
        BTreeNode* root = btree_create_node(tree->order, false);
        root->keys[0] = promoted;
        root->children[0] = tree->root;
        root->children[1] = right;
        root->total = 1;
        tree->root = root;
    }
}


BTreeNode* btree_add_recursive(BTree* tree, BTreeNode* node, int value, int* promoted) {
    effort++;
    int index = btree_binary_search(node, value);

    if (index > 0 && node->keys[index - 1] == value) {
        return NULL;
    }

    if (node->leaf) {
        for (int i = node->total; i > index; i--) {
            effort++;
            node->keys[i] = node->keys[i - 1];
        }
        node->keys[index] = value;
        node->total++;
    } else {
        int child_promoted;
        BTreeNode* right = btree_add_recursive(tree, node->children[index], value, &child_promoted);
        if (right == NULL) {
            return NULL;
        }
        for (int i = node->total; i > index; i--) {
            effort++;
            node->keys[i] = node->keys[i - 1];
            node->children[i + 1] = node->children[i];
        }
        node->keys[index] = child_promoted;
        node->children[index + 1] = right;
        node->total++;
    }

    if (node->total <= 2 * tree->order) {
        return NULL;
    }
    return btree_split_node(tree, node, promoted);
}


BTreeNode* btree_split_node(BTree* tree, BTreeNode* node, int* promoted) {
    effort++;
    BTreeNode* right = btree_create_node(tree->order, node->leaf);
    int middle = tree->order;

    right->total = node->total - middle - 1;
    for (int i = 0; i < right->total; i++) {
        effort++;
        right->keys[i] = node->keys[middle + 1 + i];
    }
    if (!node->leaf) {
        for (int i = 0; i <= right->total; i++) {
            effort++;
            right->children[i] = node->children[middle + 1 + i];
        }
    }

    *promoted = node->keys[middle];
    node->total = middle;
    return right;
}


void btree_remove_node(BTree* tree, int value) {
    if (tree->root == NULL) {
        return;
    }

    btree_remove_recursive(tree, tree->root, value);

    BTreeNode* root = tree->root;
    if (root->total == 0) {
        tree->root = root->leaf ? NULL : root->children[0];
        btree_free_node(root);
    }
}


void btree_remove_recursive(BTree* tree, BTreeNode* node, int value) {
    effort++;
    int index = btree_binary_search(node, value);
    bool found = index > 0 && node->keys[index - 1] == value;

    if (node->leaf) {
        if (!found) {
            return;
        }
        for (int i = index - 1; i < node->total - 1; i++) {
            effort++;
            node->keys[i] = node->keys[i + 1];
        }
        node->total--;
        return;
    }

    if (found) {
        index--;
        BTreeNode* predecessor = node->children[index];
        while (!predecessor->leaf) {
            effort++;
            predecessor = predecessor->children[predecessor->total];
        }
        value = predecessor->keys[predecessor->total - 1];
        node->keys[index] = value;
    }

    btree_remove_recursive(tree, node->children[index], value);

    if (node->children[index]->total < tree->order) {
        btree_balance(tree, node, index);
    }
}


void btree_balance(BTree* tree, BTreeNode* father, int index) {
    effort++;
    BTreeNode* node = father->children[index];
    BTreeNode* left = index > 0 ? father->children[index - 1] : NULL;
    BTreeNode* right = index < father->total ? father->children[index + 1] : NULL;

    if (left != NULL && left->total > tree->order) {
        for (int i = node->total; i > 0; i--) {
            effort++;
            node->keys[i] = node->keys[i - 1];
        }
        if (!node->leaf) {
            for (int i = node->total + 1; i > 0; i--) {
                effort++;
                node->children[i] = node->children[i - 1];
            }
            node->children[0] = left->children[left->total];
        }
        node->keys[0] = father->keys[index - 1];
        father->keys[index - 1] = left->keys[left->total - 1];
        node->total++;
        left->total--;
    } else if (right != NULL && right->total > tree->order) {
        node->keys[node->total] = father->keys[index];
        father->keys[index] = right->keys[0];
        if (!node->leaf) {
            node->children[node->total + 1] = right->children[0];
            for (int i = 0; i < right->total; i++) {
                effort++;
                right->children[i] = right->children[i + 1];
            }
        }
        for (int i = 0; i < right->total - 1; i++) {
            effort++;
            right->keys[i] = right->keys[i + 1];
        }
        node->total++;
        right->total--;
    } else if (left != NULL) {
        btree_merge(father, index - 1);
    } else {
        btree_merge(father, index);
    }
}


void btree_merge(BTreeNode* father, int index) {
    effort++;
    BTreeNode* left = father->children[index];
    BTreeNode* right = father->children[index + 1];

    left->keys[left->total] = father->keys[index];
    for (int i = 0; i < right->total; i++) {
        effort++;
        left->keys[left->total + 1 + i] = right->keys[i];
    }
    if (!left->leaf) {
        for (int i = 0; i <= right->total; i++) {
            effort++;
            left->children[left->total + 1 + i] = right->children[i];
        }
    }
    left->total += right->total + 1;

    for (int i = index; i < father->total - 1; i++) {
        effort++;
        father->keys[i] = father->keys[i + 1];
        father->children[i + 1] = father->children[i + 2];
    }
    father->total--;
    btree_free_node(right);
}


void btree_set_random_numbers(BTree* tree, int* random_numbers, int dataset_size) {
    for (int i = 0; i < dataset_size; i++) {
        btree_add_node(tree, random_numbers[i]);
    }
}


void btree_remove_random_numbers(BTree* tree, int* random_numbers, int dataset_size) {
    for (int i = 0; i < dataset_size; i++) {
        btree_remove_node(tree, random_numbers[i]);
    }
}

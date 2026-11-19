// libs
#include <stdbool.h>


typedef struct BTreeNode {
    struct BTreeNode **children;
    int *keys;
    int total;
    bool leaf;
} BTreeNode;

typedef struct {
    BTreeNode *root;
    int order;
} BTree;


BTree* btree_create_tree(int order);

BTreeNode* btree_create_node(int order, bool leaf);

void btree_free_node(BTreeNode* node);

int btree_binary_search(BTreeNode* node, int value);

void btree_add_node(BTree* tree, int value);

BTreeNode* btree_add_recursive(BTree* tree, BTreeNode* node, int value, int* promoted);

BTreeNode* btree_split_node(BTree* tree, BTreeNode* node, int* promoted);

void btree_remove_node(BTree* tree, int value);

void btree_remove_recursive(BTree* tree, BTreeNode* node, int value);

void btree_balance(BTree* tree, BTreeNode* father, int index);

void btree_merge(BTreeNode* father, int index);

void btree_set_random_numbers(BTree* tree, int* random_numbers, int dataset_size);

void btree_remove_random_numbers(BTree* tree, int* random_numbers, int dataset_size);

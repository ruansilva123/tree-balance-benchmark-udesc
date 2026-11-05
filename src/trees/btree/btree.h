#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int total;
    int* keys;
    struct Node** childs;
    struct Node* father; 
} Node;

typedef struct BTree {
  Node* root;
  int order;
} Btree;

BTree* create_b_tree(int);

Node * add_node(BTree*);

int binary_search(Node*, int);

void add_node_key(Node*, Node*, int);

Node* split_node(BTree*, Node*);

void add_key_recursive(BTree*, Node*, Node*, int);

void add_key(BTree*, int);

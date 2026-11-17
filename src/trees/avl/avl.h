// libs
#include <stdbool.h>


typedef struct Node {
    struct Node *father;
    struct Node *left;
    struct Node *right;
    int height;
    int value;
} Node;

typedef struct {
    Node *root;
} AVLTree;


AVLTree* avl_create_tree();

void avl_add_node(AVLTree* tree, int value);

void avl_remove_node(AVLTree* tree, int value);

void avl_balance(AVLTree* tree, Node* node);

int avl_balance_factor(Node* node);

int avl_get_height(Node* node);

Node* avl_simple_left_rotation(Node* node, AVLTree* tree);

Node* avl_simple_right_rotation(Node* node, AVLTree* tree);

Node* avl_double_left_rotation(Node* node, AVLTree* tree);

Node* avl_double_right_rotation(Node* node, AVLTree* tree);

void avl_set_random_numbers(AVLTree* tree, int* random_numbers, int dataset_size);

void avl_remove_random_numbers(AVLTree* tree, int* random_numbers, int dataset_size);
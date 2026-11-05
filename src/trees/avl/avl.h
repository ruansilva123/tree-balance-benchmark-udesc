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


AVLTree* create_avl_tree();

bool empty_tree(AVLTree* tree);

void add_node(AVLTree* tree, int value);

void remove_node(AVLTree* tree, int value);

void balance(AVLTree* tree, Node* node);

int balance_factor(Node* node);

int get_height(Node* node);

Node* simple_left_rotation(Node* node, AVLTree* tree);

Node* simple_right_rotation(Node* node, AVLTree* tree);

Node* double_left_rotation(Node* node, AVLTree* tree);

Node* double_right_rotation(Node* node, AVLTree* tree);

void set_random_numbers(AVLTree* tree, int* random_numbers, int dataset_size);

void remove_random_numbers(AVLTree* tree, int* random_numbers, int dataset_size);
// libs
#include <stdbool.h>


typedef enum {
    RED,
    BLACK
} Color;

typedef struct RedBlackNode {
    struct RedBlackNode *father;
    struct RedBlackNode *left;
    struct RedBlackNode *right;
    Color color;
    int value;
} RedBlackNode;

typedef struct {
    RedBlackNode *root;
} RedBlackTree;


RedBlackTree* red_black_create_tree();

void red_black_add_node(RedBlackTree* tree, int value);

void red_black_remove_node(RedBlackTree* tree, int value);

void red_black_add_balance(RedBlackTree* tree, RedBlackNode* node);

void red_black_remove_balance(RedBlackTree* tree, RedBlackNode* node, RedBlackNode* father);

bool red_black_is_black(RedBlackNode* node);

void red_black_left_rotation(RedBlackTree* tree, RedBlackNode* node);

void red_black_right_rotation(RedBlackTree* tree, RedBlackNode* node);

void red_black_set_random_numbers(RedBlackTree* tree, int* random_numbers, int dataset_size);

void red_black_remove_random_numbers(RedBlackTree* tree, int* random_numbers, int dataset_size);

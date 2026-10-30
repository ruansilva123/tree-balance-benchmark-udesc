typedef struct {
    struct Node *father;
    struct Node *left;
    struct Node *right;
    int value;
} Node;

typedef struct {
    Node *root;
} AVLTree;


AVLTree* create_avl_tree();
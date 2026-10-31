#ifndef BLACKRED_H
#define BLACKRED_H

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

#define boolean int
#define true  1
#define false  0

typedef struct BlackRedTree{
    Node *root;
} RedBlackTree;

static RedBlackTree* createTree(){
    printf("Inicializando a arvore\n");
    RedBlackTree *tree = (RedBlackTree*) malloc(sizeof(RedBlackTree));
    tree->root = NULL;
    return tree;
}

static void freeNodes(Node *node){
    if(node != NULL){
        freeNodes(node->left);
        freeNodes(node->right);
        free(node);
    }
}

static void destroyTree(RedBlackTree *tree){
    if(tree == NULL){
        return;
    }
    freeNodes(tree->root);
    free(tree);
}

/*
Read-only functions, passes a const pointer
so it makes sure it doesnt change the values of the RedBlackTree
*/
static void printTree(const Node *node, int level){//Print, Left, Right -- Pre-order
    if(node != NULL){

        for(int i = 0; i < level; i++){
            printf("     ");
        }

        printf("|-- [Nivel %d] -> [%d] %d \n", level, node->key, node->data);
        printTree(node->left, level + 1);
        printTree(node->right, level + 1);
    }
}

static void printTreeHelper(const RedBlackTree *tree){
    if(tree == NULL || tree->root == NULL){
        printf("Arvore Vazia\n");
        return;
    }
    printf("-------------------\n");
    printTree(tree->root, 0);
    printf("-------------------\n");
}

static int searchTree(const Node *node, int id){
    if(node != NULL){
        if(node->key == id){
            printf("Node encontrado!:\n");
            printf("[%d] - %d\n", node->key, node->data);
            return 1;
        }else{
            if(node->key > id){
                return searchTree(node->left, id);
            }else{
                return searchTree(node->right, id);
            }
        }
    }
    return 0;
}
/*
Write functions
*/

static void LeftR(RedBlackTree *tree, Node *pivot){
    //pivot desce
    //seu filho sobe (y)
    //filho esquerdo de y sobe
    Node *y = pivot->right;
    pivot->right = y->left;

    if (y->left != NULL) {
        y->left->parent = pivot;
    }

    y->parent = pivot->parent;

    if (pivot->parent == NULL) {
        tree->root = y;
    } else if (pivot == pivot->parent->left) {
        pivot->parent->left = y;
    } else {
        pivot->parent->right = y;
    }

    y->left = pivot;
    pivot->parent = y;
}

static void RightR(RedBlackTree *tree, Node *pivot){
    //pivot desce
    //seu filho sobe (root)
    //filho direito de root sobe
    Node *root = pivot->left;
    pivot->left = root->right;

    if (root->right != NULL) {
        root->right->parent = pivot;
    }

    root->parent = pivot->parent;

    if (pivot->parent == NULL) {
        tree->root = root;
    } else if (pivot == pivot->parent->right) {
        pivot->parent->right = root;
    } else {
        pivot->parent->left = root;
    }

    root->right = pivot;
    pivot->parent = root;
}

static void insertFixup(RedBlackTree *tree, Node *z) {
    while (z != tree->root && z->parent->color == RED) {

        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;

            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftR(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightR(tree, z->parent->parent);
            }
        }
        else {
            Node *y = z->parent->parent->left;

            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightR(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftR(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

static void insert(RedBlackTree *tree, Node *newNode) {
    Node *y = NULL;
    Node *root = tree->root;

    while (root != NULL) {
        y = root;
        if (newNode->key < root->key) {
            root = root->left;
        } else if (newNode->key > root->key) {
            root = root->right;
        } else {
            return;
        }
    }

    newNode->parent = y;

    if (y == NULL) {
        tree->root = newNode;
    } else if (newNode->key < y->key) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = RED;
    insertFixup(tree, newNode);
}

static void transplant(RedBlackTree *tree, Node *u, Node *v){
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != NULL) {
        v->parent = u->parent;
    }
}

static Node* minimum(Node *node){
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

/*
x pode ser NULL (folha), por isso o pai e passado explicitamente.
Quando x e NULL, x == xParent->left so e verdadeiro se x for o filho esquerdo,
pois um pai com os dois filhos NULL nunca ocorre aqui (o irmao teria altura negra >= 1).
*/
static void deleteFixup(RedBlackTree *tree, Node *x, Node *xParent) {
    while (x != tree->root && (x == NULL || x->color == BLACK)) {

        if (x == xParent->left) {
            Node *w = xParent->right;

            if (w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                LeftR(tree, xParent);
                w = xParent->right;
            }

            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightR(tree, w);
                    w = xParent->right;
                }
                w->color = xParent->color;
                xParent->color = BLACK;
                if (w->right != NULL) {
                    w->right->color = BLACK;
                }
                LeftR(tree, xParent);
                x = tree->root;
                xParent = NULL;
            }
        } else {
            Node *w = xParent->left;

            if (w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                RightR(tree, xParent);
                w = xParent->left;
            }

            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftR(tree, w);
                    w = xParent->left;
                }
                w->color = xParent->color;
                xParent->color = BLACK;
                if (w->left != NULL) {
                    w->left->color = BLACK;
                }
                RightR(tree, xParent);
                x = tree->root;
                xParent = NULL;
            }
        }
    }

    if (x != NULL) {
        x->color = BLACK;
    }
}

static void delete(RedBlackTree *tree, int deleteId){
    Node *z = tree->root;

    while (z != NULL && z->key != deleteId) {
        z = (deleteId < z->key) ? z->left : z->right;
    }

    if (z == NULL) {
        return;
    }

    Node *y = z;
    Color yOriginalColor = y->color;
    Node *x;
    Node *xParent;

    if (z->left == NULL) {
        x = z->right;
        xParent = z->parent;
        transplant(tree, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        xParent = z->parent;
        transplant(tree, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            xParent = y;
        } else {
            xParent = y->parent;
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        deleteFixup(tree, x, xParent);
    }

    free(z);
}

#endif

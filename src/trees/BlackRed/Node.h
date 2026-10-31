#ifndef NODE_H
#define NODE_H
#define boolean int
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Color.h"

typedef struct Node{
    int key;
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    Color color;
} Node;

static int global_index = 0;

static void setGlobalIndex(int val) {
    global_index = val;
}

static int createIndex(){
    return ++global_index;
}

static Node* createNode(const int data, int rowsize){
    Node *newNode = (Node*) malloc(sizeof(Node));

    if(newNode != NULL){ //case de falha no malloc
        newNode->data = data;
        newNode->key = createIndex();
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        newNode->color = RED;
    }

    return newNode;
}

#endif
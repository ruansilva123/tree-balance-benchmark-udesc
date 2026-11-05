//libs
#include <stdio.h>
#include <stdlib.h>

//project
#include "./avl.h"

BTree* create_b_tree(int a){
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNo(a);

    return a;
}
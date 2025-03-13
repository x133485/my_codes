#ifndef Function_H
#define Function_H

typedef struct node { 
    char key[30]; 
    char description[200]; 
    struct node *left; 
    struct node *right; 
} Node; 

typedef struct { 
    Node *root; 
} Tree; 

Node* createNode(char *key,char *description);
void printNode(Node *node);
Tree* createTree();
int treeEmpty(Tree *tree);
void insertNode(Node *node, Tree *tree);  


#endif 
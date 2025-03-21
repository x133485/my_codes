#ifndef Function_H
#define Function_H

#include <stdio.h>

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
void clearInputBuffer();
void inorderPrint(Node* root,int n, int *count);
int countNodes(Node* root);
Node* search(Node *root, char *key);
Node *delete(Node *root, char *key);
void loadTextFile(char* filename);
void preorderWrite(Node *node,FILE *file);
void storeTextFile(Node* root,char *filename);

#endif 